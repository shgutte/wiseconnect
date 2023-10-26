/***************************************************************************/ /**
 * @file
 * @brief TCP Client and Server Example Application
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

#include "cmsis_os2.h"
#include "sl_net.h"
#include "sl_wifi.h"
#include "sl_net_dns.h"
#include "socket.h"
#include "sl_si91x_socket_support.h"
#include "errno.h"
#include "sl_rsi_utility.h"
#include "sl_board_configuration.h"
#include "sl_wifi_types.h"

//! Certificates to be loaded
#include "cacert.pem.h"

/******************************************************
 *                      Macros
 ******************************************************/
#define VERFIY_SOCKET_CREATE(expression)                                    \
  {                                                                         \
    if (expression) {                                                       \
      printf("\r\nSSL Socket Create failed with bsd error: %d\r\n", errno); \
    }                                                                       \
  };
/******************************************************
 *                    Constants
 ******************************************************/
#define SERVER_IP "192.168.0.108"

#define SERVER_PORT1 5003
#define SERVER_PORT2 5004
#define SERVER_PORT3 443

#define TX_ENABLE 1
#define RX_ENABLE 0

#define DATA1 "hello from tcp client"
#define DATA2 "hello from ssl tcp client"

#define SSL              1
#define LOAD_CERTIFICATE 1

#define MAX_SOCKET        3
#define NUMBER_OF_PACKETS 1000

#define SL_HIGH_PERFORMANCE_SOCKET BIT(7)
#define RECV_BUFFER_SIZE           1460
#define BACK_LOG                   1
#define TEST_TIMEOUT               10000

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
  .region_code = US,
  .boot_config = { .oper_mode = SL_SI91X_CLIENT_MODE,
                   .coex_mode = SL_SI91X_WLAN_ONLY_MODE,
                   .feature_bit_map =
#ifdef RSI_M4_INTERFACE
                     (SL_SI91X_FEAT_SECURITY_OPEN | SL_SI91X_FEAT_WPS_DISABLE),
#else
                     (SL_SI91X_FEAT_SECURITY_OPEN | SL_SI91X_FEAT_AGGREGATION),
#endif
                   .tcp_ip_feature_bit_map = (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT
                                              | SL_SI91X_TCP_IP_FEAT_SSL | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map = SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID,
                   .ext_custom_feature_bit_map =
                     (SL_SI91X_EXT_FEAT_XTAL_CLK | SL_SI91X_EXT_FEAT_UART_SEL_FOR_DEBUG_PRINTS | MEMORY_CONFIG
#ifdef CHIP_917
                      | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#endif
                      ),
                   .bt_feature_bit_map         = 0,
                   .ext_tcp_ip_feature_bit_map = (SL_SI91X_EXT_TCP_IP_FEAT_SSL_THREE_SOCKETS),
                   .ble_feature_bit_map        = 0,
                   .ble_ext_feature_bit_map    = 0,
                   .config_feature_bit_map     = 0 }
};

uint8_t recv_buffer[RECV_BUFFER_SIZE];
/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
sl_status_t clear_and_load_certificates_in_flash(void);
sl_status_t send_and_recieve_data(void);

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

  status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &station_init_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start Wi-Fi Client interface: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi client interface init success");

#if LOAD_CERTIFICATE
#if SSL
  status = clear_and_load_certificates_in_flash();
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading certificate: 0x%lx\r\n", status);
    return;
  }
#endif
#endif

  status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
  if (status != SL_STATUS_OK) {
    printf("Failed to bring Wi-Fi client interface up: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi client connected\r\n");

  status = send_and_recieve_data();
  if (status != SL_STATUS_OK) {
    printf("Bidirectional data transfer failed: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nBidirectional data transfer success\r\n");
}

sl_status_t clear_and_load_certificates_in_flash(void)
{
  sl_status_t status = SL_STATUS_OK;

  // Load SSL CA certificate
  status =
    sl_net_set_credential(SL_NET_TLS_SERVER_CREDENTIAL_ID(0), SL_NET_SIGNING_CERTIFICATE, cacert, sizeof(cacert) - 1);
  if (status != SL_STATUS_OK) {
    printf("\r\nLoading TLS CA certificate in to FLASH Failed, Error Code : 0x%lX\r\n", status);
  } else {
    printf("\r\nLoad TLS CA certificate at index %d Success\r\n", 0);
  }

  return status;
}

sl_status_t send_and_recieve_data(void)
{
  int32_t client_socket[MAX_SOCKET] = { 0 };
  int32_t socket_status             = -1;
  int sock_id                       = 0;
  struct sockaddr_in server_addr[MAX_SOCKET];

#if TX_ENABLE
  int sent_bytes;
  int packet_count                 = 0;
  sl_ipv4_address_t server_address = { 0 };

  printf("\r\nTX started\r\n");

  //! Converting and storing given IP address into SL IPV4
  sl_net_inet_addr(SERVER_IP, (uint32_t *)&server_address);

  //! Create Sockets
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    client_socket[sock_id] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    VERFIY_SOCKET_CREATE(client_socket[sock_id] < 0);
    printf("\r\n%d Socket Create Success\r\n", sock_id + 1);
  }

  //!Set socket
  socket_status = setsockopt(client_socket[2], SOL_TCP, TCP_ULP, TLS, sizeof(TLS));
  if (socket_status < 0) {
    printf("\r\n SSL Set socket failed with bsd error: %d\r\n", errno);
    close(client_socket[2]);
    return SL_STATUS_FAIL;
  }

  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    server_addr[sock_id].sin_family      = AF_INET;              //! Set server address family
    server_addr[sock_id].sin_addr.s_addr = server_address.value; //! Set IP address to localhost
    if (sock_id == 0) {
      server_addr[sock_id].sin_port = SERVER_PORT1; //! Set server port number
    }
    if (sock_id == 1) {
      server_addr[sock_id].sin_port = SERVER_PORT2; //! Set server port number
    }
    if (sock_id == 2) {
      server_addr[sock_id].sin_port = SERVER_PORT3; //! Set server port number
    }
  }

  //! Connect to server socket
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    socket_status =
      connect(client_socket[sock_id], (struct sockaddr *)&server_addr[sock_id], sizeof(server_addr[sock_id]));
    if (socket_status < 0) {
      printf("\r\n%d Socket Connect failed with bsd error: %d\r\n", sock_id + 1, errno);
      close(client_socket[sock_id]);
      return SL_STATUS_FAIL;
    }
    printf("\r\n%d Socket Connect Success\r\n", sock_id + 1);
  }

  //!Send data
  while (packet_count < NUMBER_OF_PACKETS) {
    sent_bytes = send(client_socket[0], DATA1, sizeof(DATA1), 0);
    if (sent_bytes < 0) {
      printf("\r\nSend failed on 1st client_socket  with bsd error : %d\r\n", errno);
      return SL_STATUS_FAIL;
    }
    sent_bytes = send(client_socket[1], DATA1, sizeof(DATA1), 0);
    if (sent_bytes < 0) {
      printf("\r\nSend failed on 2nd client_socket  with bsd error : %d\r\n", errno);
      return SL_STATUS_FAIL;
    }
    sent_bytes = send(client_socket[2], DATA2, sizeof(DATA2), 0);
    if (sent_bytes < 0) {
      printf("\r\nSend failed on 3rd client_socket  with bsd error : %d\r\n", errno);
      return SL_STATUS_FAIL;
    }
    packet_count++;
  }

  printf("\r\nTX completed success\r\n");

  //!Close sockets
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    socket_status = close(client_socket[sock_id]);
    if (socket_status < 0) {
      printf("\r\n%d Socket close failed with bsd error: %d\r\n", sock_id + 1, errno);
    }
  }

  printf("\r\nSocket Close Success\r\n");
#endif

#if RX_ENABLE
  int32_t server_socket[MAX_SOCKET] = { 0 };
  uint8_t high_performance_socket   = SL_HIGH_PERFORMANCE_SOCKET;
  uint32_t start                    = 0;
  uint32_t now                      = 0;
  int read_bytes                    = 1;

  printf("\r\n RX start\r\n");
  //! Create Sockets
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    server_socket[sock_id] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    VERFIY_SOCKET_CREATE(server_socket[sock_id] < 0);
    printf("\r\n%d Socket Create Success\r\n", sock_id + 1);
  }

  socket_status = setsockopt(server_socket[2], SOL_TCP, TCP_ULP, TLS, sizeof(TLS));
  if (socket_status < 0) {
    printf("\r\n SSL Set Socket 3 failed with bsd error: %d\r\n", errno);
    close(server_socket[2]);
    return SL_STATUS_FAIL;
  }

  //! Set socket
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    socket_status = sl_si91x_set_custom_sync_sockopt(server_socket[sock_id],
                                                     SOL_SOCKET,
                                                     SO_HIGH_PERFORMANCE_SOCKET,
                                                     &high_performance_socket,
                                                     sizeof(high_performance_socket));
    if (socket_status < 0) {
      printf("\r\nSet Socket %d option failed with bsd error: %d\r\n", sock_id + 1, errno);
      close(server_socket[sock_id]);
      return SL_STATUS_FAIL;
    }
  }

  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    server_addr[sock_id].sin_family = AF_INET; //! Set server address family
    if (sock_id == 0) {
      server_addr[sock_id].sin_port = SERVER_PORT1; //! Set server port number
    }
    if (sock_id == 1) {
      server_addr[sock_id].sin_port = SERVER_PORT2; //! Set server port number
    }
    if (sock_id == 2) {
      server_addr[sock_id].sin_port = SERVER_PORT3; //! Set server port number
      sl_net_inet_addr(SERVER_IP, &server_addr[sock_id].sin_addr.s_addr);
    }
  }

  //!Bind socket
  for (sock_id = 0; sock_id < MAX_SOCKET - 1; sock_id++) {
    socket_status =
      bind(server_socket[sock_id], (struct sockaddr *)&server_addr[sock_id], sizeof(server_addr[sock_id]));
    if (socket_status < 0) {
      printf("\r\n%d Socket bind failed with bsd error: %d\r\n", sock_id + 1, errno);
      close(server_socket[sock_id]);
      return SL_STATUS_FAIL;
    }
    printf("\r\n%d Socket bind success\r\n", sock_id + 1);
  }

  //!Listen socket
  for (sock_id = 0; sock_id < MAX_SOCKET - 1; sock_id++) {
    socket_status = listen(server_socket[sock_id], BACK_LOG);
    if (socket_status < 0) {
      printf("\r\n %d Socket listen failed with bsd error: %d\r\n", sock_id + 1, errno);
      close(server_socket[sock_id]);
      return SL_STATUS_FAIL;
    }
    printf("\r\n%d Socket listen success\r\n", sock_id + 1);
  }

  //!Accept socket
  for (sock_id = 0; sock_id < MAX_SOCKET - 1; sock_id++) {
    client_socket[sock_id] = accept(server_socket[sock_id], NULL, NULL);
    if (client_socket[sock_id] < 0) {
      printf("\r\n%d Socket accept failed with bsd error: %d\r\n", errno, sock_id + 1);
      close(server_socket[sock_id]);
      return SL_STATUS_FAIL;
    }
    printf("\r\n%d Client Socket Success\r\n", sock_id + 1);
  }

  //!Connect socket
  socket_status = connect(server_socket[2], (struct sockaddr *)&server_addr[2], sizeof(server_addr[2]));
  if (socket_status < 0) {
    printf("\r\n3rd Socket Connect failed with bsd error: %d\r\n", errno);
    close(server_socket[2]);
    return SL_STATUS_FAIL;
  }
  printf("\r\n3 Socket Connect Success\r\n");

  //!Recieve data
  start = osKernelGetTickCount();
  while (read_bytes > 0) {
    read_bytes = recv(client_socket[0], recv_buffer, sizeof(recv_buffer), 0);
    if (read_bytes < 0) {
      printf("\r\nReceive failed 1st socket with bsd error:%d\r\n", errno);
      close(client_socket[0]);
      close(server_socket[0]);
      return SL_STATUS_FAIL;
    }
    now = osKernelGetTickCount();
    if ((now - start) > TEST_TIMEOUT) {
      break;
    }
  }
  start = osKernelGetTickCount();
  while (read_bytes > 0) {
    read_bytes = recv(client_socket[1], recv_buffer, sizeof(recv_buffer), 0);
    if (read_bytes < 0) {
      printf("\r\nReceive failed 2nd socket with bsd error:%d\r\n", errno);
      close(client_socket[1]);
      close(server_socket[1]);
      return SL_STATUS_FAIL;
    }
    now = osKernelGetTickCount();
    if ((now - start) > TEST_TIMEOUT) {
      break;
    }
  }

  start = osKernelGetTickCount();
  now   = start;
  while (read_bytes > 0) {
    read_bytes = recv(server_socket[2], recv_buffer, sizeof(recv_buffer), 0);
    if (read_bytes < 0) {
      printf("\r\nReceive failed 3rd socket with bsd error:%d\r\n", errno);
      close(server_socket[2]);
      return SL_STATUS_FAIL;
    }
    now = osKernelGetTickCount();
    if ((now - start) > TEST_TIMEOUT) {
      break;
    }
  }

  printf("\r\nRX completed success\r\n");

  //!Close socket
  for (sock_id = 0; sock_id < MAX_SOCKET - 1; sock_id++) {
    socket_status = close(client_socket[sock_id]);
    if (socket_status < 0) {
      printf("\r\n%d Socket close failed with bsd error: %d\r\n", sock_id + 1, errno);
    }
  }
  for (sock_id = 0; sock_id < MAX_SOCKET; sock_id++) {
    socket_status = close(server_socket[sock_id]);
    if (socket_status < 0) {
      printf("\r\n%d Socket close failed with bsd error: %d\r\n", sock_id + 1, errno);
    }
  }

  printf("\r\nSocket Close Success\r\n");
#endif

  return SL_STATUS_OK;
}
