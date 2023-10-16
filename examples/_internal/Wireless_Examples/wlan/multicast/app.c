/***************************************************************************/ /**
 * @file
 * @brief Multicast Application
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
#define SERVER_PORT       6001
#define DEVICE_PORT       6001
#define MAX_CLIENT_COUNT  1
#define NUMBER_OF_PACKETS 1000
#define RECV_BUFFER_SIZE  100
#define CLIENT_MESSAGE    "WIFISDK"

//! Multicast group IP address
#define MULTICAST_GROUP_ADDRESS "224.0.0.1" /* 0x010000E0 */

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

sl_ip_address_t ip_address           = { 0 };
sl_net_wifi_client_profile_t profile = { 0 };
uint32_t packet_count                = 0;
uint32_t recv_size                   = 0;

//! Multicast group address
sl_ip_address_t multicast_ip = { 0 };

/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
void send_and_recieve_data_to_and_from_server();
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

  multicast_ip.type = SL_IPV4;
  sl_net_inet_addr((const char *)MULTICAST_GROUP_ADDRESS, &multicast_ip.ip.v4.value);

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

  status = sl_net_join_multicast_address(SL_NET_WIFI_CLIENT_INTERFACE, (const sl_ip_address_t *)&multicast_ip);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to Join Multicast address: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nJoined Multicast address successfully.\r\n");

  send_and_recieve_data_to_and_from_server();

  status = sl_net_leave_multicast_address(SL_NET_WIFI_CLIENT_INTERFACE, (const sl_ip_address_t *)&multicast_ip);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to leave Multicast address: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nLeft Multicast address successfully.\r\n");

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

void send_and_recieve_data_to_and_from_server()
{
  int server_socket                     = -1;
  int return_value                      = 0;
  int32_t received_bytes                = 0;
  uint8_t recv_buffer[RECV_BUFFER_SIZE] = { 0 }; //! buffer to receive data over UDP server socket

  struct sockaddr_in client_address = { 0 };
  struct sockaddr_in server_address = { 0 };
  client_address.sin_family         = AF_INET;
  client_address.sin_port           = DEVICE_PORT;
  server_address.sin_family         = AF_INET;
  server_address.sin_port           = SERVER_PORT;
  socklen_t socket_length           = sizeof(struct sockaddr_in);

  sl_net_inet_addr((const char *)MULTICAST_GROUP_ADDRESS, &client_address.sin_addr.s_addr);

  // Create socket
  server_socket = sl_si91x_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (server_socket < 0) {
    printf("\r\nSocket creation failed with bsd error: %d\r\n", errno);
    return;
  }
  printf("\r\nUDP socket created successfully\r\n");

  return_value = sl_si91x_bind(server_socket, (struct sockaddr *)&server_address, socket_length);
  if (return_value < 0) {
    printf("\r\nBind failed: %d\r\n", errno);
    return;
  }
  printf("\r\nBind successful, Starting sending data to server\r\n");

  while (packet_count < NUMBER_OF_PACKETS) {
    return_value = sl_si91x_sendto(server_socket,
                                   (uint8_t *)CLIENT_MESSAGE,
                                   strlen(CLIENT_MESSAGE),
                                   0,
                                   (const struct sockaddr *)&client_address,
                                   sizeof(client_address));

    if (return_value <= 0) {
      printf("\r\n Send failed \r\n");
      return;
    }
    packet_count++;
  }
  printf("\r\nSent data successfully, Starting receiving data from server \r\n");
  packet_count = 0;

  while (packet_count < NUMBER_OF_PACKETS) {
    recv_size = RECV_BUFFER_SIZE;
    do {
      //! Receive data on socket
      received_bytes =
        sl_si91x_recvfrom(server_socket, recv_buffer, recv_size, 0, (struct sockaddr *)&client_address, &socket_length);
      if (received_bytes < 0) {
        printf("\r\nReceive failed with bsd error: %d\r\n", errno);
        sl_si91x_shutdown(server_socket, SHUTDOWN_BY_ID);
        printf("\r\nSocket closed successfully\r\n");
        return;
      }
      recv_size -= received_bytes; //! subtract received bytes
    } while (recv_size > 0);
    packet_count++;
  }
  printf("\r\nData received successfully\r\n");

  // Socket close
  sl_si91x_shutdown(server_socket, SHUTDOWN_BY_ID);
  printf("\r\nSocket closed successfully\r\n");

  return;
}
