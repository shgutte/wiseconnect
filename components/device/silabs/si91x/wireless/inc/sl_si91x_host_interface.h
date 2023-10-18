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

#include "sl_status.h"
#include "sl_wifi_types.h"
#include "sl_wifi_host_interface.h"
#include "sl_si91x_types.h"
#include "sl_wifi_device.h"
#include <stdbool.h>
#include <stdint.h>

void sl_si91x_host_hold_in_reset(void);      /*Function used to hold the device in reset state*/
void sl_si91x_host_release_from_reset(void); /*Function used to release the device from reset state*/

sl_status_t sl_si91x_host_init(void);   /*Function used to allocate all threads, mutexes and event handlers*/
sl_status_t sl_si91x_host_deinit(void); /*Function used to deallocate all threads, mutexes and event handlers*/

// ---------------

sl_status_t sl_si91x_host_get_credentials(
  sl_wifi_credential_id_t id,
  uint8_t type,
  sl_wifi_credential_t *cred); /*Function used to obtain wifi credential type like EsAP,PMK,etc..*/

sl_status_t sl_si91x_host_spi_transfer(const void *tx_buffer,
                                       void *rx_buffer,
                                       uint16_t buffer_length); /*Function used for data transfer between TA and MCU*/

void sl_si91x_host_enable_high_speed_bus(); /*Function used to set USART baurd rate to 20000000*/

sl_status_t sl_si91x_host_process_data_frame(sl_wifi_interface_t interface, sl_wifi_buffer_t *buffer);

void sl_si91x_host_enable_bus_interrupt(void);  /*Function used to enable the interrupt handling*/
void sl_si91x_host_disable_bus_interrupt(void); /*Function used to disable the interrupt handling*/
void sl_si91x_host_set_sleep_indicator(void);   /*Function used to set the GPIO pins associated with sleep */
void sl_si91x_host_clear_sleep_indicator(void); /*Function used to reset the GPIO pins associated with sleep*/
uint32_t sl_si91x_host_get_wake_indicator(
  void); /*Function used to read the value of pin and port associated with wake*/

/** @ */
