/***************************************************************************/ /**
 * @file adcsensor_hal.h
 * @brief adc sensor hal driver
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

#ifndef ADCSENSOR_HAL_H_
#define ADCSENSOR_HAL_H_
#include "sensor_type.h"
#include "sl_si91x_adc.h"

/***************************************************************************/ /**
 * Typedef for different pointer handles
 ******************************************************************************/
typedef void *sl_error_t;

typedef int32_t sl_adc_bus__error_t;

typedef void *sl_sensor_adc_handle_t;

/* Macros for sensor hub */
#define SL_CONFIG_SENSOR_ADC_INCLUDED_JOYSTICK 1

#ifdef SL_CONFIG_SENSOR_ADC_INCLUDED_JOYSTICK
#include "adc_joystick.h"
#endif

/* ADC peripheral configurations */
#define SL_ADC_PS4_SOC_FREQ          180000000 ///< PLL out clock 180MHz
#define SL_ADC_SOC_PLL_REF_FREQUENCY 32000000  ///< PLL input REFERENCE clock 32MHZ
#define SL_ADC_DVISION_FACTOR        0         ///< Division factor
#define SL_ADC_STATIC_INPUT          0         ///< ADC static input selection
#define SL_ADC_SAMPLING_RATE         10000     ///< ADC sampling rate, 1Ksps
#define SL_ADC_NUM_CHANNELS_ENABLE   1         ///< ADC number of channels enabled

/* ADC sensor 0 configurations */
#define SL_ADC_SENSOR0_P_INPUT     5 ///< ADC sensor 0 positive input selection
#define SL_ADC_SENSOR0_CHANNEL     0 ///< ADC sensor 0 channel number
#define SL_ADC_SENSOR0_OPAMP_GAIN  0 ///< ADC sensor 0 opamp gain
#define SL_ADC_SENSOR0_NUM_SAMPLES 1 ///< ADC sensor 0 number of samples

#define SL_ADC_MAX_OP_VALUE 4096 ///< Maximum voltage output value from adc, this is used to calculate input volatge
#define SL_ADC_VREF_VALUE   3.3f ///< Reference voltage

/* ADC sensor implementations per sensor */
typedef struct {
  adc_sensor_id_t channel;
  sl_status_t (*init)(sl_adc_channel_config_t *, sl_adc_config_t *);
  sl_status_t (*enable)(uint8_t);
  sl_status_t (*disable)(uint8_t);
  sl_status_t (*deinit)(sl_adc_config_t *);
  sl_status_t (*sample_adc_static)(sl_adc_channel_config_t *, sl_adc_config_t *, uint16_t *);
  sl_status_t (*sleep)(void);
  sl_status_t (*wakeup)(void);
} adc_sensor_impl_t;

/* ADC sensor hal configurations */
typedef struct {
  uint8_t channel;               ///< ADC channel number
  sl_sensor_bus_t bus;           ///< ADC bus handle configuration
  bool is_init;                  ///< Initialization check flag
  const adc_sensor_impl_t *impl; ///< Pointer to adc sensor implementation
} sensor_adc_t;

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************/ /**
 * @fn        void sl_si91x_adc_callback(UNUSED_PARAM uint8_t channel_no, UNUSED_PARAM uint8_t event)
 * @brief     ADC user callback
 *
 * @param[in] channel_no : respective channel number 
 * @param[in] channel_no : callback event (ADC_STATIC_MODE_CALLBACK, etc)
 ******************************************************************************/
void sl_si91x_adc_callback(uint8_t channel_no, uint8_t event);

/***************************************************************************/ /**
 * @fn        sl_sensor_adc_handle_t sl_si91x_adc_sensor_create(sl_adc_bus_handle_t bus, int channel)
 * @brief     ADC sensor create
 *
 * @param[in] bus : bus type (ADC)
 * @param[in] id : respective channel number
 * @return adc sensor handle
 ******************************************************************************/
sl_sensor_adc_handle_t sl_si91x_adc_sensor_create(sl_sensor_bus_t bus, int id);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_delete(sl_sensor_adc_handle_t *sensor)
 * @brief     ADC sensor delete
 *
 * @param[in] sensor : ADC sensor handle
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_delete(sl_sensor_adc_handle_t *sensor);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_sample_static(sl_sensor_adc_handle_t *sensor, uint16_t *adc_value)
 * @brief     ADC sensor read static data
 *
 * @param[in] sensor : ADC sensor handle
 * @param[in] adc_value : address to store to ADC data
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_sensor_sample_static(sl_sensor_adc_handle_t *sensor, uint16_t *adc_value);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_sleep(sl_sensor_adc_handle_t sensor)
 * @brief     ADC sensor sleep
 *
 * @param[in] sensor : ADC sensor handle
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_sensor_sleep(sl_sensor_adc_handle_t sensor);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_wakeup(sl_sensor_adc_handle_t sensor)
 * @brief     ADC sensor wakeup
 *
 * @param[in] sensor : ADC sensor handle
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_sensor_wakeup(sl_sensor_adc_handle_t sensor);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_set_power(sl_sensor_adc_handle_t sensor, sl_sensor_power_mode_t power_mode)
 * @brief     ADC sensor set power mode
 *
 * @param[in] sensor : ADC sensor handle
 * @param[in] power_mode : set ADC sensor to requested power mode
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_status_t sl_si91x_adc_sensor_set_power(sl_sensor_adc_handle_t sensor, sl_sensor_power_mode_t power_mode);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_sample(sl_sensor_adc_handle_t *sensor, sl_sensor_data_group_t *data_group)
 * @brief     ADC sensor sample
 *
 * @param[in] sensor : ADC sensor handle
 * @param[in] data_group : sensor hub data group structure that contains
 *            memory to store ADC data and number of samples
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_sample(sl_sensor_adc_handle_t sensor, sl_sensor_data_group_t *data_group);

/***************************************************************************/ /**
 * @fn        sl_status_t sl_si91x_adc_sensor_control(sl_sensor_adc_handle_t sensor, sl_sensor_command_t cmd, UNUSED_PARAM void *args)
 * @brief     ADC sensor control
 *
 * @param[in] sensor : ADC sensor handle
 * @param[in] cmd : command to change the sensor modes
 * @return status 0 if successful, else error code
 *         \ref SL_STATUS_OK (0x0000) - Success
 *         \ref SL_STATUS_NULL_POINTER (0x0022) - The parameter is null pointer
 *         \ref SL_STATUS_INVALID_PARAMETER (0x0021) - Parameters are invalid
 *         \ref SL_STATUS_FAIL (0x0001) - The function is failed
 *         \ref SL_STATUS_NOT_INITIALIZED (0x0011) - Clock is not initialized
 ******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_control(sl_sensor_adc_handle_t sensor, sl_sensor_command_t cmd, void *args);

#ifdef __cplusplus
extern "C"
}
#endif

#endif /* ADCSENSOR_HAL_H_ */
