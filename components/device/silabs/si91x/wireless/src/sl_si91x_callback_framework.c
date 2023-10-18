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
#include "sl_net_rsi_utility.h"
#include "sl_si91x_core_utilities.h"
#include "sl_si91x_driver.h"
#include "sl_si91x_constants.h"

// Define a structure to hold a callback function and user data
typedef struct {
  sl_net_event_handler_t function;
  void *user_data;
} sl_si91x_callback_entry_t;

// SL_NET_EVENT_COUNT is assumed to be a constant representing the number of network events
static sl_si91x_callback_entry_t sl_si91x_callbacks[SL_NET_EVENT_COUNT] = { 0 };

sl_status_t sl_si91x_register_callback(sl_net_event_t event, sl_net_event_handler_t function)
{
  // Check if the event is within valid bounds
  if (event >= SL_NET_EVENT_COUNT) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  sl_si91x_callback_entry_t *entry = &sl_si91x_callbacks[event];

  entry->function = function;

  return SL_STATUS_OK;
}

sl_status_t sl_si91x_default_handler(sl_net_event_t event, sl_wifi_buffer_t *buffer)
{
  sl_si91x_callback_entry_t *callback_entry = &sl_si91x_callbacks[event];
  sl_si91x_packet_t *packet                 = sl_si91x_host_get_buffer_data(buffer, 0, NULL);
  sl_status_t status                        = convert_and_save_firmware_status(get_si91x_frame_status(packet));
  sl_ip_address_t ip                        = { 0 };
  void *data;

  // Check if there's a valid callback registered for this event
  if (callback_entry == NULL || callback_entry->function == NULL) {
    return SL_STATUS_FAIL; // If no callback is registered, return failure
  }

  // Depending on the event type, prepare data for the callback
  switch (event) {
    case SL_NET_DNS_RESOLVE_EVENT: {
      data = &ip;

      // Convert the SI91x DNS response to an IP address structure
      convert_si91x_dns_response(&ip, (sl_si91x_dns_response_t *)packet->data);
      break;
    }
    case SL_NET_OTA_FW_UPDATE_EVENT:
    case SL_NET_PING_RESPONSE_EVENT:
    case SL_NET_ASYNC_MODULE_STATUS_EVENT: {
      data = &packet->data; // Use packet data directly for certain events
      break;
    }
    default: {
      return SL_STATUS_FAIL; // Return failure for unsupported events
    }
  }
  // Call the registered callback function with event details
  callback_entry->function(event, status, data, packet->length);

  return SL_STATUS_OK;
}
