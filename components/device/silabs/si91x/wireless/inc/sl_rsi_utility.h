/***************************************************************************/ /**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#pragma once

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "sl_status.h"
#include "sl_constants.h"
#include "sl_si91x_host_interface.h"
#include "sl_si91x_protocol_types.h"
#include "sl_utility.h"
#include "sl_si91x_driver.h"
#include "sl_wifi_device.h"

#define NCP_HOST_DATA_TX_EVENT           (1 << 1) // Notify there is something to transmit
#define NCP_HOST_BUS_RX_EVENT            (1 << 2) // Triggered by IRQ to indicate something to read
#define NCP_HOST_COMMON_RESPONSE_EVENT   (1 << 3) // Indicates RX response received for COMMON command type
#define NCP_HOST_WLAN_RESPONSE_EVENT     (1 << 4) // Indicates synchronous RX response received for WLAN command type
#define NCP_HOST_WLAN_NOTIFICATION_EVENT (1 << 5) // Indicates asynchronous RX response received for WLAN command type
#define NCP_HOST_NETWORK_RESPONSE_EVENT  (1 << 6) // Indicates synchronous RX response received for NETWORK command type
#define NCP_HOST_NETWORK_NOTIFICATION_EVENT \
  (1 << 7)                                      // Indicates asynchronous RX response received for NETWORK command type
#define NCP_HOST_SOCKET_RESPONSE_EVENT (1 << 8) // Indicates RX response received for SOCKET command type
#define NCP_HOST_SOCKET_NOTIFICATION_EVENT \
  (1 << 9)                                   // Indicates asynchronous RX response received for SOCKET command type
#define NCP_HOST_BT_RESPONSE_EVENT (1 << 10) // Indicates RX response received for BLE command type

typedef struct {
  sl_wifi_performance_profile_t wifi_performance_profile;
  sl_bt_performance_profile_t bt_performance_profile;
  sl_si91x_coex_mode_t coex_mode;
} sl_si91x_performance_profile_t;

typedef uint32_t sl_si91x_host_timestamp_t;

typedef void (*sl_si91x_host_atomic_action_function_t)(void *user_data);
typedef bool (*sl_si91x_compare_function_t)(sl_wifi_buffer_t *node, void *user_data);
typedef void (*sl_si91x_node_free_function_t)(sl_wifi_buffer_t *node);

extern sl_performance_profile_t current_performance_profile; /*Indicates the current performance profile*/

sl_status_t convert_si91x_wifi_client_info(
  sl_wifi_client_info_response *client_info_response,
  sl_si91x_client_info_response *sl_si91x_client_info_response); /*Function converts TA client info to SDK client info*/
sl_wifi_event_t convert_si91x_event_to_sl_wifi_event(
  rsi_wlan_cmd_response_t command,
  uint16_t frame_status); /*Function converts TA events to SDK events*/

sl_status_t save_sl_wifi_rate(
  sl_wifi_rate_t transfer_rate); /*Function used to update the variable that stores the wifi rate*/
sl_status_t get_saved_sl_wifi_rate(sl_wifi_rate_t *transfer_rate); /*Function used to retrieve the wifi rate*/
void reset_sl_wifi_rate(); /*Function used to set wifi rate to default value of 1 Mbps*/

sl_status_t get_rate_protocol_and_data_rate(
  const uint8_t data_rate,
  sl_wifi_rate_protocol_t *rate_protocol,
  sl_wifi_rate_t *transfer_rate); /*Function used to retrieve protocol and transfer rate*/

sl_status_t save_ap_configuration(
  const sl_wifi_ap_configuration_t *wifi_ap_configuration); /*Function used to update the access point configuration*/
sl_status_t get_saved_ap_configuration(
  sl_wifi_ap_configuration_t *wifi_ap_confuguration); /*Function used to retrieve the access point configuration*/
void reset_ap_configuration(); /*Function used to destroy the current access point configuration*/

void save_tcp_auto_close_choice(
  bool is_tcp_auto_close_enabled); /*Function used to set whether tcp auto close is enabled or disabled*/
bool is_tcp_auto_close_enabled();  /*Function used to check whether tcp auto close is enabled or disabled*/
void set_card_ready_required(bool card_ready_required); /*Function used to set whether card ready is required or not*/
bool get_card_ready_required();                         /*Function used to check whether card ready is required or not*/

void save_max_tx_power(uint8_t max_tx_power); /*Function used to set the maximum transmission power*/
uint8_t get_max_tx_power();                   /*Function used to get maximum transmission power*/
void reset_max_tx_power();                    /*Function used to set maximum transmission power to 0 */

void save_wifi_current_performance_profile(
  const sl_wifi_performance_profile_t *profile); /*Function used to set the current performance profile*/
void get_wifi_current_performance_profile(
  sl_wifi_performance_profile_t *profile); /*Function used to get current wifi performance profile*/

void save_bt_current_performance_profile(
  const sl_bt_performance_profile_t *profile); /*Function used to set the bluetooth performance profile*/
void get_bt_current_performance_profile(
  sl_bt_performance_profile_t *profile); /*Function used to retrieve bluetooth performance profile*/

void get_coex_performance_profile(
  sl_performance_profile_t *profile);              /*Function used to retrieve the coex performance profile*/
void reset_coex_current_performance_profile(void); /*Function used to zero out the coex performance profile */

void save_boot_configuration(
  const sl_si91x_boot_configuration_t *boot_configuration); /*Function used to update the boot configuration*/
void get_saved_boot_configuration(
  sl_si91x_boot_configuration_t *boot_configuration); /*Function used to retrieve the boot configuration*/

void save_coex_mode(sl_si91x_coex_mode_t coex_mode); /*Function used to update the coex mode*/
sl_si91x_coex_mode_t get_coex_mode(void);            /*Function used to retrieve the coex mode*/

sl_status_t convert_sl_wifi_to_sl_si91x_encryption(
  sl_wifi_encryption_t encryption_mode,
  uint8_t *encryption_request); /*Function converts SDK encryption mode to TA supported mode*/

/*********************************************************************************************
 * @brief
 * 	 An utility function computes coex performance profile internally and converts into sl_si91x_power_save_request_t.
 * @param profile
 *   performance profile which needs to be converted to its equivalent si91x_power_save_request structure.
 * @param power_save_request
 *   si91x specific structure that holds required configuration for the given performance profile.
 *   This is optional parameter.
 * @return coex_profile
 *   Coex power profile
 * @return
 * 	 sl_status_t
 *********************************************************************************************/
sl_status_t sl_si91x_send_power_save_request(sl_performance_profile_t profile);

/**
 * An utility function to convert dBm value  to si91x specific power value
 * @param power_value_in_dbm power value with dBm as units.
 * @return si91x power level
 */
static inline uint8_t convert_dbm_to_si91x_power_level(uint8_t power_value_in_dBm)
{
  if (power_value_in_dBm >= SI91X_LOW_TRANSMIT_POWER_THRESHOLD) {
    return SL_SI91X_LOW_POWER_LEVEL;
  } else if (power_value_in_dBm >= SI91X_MEDIUM_TRANSMIT_POWER_THRESHOLD) {
    return SL_SI91X_MEDIUM_POWER_LEVEL;
  } else {
    return SL_SI91X_HIGH_POWER_LEVEL;
  }
}

sl_status_t sl_si91x_platform_init(void);
sl_status_t sl_si91x_platform_deinit(void);
void sl_si91x_host_delay_ms(uint32_t delay_milliseconds);    /*Function used to block MCU for specified time*/
sl_si91x_host_timestamp_t sl_si91x_host_get_timestamp(void); /*Function provides the timestamp at the instance*/
sl_si91x_host_timestamp_t sl_si91x_host_elapsed_time(
  uint32_t starting_timestamp); /*Function used to calculate the timestamp difference*/

// Event API
void sl_si91x_host_set_event(uint32_t event_mask);       /*Function used to set specified flags for event*/
void sl_si91x_host_set_bus_event(uint32_t event_mask);   /*Function used to set specified flags for event*/
void sl_si91x_host_set_async_event(uint32_t event_mask); /*Function used to set specified flags for event*/
uint32_t si91x_host_wait_for_event(uint32_t event_mask,
                                   uint32_t timeout); /*Function used to wait for specific event to occur*/
uint32_t si91x_host_wait_for_bus_event(uint32_t event_mask,
                                       uint32_t timeout); /*Function used to wait for specific event to occur*/
uint32_t si91x_host_wait_for_async_event(uint32_t event_mask,
                                         uint32_t timeout);  /*Function used to wait for specific event to occur*/
uint32_t si91x_host_clear_events(uint32_t event_mask);       /*Function used to clear flags for specific event*/
uint32_t si91x_host_clear_bus_events(uint32_t event_mask);   /*Function used to clear flags for specific event*/
uint32_t si91x_host_clear_async_events(uint32_t event_mask); /*Function used to clear flags for specific event*/

sl_status_t sl_si91x_host_allocate_buffer(sl_wifi_buffer_t **buffer,
                                          sl_wifi_buffer_type_t type,
                                          uint32_t buffer_size,
                                          uint32_t wait_duration_ms); /*Function used to allocate memory*/
void *sl_si91x_host_get_buffer_data(
  sl_wifi_buffer_t *buffer,
  uint16_t offset,
  uint16_t *data_length); /*Function used to obtain pointer to a specified location in the buffer*/
void sl_si91x_host_free_buffer(
  sl_wifi_buffer_t *buffer,
  sl_wifi_buffer_type_t type); /*Function used to deallocate the memory associated with buffer*/
// ---------------

sl_status_t sl_si91x_host_add_to_queue(
  sl_si91x_queue_type_t queue,
  sl_wifi_buffer_t *buffer); /*Function enqueues response into corresponding response queue*/
sl_status_t sl_si91x_host_add_to_queue_with_atomic_action(
  sl_si91x_queue_type_t queue,
  sl_wifi_buffer_t *buffer,
  void *user_data,
  sl_si91x_host_atomic_action_function_t handler); /*Function enqueues command into corresponding command queue*/
sl_status_t sl_si91x_host_remove_from_queue(
  sl_si91x_queue_type_t queue,
  sl_wifi_buffer_t **buffer); /*Function dequeues responses from Asynch response queues*/
sl_status_t sl_si91x_host_remove_node_from_queue(
  sl_si91x_queue_type_t queue,
  sl_wifi_buffer_t **buffer,
  void *user_data,
  sl_si91x_compare_function_t compare_function); /*Function dequeues response from Synch response queues*/
/* Function used to flush the pending TX packets from the specified queue */
sl_status_t sl_si91x_host_flush_nodes_from_queue(sl_si91x_queue_type_t queue,
                                                 void *user_data,
                                                 sl_si91x_compare_function_t compare_function,
                                                 sl_si91x_node_free_function_t node_free_function);
uint32_t sl_si91x_host_queue_status(
  sl_si91x_queue_type_t queue); /*Function used to check whether queue is empty or not*/

// These aren't host APIs. These should go into a wifi bus API header
sl_status_t sl_si91x_bus_read_memory(
  uint32_t addr,
  uint16_t length,
  uint8_t *buffer); /*Function used to set buffer pointer to point to specified memory address*/
sl_status_t sl_si91x_bus_write_memory(
  uint32_t addr,
  uint16_t length,
  const uint8_t *buffer); /*Function used to set specified memory address to point to buffer*/
sl_status_t sl_si91x_bus_read_register(uint8_t address,
                                       uint8_t register_size,
                                       uint16_t *output); /*Function used to read contents of the register*/
sl_status_t sl_si91x_bus_write_register(uint8_t address,
                                        uint8_t register_size,
                                        uint16_t data);         /*Function used to write data into register*/
sl_status_t sl_si91x_bus_read_frame(sl_wifi_buffer_t **buffer); /*Function used to read frame*/
sl_status_t sl_si91x_bus_write_frame(sl_si91x_packet_t *packet,
                                     const uint8_t *payloadparam,
                                     uint16_t size_param); /*Function used to write frames*/

sl_status_t sl_si91x_bus_init();              /*Function used to check the bus availability */
sl_status_t sl_si91x_bus_enable_high_speed(); /*Function used to start DMA channels for transmission and reception*/
sl_status_t sl_si91x_bus_read_interrupt_status(
  uint16_t *interrupt_status);                              /*Function used to read the interrupt register*/
sl_status_t sl_si91x_bus_set_interrupt_mask(uint32_t mask); /*Function used to block specified interrupts*/

void sl_si91x_ulp_wakeup_init(void); /*Function used to initialize SPI interface on ulp wakeup*/

sl_status_t sl_si91x_semaphore_wait(sl_si91x_semaphore_handle_t *semaphore,
                                    uint32_t timeout_ms);                    /*Function used to wait for the semaphore*/
sl_status_t sl_si91x_semaphore_post(sl_si91x_semaphore_handle_t *semaphore); /*Function used to release the semaphore*/
sl_status_t sl_si91x_semaphore_create(sl_si91x_semaphore_handle_t *semaphore,
                                      uint32_t count); /*Function used to create a Semaphore with sepcified count*/