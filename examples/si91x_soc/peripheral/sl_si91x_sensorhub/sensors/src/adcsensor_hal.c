/***************************************************************************/ /**
 * @file adcsensor_hal.c
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

#include <stdio.h>
#include "rsi_debug.h"
#include "sensor_hub.h"
#include "sensor_type.h"
#include "sl_si91x_adc.h"
#include "adc_joystick.h"

// For unused parameter
#define UNUSED_PARAM __attribute__((unused))

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
static volatile bool adc_data_ready = false;

static sl_adc_cfg_t *adc_config;

static const adc_sensor_impl_t adc_sensor_implementations[] = {
#ifdef SL_CONFIG_SENSOR_ADC_INCLUDED_JOYSTICK
  {
    .channel           = SL_ADC_JOYSTICK_ID,
    .init              = sl_si91x_adc_joystick_init,
    .enable            = sl_si91x_adc_joystick_enable,
    .disable           = sl_si91x_adc_joystick_disable,
    .deinit            = sl_si91x_adc_joystick_deinit,
    .sample_adc_static = sl_si91x_adc_joystick_read_static_data,
    .sleep             = NULL,
    .wakeup            = NULL,
  },
#endif
};

/*******************************************************************************
 * @fn        static const adc_sensor_impl_t *find_implementation(int channel)
 * @brief     ADC find sensor implementation
 *            This function goes through the available sensor implementations and load the
 *            required implementation based on channel. One one channel is one sensor but
 *            one sensor can have multiple channels
 *
 * @param[in] ADC channel no 
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
static const adc_sensor_impl_t *find_implementation(int channel)
{
  const adc_sensor_impl_t *active_driver = NULL;
  int count                              = sizeof(adc_sensor_implementations) / sizeof(adc_sensor_impl_t);
  for (int i = 0; i < count; i++) {
    if (adc_sensor_implementations[i].channel == channel) {
      active_driver = &adc_sensor_implementations[i];
      break;
    }
  }
  return active_driver;
}

/*******************************************************************************
 * @fn        static sl_status_t adc_start(sl_adc_config_t *adc_cfg)
 * @brief     ADC start
 *            This function starts ADC peripheral
 *
 * @param[in] ADC configuration
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
static sl_status_t adc_start(sl_adc_config_t *adc_cfg)
{
  sl_status_t sl_status;
  sl_status = sl_si91x_adc_start(*adc_cfg);

  return sl_status;
}

/*******************************************************************************
 * @fn        static sl_status_t adc_stop(sl_adc_config_t *adc_cfg)
 * @brief     ADC stop
 *            This function stops ADC peripheral
 *
 * @param[in] ADC configuration
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
static sl_status_t adc_stop(sl_adc_config_t *adc_cfg)
{
  sl_status_t sl_status;
  sl_status = sl_si91x_adc_stop(*adc_cfg);

  return sl_status;
}

/*******************************************************************************
 * @fn        void sl_si91x_adc_callback(UNUSED_PARAM uint8_t channel_no, UNUSED_PARAM uint8_t event)
 * @brief     ADC user callback
 *            This function will be called from ADC interrupt handler
 *
 * @param[in] ADC channel number
 * @param[in] ADC event (SL_ADC_STATIC_MODE_EVENT, SL_INTERNAL_DMA)
 *
*******************************************************************************/
void sl_si91x_adc_callback(UNUSED_PARAM uint8_t channel_no, UNUSED_PARAM uint8_t event)
{
  if (event == SL_ADC_STATIC_MODE_EVENT) {
    adc_data_ready = true;
  }
}

/*******************************************************************************
 * @fn        sl_sensor_adc_handle_t sl_si91x_adc_sensor_create(sl_adc_bus_handle_t bus, int channel)
 * @brief     ADC sensor create
 *            This function will create ADC sensor by initializing respective sensor and
 *            then starts the ADC peripheral if not started already. We will keep is_init
 *            flag to know if particular sensor is initialized.
 *
 * @param[in] ADC bus value
 * @param[in] ADC channel (used to find respective sensor implementations)
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_sensor_adc_handle_t sl_si91x_adc_sensor_create(sl_sensor_bus_t bus, int channel)
{
  const adc_sensor_impl_t *sensor_impl = find_implementation(channel);

  if (sensor_impl == NULL) {
    DEBUGOUT("\r\n No driver founded, ADC INPUT channel = %d \r\n", channel);
    return NULL;
  }

  /* Store sensor information in the internal structure only when it is being created with run time memory allocation */
  sensor_adc_t *p_sensor = (sensor_adc_t *)pvPortMalloc(sizeof(sensor_adc_t));
  if (p_sensor == NULL) {
    DEBUGOUT("\r\n ADC sensor create failed while memory allocation:%u \r\n", sizeof(sensor_adc_t));
    return NULL;
  }
  p_sensor->channel = (uint8_t)channel;
  p_sensor->bus     = bus;
  p_sensor->impl    = sensor_impl;

  /* All other adc sensor handles will be called only after sensor_create, so we are storing the pointer to adc bus interface info here */
  adc_config = sl_si91x_fetch_adc_bus_intf_info();

  sl_status_t ret = p_sensor->impl->init(&adc_config->adc_ch_cfg, &adc_config->adc_cfg);
  if (ret != SL_STATUS_OK) {
    free(p_sensor);
    DEBUGOUT("\r\n ADC sensor init failed, channel:%d \r\n", p_sensor->channel);
    return NULL;
  } else {
    DEBUGOUT("\r\n ADC - sensor created, channel:%d \r\n", p_sensor->channel);
  }
  p_sensor->is_init = true;

  ret = adc_start(&adc_config->adc_cfg);
  if (ret != SL_STATUS_OK) {
    free(p_sensor);
    DEBUGOUT("\r\n ADC sensor start failed while initialization \r\n");
    return NULL;
  }

  return (sl_sensor_adc_handle_t)p_sensor;
}

/*******************************************************************************
 * @fn        inline sl_status_t sl_si91x_adc_sensor_enable(sensor_adc_t *p_sensor, UNUSED_PARAM int channel)
 * @brief     ADC sensor enable
 *            This function will enable the sensor by enabling respective ADC channel. Note
 *            that ADC peripheral is started as part of sensor init. And this should be 
 *            used only if you are using multiple channels
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] ADC channel number
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
inline sl_status_t sl_si91x_adc_sensor_enable(sensor_adc_t *p_sensor, UNUSED_PARAM int channel)
{
  if (p_sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sl_status_t ret = p_sensor->impl->enable(p_sensor->channel);
  if (ret != SL_STATUS_OK) {
    DEBUGOUT("\r\n ADC sensor enable failed \r\n");
    return ret;
  }

  return ret;
}

/*******************************************************************************
 * @fn        inline sl_status_t sl_si91x_adc_sensor_disable(sensor_adc_t *p_sensor, UNUSED_PARAM int channel)
 * @brief     ADC sensor disable
 *            This function will disables the sensor by disabling respective ADC channel
 *            Note that ADC peripheral will not be deinitialized here. And this should be 
 *            used only if you are using multiple channels
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] ADC channel number
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
inline sl_status_t sl_si91x_adc_sensor_disable(sensor_adc_t *p_sensor, UNUSED_PARAM int channel)
{
  if (p_sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sl_status_t ret = p_sensor->impl->disable(p_sensor->channel);
  if (ret != SL_STATUS_OK) {
    DEBUGOUT("\r\n ADC sensor disable failed \r\n");
    return ret;
  }

  return ret;
}

/******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_delete(sl_sensor_adc_handle_t *sensor)
 * @brief     ADC sensor delete
 *            This function will delete the sensor by freeing the adc sensor configurations
 *            and ADC peripheral will be stopped if no sensor is running.
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 *
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_delete(sl_sensor_adc_handle_t *sensor)
{
  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sensor_adc_t *p_sensor = (sensor_adc_t *)(*sensor);

  if (!p_sensor->is_init) {
    free(p_sensor);
    return SL_STATUS_OK;
  }

  p_sensor->is_init = false;
  sl_status_t ret   = p_sensor->impl->deinit(&adc_config->adc_cfg);
  if (ret != SL_STATUS_OK) {
    DEBUGOUT("\r\n ADC sensor deinitialization failed\r\n");
    return ret;
  }

  ret = adc_stop(&adc_config->adc_cfg);
  if (ret != SL_STATUS_OK) {
    DEBUGOUT("\r\n ADC sensor stop failed while deinitialization \r\n");
    return ret;
  }

  free(p_sensor);
  *sensor = NULL;
  return SL_STATUS_OK;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_sample_static(sl_sensor_adc_handle_t *sensor, uint16_t *adc_value)
 * @brief     ADC sensor read static data
 *            This function will sample static ADC data from the ADC_DATA register.
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] data pointer to store the ADC static value
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_status_t sl_si91x_adc_sensor_sample_static(sl_sensor_adc_handle_t *sensor, uint16_t *adc_value)
{
  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (adc_value == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  } else if (adc_data_ready == false) {
    return SL_STATUS_NOT_READY;
  }
  adc_data_ready         = false;
  sensor_adc_t *p_sensor = (sensor_adc_t *)(sensor);
  sl_status_t ret        = p_sensor->impl->sample_adc_static(&adc_config->adc_ch_cfg, &adc_config->adc_cfg, adc_value);
  return ret;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_sleep(sl_sensor_adc_handle_t sensor)
 * @brief     ADC sensor sleep
 *            This function will put ADC sensor into sleep
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_status_t sl_si91x_adc_sensor_sleep(sl_sensor_adc_handle_t sensor)
{
  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sensor_adc_t *p_sensor = (sensor_adc_t *)(sensor);
  sl_status_t ret        = p_sensor->impl->sleep();
  return ret;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_wakeup(sl_sensor_adc_handle_t sensor)
 * @brief     ADC sensor wakeup
 *            This function will wakeup ADC sensor from sleep
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_status_t sl_si91x_adc_sensor_wakeup(sl_sensor_adc_handle_t sensor)
{
  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sensor_adc_t *p_sensor = (sensor_adc_t *)(sensor);
  sl_status_t ret        = p_sensor->impl->wakeup();
  return ret;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_set_power(sl_sensor_adc_handle_t sensor, sl_sensor_power_mode_t power_mode)
 * @brief     ADC sensor set power mode
 *            This function will put sensor into requested power mode
 * 
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] power mode for sensor
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_status_t sl_si91x_adc_sensor_set_power(sl_sensor_adc_handle_t sensor, sl_sensor_power_mode_t power_mode)
{
  sensor_adc_t *p_sensor = (sensor_adc_t *)(sensor);
  sl_status_t ret        = 0;

  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (power_mode > SL_SENSOR_POWER_MAX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (power_mode) {
    case SL_SENSOR_POWER_MODE_WAKEUP:
      ret = p_sensor->impl->wakeup();
      break;
    case SL_SENSOR_POWER_MODE_SLEEP:
      ret = p_sensor->impl->sleep();
      break;
    default:
      ret = SL_STATUS_INVALID_PARAMETER;
      break;
  }
  return ret;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_sample(sl_sensor_adc_handle_t *sensor, sl_sensor_data_group_t *data_group)
 * @brief     ADC sensor sample
 *            This function will sample the respective channel ADC data.
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] data group which contains memory to store ADC data and handle
 *            number of samples
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_sample(sl_sensor_adc_handle_t sensor, sl_sensor_data_group_t *data_group)
{
  sensor_adc_t *p_sensor = (sensor_adc_t *)(sensor);
  sl_status_t ret        = 0;

  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (adc_data_ready == false) {
    return SL_STATUS_NOT_READY;
  }

  adc_data_ready = false;
  if ((p_sensor->impl->sample_adc_static) != NULL) {
    ret = p_sensor->impl->sample_adc_static(&adc_config->adc_ch_cfg,
                                            &adc_config->adc_cfg,
                                            &data_group->sensor_data[data_group->number].adc);
    if (SL_STATUS_OK != ret) {
      return ret;
    }
  }
  data_group->number++;

  return RSI_OK;
}

/*******************************************************************************
 * @fn        sl_status_t sl_si91x_adc_sensor_control(sl_sensor_adc_handle_t sensor, sl_sensor_command_t cmd, UNUSED_PARAM void *args)
 * @brief     ADC sensor control
 *            This function will control the different sensor modes
 *
 * @param[in] ADC sensor pointer which contains implementations, bus, etc.
 * @param[in] cmd to put the sensor into respective mode
 * 
 * @return    respective sl error code (SL_STATUS_OK, SL_STATUS_FAIL, ETC)
*******************************************************************************/
sl_adc_bus__error_t sl_si91x_adc_sensor_control(sl_sensor_adc_handle_t sensor,
                                                sl_sensor_command_t cmd,
                                                UNUSED_PARAM void *args)
{
  sl_status_t ret = SL_STATUS_OK;

  if (sensor == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else if (cmd > SL_COMMAND_MAX) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (cmd) {
    case SL_COMMAND_SET_MODE:
      ret = SL_STATUS_OK;
      break;
    case SL_COMMAND_SET_RANGE:
      ret = SL_STATUS_OK;
      break;
    case SL_COMMAND_SET_ODR:
      ret = SL_STATUS_OK;
      break;
    case SL_COMMAND_SET_POWER:
      ret = SL_STATUS_OK;
      break;
    case SL_COMMAND_SELF_TEST:
      ret = SL_STATUS_OK;
      break;
    default:
      ret = SL_STATUS_OK;
      break;
  }
  return ret;
}
