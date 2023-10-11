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
#include "sl_net_wifi_types.h"
#include <string.h>
#include <stdint.h>
#include "sl_si91x_socket.h"
#include "sl_si91x_socket_constants.h"

/******************************************************
 *                      Macros
 ******************************************************/
#define SERVER_IP        "192.168.1.2"
#define SERVER_PORT      5001
#define MAX_CLIENT_COUNT 1

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

static uint8_t is_client_accepted    = 0;
sl_ip_address_t ip_address           = { 0 };
sl_net_wifi_client_profile_t profile = { 0 };
uint32_t bytes_read                  = 0;

int client_socket = -1;
/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
void receive_data_from_client();
void accept_async_trigger(int32_t sock_id, struct sockaddr *addr, uint8_t ip_version);

/******************************************************
 *               Function Definitions
 ******************************************************/
void data_callback(uint32_t sock_no, uint8_t *buffer, uint32_t length)
{
  UNUSED_PARAMETER(sock_no);
  UNUSED_PARAMETER(buffer);
  bytes_read += length;
}

void accept_async_trigger(int32_t sock_id, struct sockaddr *addr, uint8_t ip_version)
{
  UNUSED_PARAMETER(addr);
  UNUSED_PARAMETER(ip_version);
  printf("\r\nSocket ID of client is %ld\r\n", sock_id);

  client_socket      = sock_id;
  is_client_accepted = 1;
}

void app_init(const void *unused)
{
  UNUSED_PARAMETER(unused);
  osThreadNew((osThreadFunc_t)application_start, NULL, &thread_attributes);
}

static void application_start(void *argument)
{
  UNUSED_PARAMETER(argument);

  sl_status_t status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &sl_wifi_default_client_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to start Wi-Fi Client interface: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi Init Success \r\n");

  status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to bring Wi-Fi client interface up: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi client connected\r\n");

  status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &profile);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to get client profile: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nClient profile is fetched successfully.\r\n");

  ip_address.type = SL_IPV4;
  memcpy(&ip_address.ip.v4.bytes, &profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
  print_sl_ip_address(&ip_address);

  receive_data_from_client();

  status = sl_net_down(SL_NET_WIFI_CLIENT_INTERFACE);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to bring down Wi-Fi client interface up: 0x%lx\r\n", status);
    return;
  }

  status = sl_net_deinit(SL_NET_WIFI_CLIENT_INTERFACE, NULL);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to deinit Wi-Fi Client interface: 0x%lx\r\n", status);
    return;
  }
}

void receive_data_from_client()
{
  int server_socket                 = -1;
  int return_value                  = 0;
  struct sockaddr_in server_address = { 0 };
  socklen_t socket_length           = sizeof(struct sockaddr_in);

  server_address.sin_family = AF_INET;
  server_address.sin_port   = SERVER_PORT;
  sl_net_inet_addr(SERVER_IP, &server_address.sin_addr.s_addr);

  // Create socket
  server_socket = sl_si91x_socket_async(AF_INET, SOCK_STREAM, IPPROTO_TCP, &data_callback);
  if (server_socket < 0) {
    printf("\r\nSocket creation failed with bsd error: %d\r\n", errno);
    return;
  }
  printf("\r\nTCP Socket Create Success\r\n");

  return_value = sl_si91x_bind(server_socket, (struct sockaddr *)&server_address, socket_length);
  if (return_value < 0) {
    printf("\r\nBind failed: %d\r\n", errno);
    return;
  }
  printf("\r\nBind success\r\n");

  return_value = sl_si91x_listen(server_socket, MAX_CLIENT_COUNT);
  if (return_value < 0) {
    printf("\r\nListen failed: %d\r\n", errno);
    return;
  }
  printf("\r\nListen success\r\n");

  return_value = sl_si91x_accept_async(server_socket, &accept_async_trigger);
  if (return_value != SL_STATUS_IN_PROGRESS) {
    printf("\r\nAccept failed: %d\r\n", errno);
    return;
  }

  // check for remote terminate
  while (!is_client_accepted) {
    osThreadYield();
  }

  printf("\r\nBytes read = %ld\r\n", bytes_read);

  // Socket close
  sl_si91x_shutdown(server_socket, SHUTDOWN_BY_ID);

  printf("\r\nSocket close success\r\n");
  return;
}
