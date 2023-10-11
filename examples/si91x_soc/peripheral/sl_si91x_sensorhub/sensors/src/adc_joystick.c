/***************************************************************************/ /**
 * @file adc_joystick.c
 * @brief adc joystick sensor driver
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

#include "adc_joystick.h"
#include "sensor_hub.h"
#include "rsi_debug.h"
#include "sl_si91x_adc.h"
#include "rsi_error.h"

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
static bool is_adc_js_init    = false;
static bool is_adc_js_enabled = false;

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_joystick_init(sl_adc_channel_config_t *adc_ch_cfg, sl_adc_config_t *adc_cfg)
 * @brief     ADC joystick sensor initialization
 *            This function should be called before everything else. And ADC peripheral
 *            initialization should be done before calling this function. This function
 *            will only initliaze respective ADC channel and does not start the ADC.
 *
 * @param[in] ADC channel configuration
 * @param[in] ADC configuration
 *
 * @return    respective sl error code
*******************************************************************************/
sl_status_t sl_si91x_adc_joystick_init(sl_adc_channel_config_t *adc_ch_cfg, sl_adc_config_t *adc_cfg)
{
  sl_status_t sl_status;

  sl_status = sl_si91x_adc_channel_set_configuration(*adc_ch_cfg, *adc_cfg);
  if (sl_status == SL_STATUS_OK) {
    is_adc_js_init = true;
  }

  return sl_status;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_joystick_deinit(sl_adc_config_t *adc_cfg)
 * @brief     ADC joystick sensor deinitialization
 *            This function deinitializes respective ADC channel by clearing up the
 *            particular ADC channel configuration register.
 *
 * @param[in] ADC channel configuration
 * @param[in] ADC configuration
 *
 * @return    respective sl error code
*******************************************************************************/
sl_status_t sl_si91x_adc_joystick_deinit(sl_adc_config_t *adc_cfg)
{
  sl_status_t sl_status;
  if (is_adc_js_init != true) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  sl_status = sl_si91x_adc_deinit(*adc_cfg);

  return sl_status;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_joystick_enable(uint8_t channel)
 * @brief     ADC joystick sensor enable
 *            This function enables respective ADC channel.
 *
 * @param[in] ADC channel configuration
 * @param[in] ADC configuration
 *
 * @return    respective sl error code
*******************************************************************************/
sl_status_t sl_si91x_adc_joystick_enable(uint8_t channel)
{
  sl_status_t sl_status;
  sl_status = sl_si91x_adc_channel_enable(channel);
  if (sl_status == SL_STATUS_OK) {
    is_adc_js_enabled = true;
  }

  return sl_status;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_joystick_disable(uint8_t channel)
 * @brief     ADC joystick sensor enable
 *            This function disables respective ADC channel.
 *
 * @param[in] ADC channel configuration
 * @param[in] ADC configuration
 *
 * @return    respective sl error code
*******************************************************************************/
sl_status_t sl_si91x_adc_joystick_disable(uint8_t channel)
{
  sl_status_t sl_status;
  sl_status = sl_si91x_adc_channel_disable(channel);
  if (sl_status == SL_STATUS_OK) {
    is_adc_js_enabled = false;
  }

  return sl_status;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_joystick_read_static_data(sl_adc_channel_config_t *adc_ch_cfg,
                                                   sl_adc_config_t *adc_cfg,
                                                   uint16_t *adc_value)
 * @brief     ADC joystick sensor read static data
 *            This function reads static ADC data from the register.
 *
 * @param[in] ADC channel configuration
 * @param[in] ADC configuration
 *
 * @return    respective sl error code
*******************************************************************************/
sl_status_t sl_si91x_adc_joystick_read_static_data(sl_adc_channel_config_t *adc_ch_cfg,
                                                   sl_adc_config_t *adc_cfg,
                                                   uint16_t *adc_value)
{
  sl_status_t sl_status;

  if (is_adc_js_init != true) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  sl_status = sl_si91x_adc_read_data_static(*adc_ch_cfg, *adc_cfg, adc_value);
  if (sl_status != SL_STATUS_OK) {
    return sl_status;
  }

  if (*adc_value & BIT(11)) {
    *adc_value = (*adc_value & (ADC_MASK_VALUE));
  } else {
    *adc_value = *adc_value | BIT(11);
  }

  return sl_status;
}
