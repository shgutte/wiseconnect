/*******************************************************************************
 * @file
 * @brief Instant BG Scan Example Application
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

#include "sl_status.h"
#include "sl_board_configuration.h"
#include "cmsis_os2.h"
#include "errno.h"
#include "sl_wifi.h"
#include "sl_net.h"
#include "socket.h"
#include "sl_utility.h"
#include "sl_net_si91x.h"
#include "sl_wifi_callback_framework.h"
#include <string.h>

#ifdef RSI_M4_INTERFACE
#include "rsi_wisemcu_hardware_setup.h"
#include "rsi_ps_config.h"
#endif

/******************************************************
 *                      Macros
 ******************************************************/
#define SERVER_IP_ADDRESS "192.168.0.102"
#define DATA              "HellofromUDPclient!!!"
#define SERVER_PORT       5001
#define NUMBER_OF_PACKETS 1000
#define WIFI_SCAN_TIMEOUT 10000

#ifdef RSI_M4_INTERFACE
#define WIRELESS_WAKEUP_IRQHandler NPSS_TO_MCU_WIRELESS_INTR_IRQn
#endif // RSI_M4_INTERFACE

#define ADV_SCAN_THRESHOLD              -40
#define ADV_RSSI_TOLERANCE_THRESHOLD    5
#define ADV_ACTIVE_SCAN_DURATION        15
#define ADV_PASSIVE_SCAN_DURATION       20
#define ADV_MULTIPROBE                  0
#define ADV_SCAN_PERIODICITY            10
#define BROADCAST_DROP_THRESHOLD        5000
#define BROADCAST_IN_TIM                1
#define BROADCAST_TIM_TILL_NEXT_COMMAND 1

/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
sl_status_t send_data(void);
void M4_sleep_wakeup(void);
sl_status_t show_scan_results(sl_wifi_scan_result_t *scan_result);
sl_status_t scan_callback_handler(sl_wifi_event_t event,
                                  sl_wifi_scan_result_t *result,
                                  uint32_t result_length,
                                  void *arg);

/******************************************************
 *               Static Inline Functions
 ******************************************************/
static inline void print_errno(void)
{
  printf("\r\nerrno: %d\r\n", errno);
}

/******************************************************
 *               Variable Definitions
 ******************************************************/
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

static const sl_wifi_device_configuration_t station_init_configuration = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = NULL,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .boot_config = { .oper_mode = SL_SI91X_CLIENT_MODE,
                   .coex_mode = SL_SI91X_WLAN_MODE,
                   .feature_bit_map =
                     (SL_SI91X_FEAT_SECURITY_OPEN | SL_SI91X_FEAT_AGGREGATION | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
#ifdef RSI_M4_INTERFACE
                      | SL_SI91X_FEAT_WPS_DISABLE
#endif
                      ),
                   .tcp_ip_feature_bit_map     = (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT
                                              | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map     = (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID),
                   .ext_custom_feature_bit_map = (SL_SI91X_EXT_FEAT_LOW_POWER_MODE | SL_SI91X_EXT_FEAT_XTAL_CLK |
#ifndef RSI_M4_INTERFACE
                                                  RAM_LEVEL_NWP_ALL_MCU_ZERO
#else
                                                  RAM_LEVEL_NWP_BASIC_MCU_ADV
#endif
#ifdef CHIP_917
                                                  | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#endif
                                                  ),
                   .bt_feature_bit_map         = 0,
                   .ext_tcp_ip_feature_bit_map = SL_SI91X_CONFIG_FEAT_EXTENTION_VALID,
                   .ble_feature_bit_map        = 0,
                   .ble_ext_feature_bit_map    = 0,
                   .config_feature_bit_map     = SL_SI91X_FEAT_SLEEP_GPIO_SEL_BITMAP }
};

volatile bool scan_results_complete  = false;
volatile sl_status_t callback_status = SL_STATUS_OK;

/******************************************************
 *               Function Definitions
 ******************************************************/
void app_init(const void *unused)
{
  UNUSED_PARAMETER(unused);
  osThreadNew((osThreadFunc_t)application_start, NULL, &thread_attributes);
}

static void application_start(void *argument)
{
  UNUSED_PARAMETER(argument);
  sl_status_t status;
  sl_wifi_performance_profile_t performance_profile                 = { .profile = ASSOCIATED_POWER_SAVE };
  sl_wifi_scan_configuration_t wifi_scan_configuration              = { 0 };
  sl_wifi_advanced_scan_configuration_t advanced_scan_configuration = { 0 };

  status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &station_init_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start Wi-Fi Client interface: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi client init success\r\n");

  status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
  if (status != SL_STATUS_OK) {
    printf("Failed to bring Wi-Fi client interface up: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi client connected\r\n");

  status = sl_wifi_filter_broadcast(BROADCAST_DROP_THRESHOLD, BROADCAST_IN_TIM, BROADCAST_TIM_TILL_NEXT_COMMAND);
  if (status != SL_STATUS_OK) {
    printf("\r\nsl_wifi_filter_broadcast Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  // set performance profile
  status = sl_wifi_set_performance_profile(&performance_profile);
  if (status != SL_STATUS_OK) {
    printf("\r\nPower save configuration Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  printf("\r\nPower save configuration success\r\n");

  advanced_scan_configuration.active_channel_time  = ADV_ACTIVE_SCAN_DURATION;
  advanced_scan_configuration.passive_channel_time = ADV_PASSIVE_SCAN_DURATION;
  advanced_scan_configuration.trigger_level        = ADV_SCAN_THRESHOLD;
  advanced_scan_configuration.trigger_level_change = ADV_RSSI_TOLERANCE_THRESHOLD;
  advanced_scan_configuration.enable_multi_probe   = ADV_MULTIPROBE;
  status = sl_wifi_set_advanced_scan_configuration(&advanced_scan_configuration);
  if (status != SL_STATUS_OK) {
    printf("\r\nsl_wifi_set_advanced_scan_configuration failed with status %lx\r\n", status);
    return;
  }

  wifi_scan_configuration.type                   = SL_WIFI_SCAN_TYPE_ADV_SCAN;
  wifi_scan_configuration.periodic_scan_interval = ADV_SCAN_PERIODICITY;

  sl_wifi_set_scan_callback(scan_callback_handler, NULL);
  status = sl_wifi_start_scan(SL_WIFI_CLIENT_2_4GHZ_INTERFACE, NULL, &wifi_scan_configuration);
  if (SL_STATUS_IN_PROGRESS == status) {
    printf("Scanning...\r\n");
    const uint32_t start = osKernelGetTickCount();

    while (!scan_results_complete && (osKernelGetTickCount() - start) <= WIFI_SCAN_TIMEOUT) {
      osThreadYield();
    }

    status = scan_results_complete ? callback_status : SL_STATUS_TIMEOUT;
  }

  if (status != SL_STATUS_OK) {
    printf("\r\nscan failed with status %lx\r\n", status);
    return;
  }

  status = send_data();
  if (status != SL_STATUS_OK) {
    printf("\r\nSend data failed with status %lx\r\n", status);
    return;
  }
  printf("\r\nExample Demonstration Completed\r\n");

#ifdef RSI_M4_INTERFACE
  M4_sleep_wakeup();
#endif
}

sl_status_t send_data(void)
{
  int32_t bytes_sent          = -1;
  int32_t total_num_of_bytes  = 0;
  int32_t packet_count        = 0;
  struct sockaddr_in address  = { 0 };
  sl_ipv4_address_t server_ip = { 0 };

  //create UDP socket
  int32_t socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_fd < 0) {
    printf("\r\nSocket Create failed with bsd error: %d\r\n", errno);
    return SL_STATUS_FAIL;
  }
  printf("\r\nsocket creation success\r\n");

  sl_net_inet_addr((char *)SERVER_IP_ADDRESS, (uint32_t *)&server_ip);

  //send data to server
  address.sin_port        = SERVER_PORT;
  address.sin_addr.s_addr = server_ip.value;

  while (packet_count < NUMBER_OF_PACKETS) {
    bytes_sent =
      sendto(socket_fd, (uint8_t *)DATA, (sizeof(DATA) - 1), 0, (const struct sockaddr *)&address, sizeof(address));
    if (bytes_sent < 0) {
      printf("\r\nSend failed with bsd error: %d\r\n", errno);
      close(socket_fd);
      return SL_STATUS_FAIL;
    }
    total_num_of_bytes += bytes_sent;
    packet_count++;
  }

  printf("total number of bytes sent: %ld\n", total_num_of_bytes);
  close(socket_fd);

  return SL_STATUS_OK;
}

#ifdef RSI_M4_INTERFACE

void M4_sleep_wakeup(void)
{
#ifndef FLASH_BASED_EXECUTION_ENABLE
  /* LDOSOC Default Mode needs to be disabled */
  sl_si91x_disable_default_ldo_mode();

  /* bypass_ldorf_ctrl needs to be enabled */
  sl_si91x_enable_bypass_ldo_rf();

  sl_si91x_disable_flash_ldo();

  /* Configure RAM Usage and Retention Size */
  sl_si91x_configure_ram_retention(WISEMCU_48KB_RAM_IN_USE, WISEMCU_RETAIN_DEFAULT_RAM_DURING_SLEEP);

  /* Trigger M4 Sleep */
  sl_si91x_trigger_sleep(SLEEP_WITH_RETENTION,
                         DISABLE_LF_MODE,
                         0,
                         (uint32_t)RSI_PS_RestoreCpuContext,
                         0,
                         RSI_WAKEUP_WITH_RETENTION_WO_ULPSS_RAM);

#else
  /* Configure RAM Usage and Retention Size */
  sl_si91x_configure_ram_retention(WISEMCU_192KB_RAM_IN_USE, WISEMCU_RETAIN_DEFAULT_RAM_DURING_SLEEP);

  /* Trigger M4 Sleep*/
  sl_si91x_trigger_sleep(SLEEP_WITH_RETENTION,
                         DISABLE_LF_MODE,
                         WKP_RAM_USAGE_LOCATION,
                         (uint32_t)RSI_PS_RestoreCpuContext,
                         IVT_OFFSET_ADDR,
                         RSI_WAKEUP_FROM_FLASH_MODE);
#endif
}
#endif

sl_status_t show_scan_results(sl_wifi_scan_result_t *scan_result)
{
  ARGS_CHECK_NULL_POINTER(scan_result);
  printf("%ld scan results:\n", scan_result->scan_count);
  if (scan_result->scan_count)
    printf("\n   %s %24s %s", "SSID", "SECURITY", "NETWORK");
  printf("%12s %12s %s\n", "BSSID", "CHANNEL", "RSSI");
  for (uint32_t a = 0; a < scan_result->scan_count; ++a) {
    uint8_t *bssid = (uint8_t *)&scan_result->scan_info[a].bssid;
    printf("%-24s %4u,  %4u, ",
           scan_result->scan_info[a].ssid,
           scan_result->scan_info[a].security_mode,
           scan_result->scan_info[a].network_type);
    printf("  %02x:%02x:%02x:%02x:%02x:%02x, %4u,  -%u\n",
           bssid[0],
           bssid[1],
           bssid[2],
           bssid[3],
           bssid[4],
           bssid[5],
           scan_result->scan_info[a].rf_channel,
           scan_result->scan_info[a].rssi_val);
  }
  printf("End");

  return SL_STATUS_OK;
}

sl_status_t scan_callback_handler(sl_wifi_event_t event,
                                  sl_wifi_scan_result_t *result,
                                  uint32_t result_length,
                                  void *arg)
{
  UNUSED_PARAMETER(result_length);
  UNUSED_PARAMETER(arg);
  if (CHECK_IF_EVENT_FAILED(event)) {
    callback_status       = *(sl_status_t *)result;
    scan_results_complete = true;
    return SL_STATUS_FAIL;
  }

  callback_status = show_scan_results(result);

  scan_results_complete = true;
  return SL_STATUS_OK;
}
