/***************************************************************************/ /**
 * @file
 * @brief User Gain Table Example Application
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <string.h>
#include "sl_status.h"
#include "cmsis_os2.h"
#include "sl_wifi.h"
#include "sl_net.h"
#include "sl_ip_types.h"
#include "sl_utility.h"
#include "sl_net_si91x.h"
#include "errno.h"
#include "sl_net_wifi_types.h"
#include "sl_wifi_callback_framework.h"
#include "sl_si91x_driver.h"
#ifdef RSI_M4_INTERFACE
#include "rsi_rom_clks.h"
#endif
const sl_wifi_data_rate_t rate = SL_WIFI_DATA_RATE_6;

//! Bandwidth 0 = 20Mhz, 1 = 40Mhz
#define SL_WIFI_BANDWIDTH_20MHz 0
#define SL_WIFI_BANDWIDTH_40MHz 1

//! Select bandwidth either 20Mhz or 40Mhz
#define BANDWIDTH SL_WIFI_BANDWIDTH_20MHz

//! Select band
#define BAND SL_SI91X_WIFI_BAND_2_4GHZ

#if (BAND == SL_SI91X_WIFI_BAND_2_4GHZ)
#define BAND_VALUE 1
#elif (BAND == SL_SI91X_WIFI_BAND_5GHZ)
#define BAND_VALUE 2
#endif

#ifndef MARS_ANTENNA
#if (BAND == SL_SI91X_WIFI_BAND_2_4GHZ)
#if (BANDWIDTH == SL_WIFI_BANDWIDTH_20MHz)
uint8_t gain_table_payload[] = { 3,  0,  13, 1,  34, 20, 20,  2,  34, 28, 28, 3,  34,  32, 32, 4,  34,
                                 36, 36, 5,  34, 38, 38, 6,   34, 40, 40, 7,  34, 38,  38, 8,  34, 36,
                                 36, 9,  34, 32, 32, 10, 34,  32, 32, 11, 34, 24, 24,  12, 34, 16, 24,
                                 13, 34, 12, 12, 2,  17, 255, 20, 16, 16, 4,  17, 255, 26, 20, 20 };
#endif
#elif (BAND == SL_SI91X_WIFI_BAND_5GHZ)
#if (BANDWIDTH == SL_WIFI_BANDWIDTH_20MHz)
uint8_t gain_table_payload[] = { 2, 0, 6, 1, 9, 10, 2, 8,  9, 100, 4,  4, 3, 6, 8, 149, 3, 3,
                                 4, 6, 7, 2, 4, 1,  9, 10, 2, 8,   10, 3, 6, 8, 4, 6,   7 };
#elif (BANDWIDTH == SL_WIFI_BANDWIDTH_40MHz)
uint8_t gain_table_payload[] = { 2,   0, 8, 1, 9, 10, 62, 8, 9, 2, 8,  9, 102, 4,  4, 134, 6, 8, 3, 6, 8,
                                 151, 3, 3, 4, 6, 7,  2,  4, 1, 9, 10, 2, 8,   10, 3, 6,   8, 4, 6, 7 };
#endif
#endif
#else
#if (BAND == SL_SI91X_WIFI_BAND_2_4GHZ)
#if (BANDWIDTH == SL_WIFI_BANDWIDTH_20MHz)
//M7DB - MARS ANTENNA
uint8_t gain_table_payload[] = { 3,  FCC, 0xD, 1,  28,    32,   30,  2,  28, 32, 30,  3,    28,  32, 30, 4,  30,
                                 28, 34,  5,   30, 28,    34,   6,   30, 28, 34, 7,   30,   28,  34, 8,  30, 28,
                                 34, 9,   28,  30, 30,    10,   28,  30, 30, 11, 28,  30,   30,  12, 28, 30, 30,
                                 13, 28,  30,  30, TELEC, 0x11, 255, 20, 16, 16, KCC, 0x11, 255, 26, 20, 20 };
#endif
#elif (BAND == SL_SI91X_WIFI_BAND_5GHZ)
#if (BANDWIDTH == SL_WIFI_BANDWIDTH_20MHz)
uint8_t gain_table_payload[] = { 2, FCC, 0x6, 1,     12,  12, 2, 11, 11, 100, 10, 12, 3, 13, 13, 140, 10, 11,
                                 4, 13,  13,  TELEC, 0x4, 1,  9, 10, 2,  8,   10, 3,  6, 8,  4,  6,   7 };
#elif (BANDWIDTH == SL_WIFI_BANDWIDTH_40MHz)
uint8_t gain_table_payload[] = { 2,   FCC, 0x8, 1, 9,  9,  62,    8,   8, 2, 9,  9, 102, 9,  9, 134, 12, 12, 3, 10, 10,
                                 151, 11,  11,  4, 11, 11, TELEC, 0x4, 1, 9, 10, 2, 8,   10, 3, 6,   8,  4,  6, 7 };
#endif
#endif
#endif

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

sl_si91x_request_tx_test_info_t tx_test_info = {
  .enable      = 1,
  .power       = 127,
  .rate        = rate,
  .length      = 1000,
  .mode        = 0,
  .channel     = 1,
  .aggr_enable = 0,
#ifdef CHIP_917
  .enable_11ax            = 0,
  .coding_type            = 0,
  .nominal_pe             = 0,
  .UL_DL                  = 0,
  .he_ppdu_type           = 0,
  .beam_change            = 0,
  .BW                     = 0,
  .STBC                   = 0,
  .Tx_BF                  = 0,
  .GI_LTF                 = 0,
  .DCM                    = 0,
  .NSTS_MIDAMBLE          = 0,
  .spatial_reuse          = 0,
  .BSS_color              = 0,
  .HE_SIGA2_RESERVED      = 0,
  .RU_ALLOCATION          = 0,
  .N_HELTF_TOT            = 0,
  .SIGB_DCM               = 0,
  .SIGB_MCS               = 0,
  .USER_STA_ID            = 0,
  .USER_IDX               = 0,
  .SIGB_COMPRESSION_FIELD = 0,
#endif
};

/******************************************************
 *               Function Declarations
 ******************************************************/

static void application_start(void *argument);

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

  status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &sl_wifi_transmit_test_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start Wi-Fi client interface: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWi-Fi Init Done \r\n");

  status = sl_wifi_set_antenna(SL_WIFI_CLIENT_2_4GHZ_INTERFACE, SL_WIFI_ANTENNA_EXTERNAL);
  if (status != SL_STATUS_OK) {
    printf("Failed to start set Antenna, Error Code: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nAntenna Command Frame Success \r\n");

  status = sl_wifi_update_gain_table(BAND_VALUE, BANDWIDTH, gain_table_payload, sizeof(gain_table_payload));
  if (status != SL_STATUS_OK) {
    printf("Failed to update gain table, Error Code: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nUpdate gain table Success \r\n");

  status = sl_si91x_transmit_test_start(&tx_test_info);

  if (status != SL_STATUS_OK) {
    printf("\r\nTransmit test start Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  printf("\r\nTransmit test start Success\r\n");

  // Add delay here to see the TX packets on AIR
  osDelay(1000);

  status = sl_si91x_transmit_test_stop();
  if (status != SL_STATUS_OK) {
    printf("\r\nTransmit test stop Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  printf("\r\nTransmit test stop Success\r\n");

  return;
}
