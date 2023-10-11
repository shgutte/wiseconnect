/***************************************************************************/ /**
 * @file
 * @brief TCP Client Example Application
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "errno.h"
#include "netdb.h"
#include "sl_wifi_callback_framework.h"
#include "sl_status.h"
#include "sl_board_configuration.h"
#include "cmsis_os2.h"
#include "sl_wifi.h"
#include "socket.h"
#include "sl_utility.h"
#include "sl_net.h"
#include "sl_net_si91x.h"
#include <string.h>
#include "sl_net_wifi_types.h"
#include <stdint.h>
#include "app.h"
#include "sl_si91x_types.h"
/******************************************************
 *                      Macros
 ******************************************************/
/******************************************************
 *                    Constants
 ******************************************************/
#define SERVER_IP         "192.168.1.4"
#define SERVER_PORT       5005
#define NUMBER_OF_PACKETS 10000

/******************************************************
 *               Variable Definitions
 ******************************************************/
uint8_t data1[1460] = { 0 };

const osThreadAttr_t thread_attributes = {
  .name       = "app",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 3072,
  .priority   = osPriorityLow,
  .tz_module  = 0,
  .reserved   = 0,
};
sl_si91x_app_cb_t sl_si91x_wlan_app_cb; //! application control block

/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
void send_data_to_tcp_server();
/******************************************************
 *               Function Definitions
 ******************************************************/
static const sl_wifi_device_configuration_t station_init_configuration = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = NULL,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .boot_config = { .oper_mode = SL_SI91X_CLIENT_MODE,
                   .coex_mode = SL_SI91X_WLAN_BLE_MODE,
                   .feature_bit_map =
                     (SL_SI91X_FEAT_SECURITY_OPEN | SL_SI91X_FEAT_AGGREGATION | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
#ifdef RSI_M4_INTERFACE
                      | SL_SI91X_FEAT_WPS_DISABLE
#endif
                      ),
                   .tcp_ip_feature_bit_map = (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT
                                              | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map = (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID),
                   .ext_custom_feature_bit_map =
                     (SL_SI91X_EXT_FEAT_XTAL_CLK | BIT(29) | SL_SI91X_EXT_FEAT_UART_SEL_FOR_DEBUG_PRINTS
                      | SL_SI91X_EXT_FEAT_LOW_POWER_MODE |
#ifndef RSI_M4_INTERFACE
                      RAM_LEVEL_NWP_ALL_MCU_ZERO
#else
                      RAM_LEVEL_NWP_ADV_MCU_BASIC // RAM_LEVEL_NWP_MEDIUM_MCU_MEDIUM
                                                  // //RAM_LEVEL_NWP_BASIC_MCU_ADV
#endif
                      ),
                   .bt_feature_bit_map         = 0,
                   .ext_tcp_ip_feature_bit_map = SL_SI91X_CONFIG_FEAT_EXTENTION_VALID,
                   //SL_SI91X_EXT_TCP_IP_WAIT_FOR_SOCKET_CLOSE
                   .ble_feature_bit_map     = 0,
                   .ble_ext_feature_bit_map = 0,
                   .config_feature_bit_map  = SL_SI91X_FEAT_SLEEP_GPIO_SEL_BITMAP | BIT(26) },
  .ta_pool = { .tx_ratio_in_buffer_pool     = TX_POOL_RATIO,
               .rx_ratio_in_buffer_pool     = RX_POOL_RATIO,
               .global_ratio_in_buffer_pool = GLOBAL_POOL_RATIO }

};

void app_init(void)
{

  osThreadNew((osThreadFunc_t)application_start, NULL, &thread_attributes);
}

sl_status_t join_callback_handler(sl_wifi_event_t event, char *result, uint32_t result_length, void *arg)
{
  UNUSED_PARAMETER(result);
  UNUSED_PARAMETER(arg);
  sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_UNCONNECTED_STATE;
  printf("in join CB\r\n");
  if (CHECK_IF_EVENT_FAILED(event)) {
    printf("F: Join Event received with %lu bytes payload\n", result_length);
    return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}
static void application_start(void *argument)
{
  UNUSED_PARAMETER(argument);
  int count                                         = 1;
  sl_wifi_performance_profile_t performance_profile = { 0 };
  sl_ip_address_t ip_address                        = { 0 };
  sl_net_wifi_client_profile_t profile              = { 0 };
  int client_socket                                 = -1;
  int return_value                                  = 0;
  int status                                        = -1;
  int sent_bytes;
  int packet_count                  = 0;
  sl_ipv4_address_t ip              = { 0 };
  struct sockaddr_in server_address = { 0 };
  sl_mac_address_t mac_addr         = { 0 };

  while (1) {
    switch (sl_si91x_wlan_app_cb.state) {

      case SL_SI91X_WLAN_INITIAL_STATE: {
        status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &station_init_configuration, NULL, NULL);
        if (status != SL_STATUS_OK) {
          printf("Failed to start Wi-Fi Client interface: 0x%x\r\n", status);
          break;
        } else {

          printf("\r\nWiFi Init Success\r\n");
          status = sl_wifi_get_mac_address(SL_WIFI_CLIENT_INTERFACE, &mac_addr);
          if (status == SL_STATUS_OK) {
            printf("%x:%x:%x:%x:%x:%x\r\n",
                   mac_addr.octet[0],
                   mac_addr.octet[1],
                   mac_addr.octet[2],
                   mac_addr.octet[3],
                   mac_addr.octet[4],
                   mac_addr.octet[5]);
          } else {
            printf("Failed to get mac address: 0x%x\r\n", status);
          }
          for (int i = 1; i < sizeof(data1); i++) {
            data1[i] = i;
          }
          sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_UNCONNECTED_STATE;
        }
      } break;
      case SL_SI91X_WLAN_UNCONNECTED_STATE: {
        sl_wifi_set_join_callback(join_callback_handler, NULL);
        status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
        if (status != SL_STATUS_OK) {
          printf("Failed to bring Wi-Fi client interface up: 0x%x\r\n", status);
          if (status == SL_STATUS_SI91X_IP_ADDRESS_ERROR) {
            sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_IP_CONFIG_RETRY_STATE;
          }
          break;
        } else {
          printf("Wi-Fi client connected\r\n");
          sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_NET_UP_STATE;
        }
      } break;
      case SL_SI91X_WLAN_IP_CONFIG_RETRY_STATE: {
        memset(&profile, 0, sizeof(sl_net_wifi_client_profile_t));
        memset(&ip_address, 0, sizeof(sl_ip_address_t));
        memset(&performance_profile, 0, sizeof(sl_wifi_performance_profile_t));
        status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &profile);
        if (status != SL_STATUS_OK) {
          printf("Failed to get client profile in ip config retry: 0x%x\r\n", status);
          break;
        } else {
          printf("\r\nSuccess to get client profile in ip config retry\r\n");
          status = sl_si91x_configure_ip_address(&profile.ip, CLIENT_MODE);
          if (status != SL_STATUS_OK) {
            printf("Ip config fail with status in ip config retry : 0x%x\r\n", status);
            break;
          } else {
            printf("Ip config Success in ip config retry\r\n");
            sl_net_set_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &profile);
            printf("\r\nSuccess to Set client profile in ip config retry\r\n");
            ip_address.type = SL_IPV4;
            memcpy(&ip_address.ip.v4.bytes, &profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
            print_sl_ip_address(&ip_address);
            sl_si91x_wlan_app_cb.state = SL_SI91X_POWERSAVE_STATE;
          }
        }
      } break;
      case SL_SI91X_WLAN_NET_UP_STATE: {
        memset(&profile, 0, sizeof(sl_net_wifi_client_profile_t));
        memset(&ip_address, 0, sizeof(sl_ip_address_t));
        memset(&performance_profile, 0, sizeof(sl_wifi_performance_profile_t));
        status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &profile);
        if (status != SL_STATUS_OK) {
          printf("Failed to get client profile: 0x%x\r\n", status);
          break;
        } else {
          printf("\r\nSuccess to get client profile\r\n");

          ip_address.type = SL_IPV4;
          memcpy(&ip_address.ip.v4.bytes, &profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
          print_sl_ip_address(&ip_address);
          sl_si91x_wlan_app_cb.state = SL_SI91X_POWERSAVE_STATE;
        }
      } break;
      case SL_SI91X_POWERSAVE_STATE: {
        /*if (station_init_configuration.boot_config.coex_mode == SL_SI91X_WLAN_BLE_MODE) {
          status = rsi_bt_power_save_profile(2, 1);
          if (status != RSI_SUCCESS) {
            printf("\r\n Failed to initiate power save in BLE mode \r\n");
            break;
          }
        }*/
        performance_profile.profile = ASSOCIATED_POWER_SAVE_LOW_LATENCY;
        status                      = sl_wifi_set_performance_profile(&performance_profile);
        if (status != SL_STATUS_OK) {
          printf("\r\nPower save configuration Failed, Error Code : 0x%X\r\n", status);
          break;
        }
        printf("\r\n power save success \r\n");
        sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_SOCKET_CREATE_STATE;
      } break;
      case SL_SI91X_WLAN_SOCKET_CREATE_STATE: {
        client_socket = -1;
        return_value  = 0;
        status        = -1;
        sent_bytes    = 0;
        packet_count  = 0;
        memset(&ip, 0, sizeof(sl_ipv4_address_t));
        memset(&server_address, 0, sizeof(struct sockaddr_in));
        socklen_t socket_length = sizeof(struct sockaddr_in);
        sl_net_inet_addr(SERVER_IP, (uint32_t *)&ip);
        server_address.sin_family      = AF_INET;
        server_address.sin_port        = SERVER_PORT;
        server_address.sin_addr.s_addr = ip.value;
        //!Create socket
        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket < 0) {
          printf("\r\nSocket creation failed with bsd error: %d\r\n", errno);
          break;
        }
        printf("\r\nTCP Socket Create Success\r\n");
        //! Socket connect
        return_value = connect(client_socket, (struct sockaddr *)&server_address, socket_length);
        if (return_value < 0) {
          printf("\r\nSocket connect failed with bsd error: %d\r\n", errno);
          sl_si91x_wlan_app_cb.state = SL_SI91X_SOCKET_CLOSE_STATE;
          break;
        }
        printf("\r\nTCP Socket Connect Success\r\n");
        if (sl_si91x_wlan_app_cb.state == SL_SI91X_WLAN_SOCKET_CREATE_STATE) {
          sl_si91x_wlan_app_cb.state = SL_SI91X_SEND_SOCKET_DATA_STATE;
        }
      } break;
      case SL_SI91X_SEND_SOCKET_DATA_STATE: {
        //! send data
        while (packet_count < NUMBER_OF_PACKETS) {
          sent_bytes = send(client_socket, data1, sizeof(data1), 0);
          if (sent_bytes < 0) {
            printf("\r\nSend failed with bsd error:%d\r\n", errno);
            if (errno == ENOTCONN) {
              sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_SOCKET_CREATE_STATE;
            }
            break;
          } else if (errno == 0x9) {
            printf("\r\n send error 0x9 \r\n");
            break;
          }
          packet_count++;
        }
        printf("\r\n%d packets sent success\r\n", packet_count);
        if (sl_si91x_wlan_app_cb.state == SL_SI91X_SEND_SOCKET_DATA_STATE) {
          sl_si91x_wlan_app_cb.state = SL_SI91X_SOCKET_CLOSE_STATE;
        }
      } break;
      case SL_SI91X_SOCKET_CLOSE_STATE: {
        //!Socket close
        status = close(client_socket);
        if (status != 0) {
          printf("\r\nSocket close fail, status = %d, errno = %d\r\n", status, errno);
        } else {
          printf("\r\nSocket close success\r\n");
        }
        sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_NET_DOWN_STATE;
      } break;
      case SL_SI91X_WLAN_NET_DOWN_STATE: {
        status = sl_net_down(SL_NET_WIFI_CLIENT_INTERFACE);
        if (status != SL_STATUS_OK) {
          printf("Failed to down Wi-Fi client interface up: 0x%x\r\n", status);
          sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_UNCONNECTED_STATE;
          break;
        }
        printf("Wi-Fi client disconnected and count = %d\r\n", count++);
        sl_si91x_wlan_app_cb.state = SL_SI91X_WLAN_UNCONNECTED_STATE;
      } break;
      default:
        break;
    }
  }
  osThreadExit();
}
