/***************************************************************************/ /**
 * @file adc_joystick.h
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

#ifndef ADC_JOYSTICK_H_
#define ADC_JOYSTICK_H_
#include "sl_si91x_adc.h"

/***************************************************************************/ /**
 * @addtogroup SENSOR_HUB
 * @ingroup SENSORHUB_ADC_JOYSTICK_ADC_APIS
 * @{
 ******************************************************************************/
// -----------------------------------------------------------------------------

/***************************************************************************/ /**
 * Typedef for different pointer handles
 ******************************************************************************/
typedef void *sl_err_t;
typedef void *adc_joystick_handle_t;
typedef void *adc_bus_handle_t;

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_joystick_init(sl_adc_channel_config_t *adc_ch_cfg, sl_adc_config_t *adc_cfg)
 * @brief     ADC joystick sensor initialization
 *
 * @param[in] adc_ch_cfg : ADC channel configuration
 * @param[in] adc_cfg : ADC configuration
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_joystick_init(sl_adc_channel_config_t *adc_ch_cfg, sl_adc_config_t *adc_cfg);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_joystick_deinit(sl_adc_config_t *adc_cfg)
 * @brief     ADC joystick sensor deinitialization
 *
 * @param[in] adc_cfg : ADC configuration
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_joystick_deinit(sl_adc_config_t *adc_cfg);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_joystick_enable(uint8_t channel)
 * @brief     ADC joystick sensor enable
 *
 * @param[in] channel : ADC channel number
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_joystick_enable(uint8_t channel);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_joystick_disable(uint8_t channel)
 * @brief     ADC joystick sensor enable
 *
 * @param[in] channel : ADC channel number
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_joystick_disable(uint8_t channel);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_joystick_read_static_data(sl_adc_channel_config_t *adc_ch_cfg,
                                                   sl_adc_config_t *adc_cfg,
                                                   uint16_t *adc_value)
 * @brief     ADC joystick sensor read static data
 *
 * @param[in] adc_ch_cfg : ADC channel configuration
 * @param[in] adc_cfg : ADC configuration
 * @param[in] adc_value :  memory pointer to store ADC data
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_joystick_read_static_data(sl_adc_channel_config_t *adc_ch_cfg,
                                                   sl_adc_config_t *adc_cfg,
                                                   uint16_t *adc_value);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* ADC_JOYSTICK_H_ */
