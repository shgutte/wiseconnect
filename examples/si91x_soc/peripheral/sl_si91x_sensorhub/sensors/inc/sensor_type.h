/***************************************************************************/ /**
 * @file sensor_type.h
 * @brief Sensor data
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

#ifndef SENSOR_TYPE_H_
#define SENSOR_TYPE_H_
#include <stdint.h>

/*******************************************************************************
 ***************** Sensor data Unions/Structure variables  *********************
 ******************************************************************************/
//Accelerometer sensor data
typedef union {
  struct {
    float x;
    float y;
    float z;
  };
  float axis[3];
} sl_axis3_t;
#define SL_AXIS3_T axis3_t
#endif
//Accelerometer sensor axis data
#ifndef AXIS_T
typedef struct {
  float x;
  float y;
  float z;
} sl_axis_t;
#define AXIS_T sl_axis_t
#endif

//Sensor RGBW data
#ifndef SL_RGBW_T
typedef struct {
  float r;
  float g;
  float b;
  float w;
} sl_rgbw_t;
#define SL_RGBW_T sl_rgbw_t
#endif

//Sensor UV data
#ifndef SL_UV_T
typedef struct {
  float uv;
  float uva;
  float uvb;
} sl_uv_t;
#define SL_UV_T sl_uv_t

//Sensor operations
typedef enum {
  SL_COMMAND_SET_MODE,
  SL_COMMAND_SET_RANGE,
  SL_COMMAND_SET_ODR,
  SL_COMMAND_SET_POWER,
  SL_COMMAND_SELF_TEST,
  SL_COMMAND_MAX
} sl_sensor_command_t;

//Sensor operations mode
typedef enum { SL_SENSOR_POWER_MODE_WAKEUP, SL_SENSOR_POWER_MODE_SLEEP, SL_SENSOR_POWER_MAX } sl_sensor_power_mode_t;

//Sensor operations range
typedef enum {
  SL_RANGE_DEFAULT,
  SL_RANGE_MIN,
  SL_RANGE_MEDIUM,
  SL_RANGE_MAX,
} sl_sensor_range_t;

//Sensor data group
typedef struct {
  int64_t timestamp;       /*!< timestamp  */
  uint32_t min_delay;      /*!<  minimum delay between two events, unit: ms */
  float proximity;         /*!< Distance.            unit: centimeters  */
  char gesture;            /*!< Gesture sensor.      unit: 1            */
  sl_rgbw_t rgbw;          /*!< Color.               unit: lux          */
  sl_axis_t accelerometer; /*!< Accelerometer.       unit: G           */
  union {
    sl_axis3_t gyro;   /*!< Gyroscope.           unit: dps         */
    sl_axis3_t mag;    /*!< Magnetometer.        unit: Gauss       */
    float temperature; /*!< Temperature.         unit: dCelsius     */
    float humidity;    /*!< Relative humidity.   unit: percentage   */
    float baro;        /*!< Pressure.            unit: pascal (Pa)  */
    float light;       /*!< Light.               unit: lux          */
    sl_uv_t uv;        /*!< ultraviole           unit: lux          */
    float hr;          /*!< Heat rate.           unit: HZ           */
    float tvoc;        /*!< TVOC.                unit: permillage   */
    float noise;       /*!< Noise Loudness.      unit: HZ           */
    float step;        /*!< Step sensor.         unit: 1            */
    float force;       /*!< Force sensor.        unit: mN           */
    float current;     /*!< Current sensor       unit: mA           */
    float voltage;     /*!< Voltage sensor       unit: mV           */
    float data[4];     /*!< for general use */
    uint16_t *adc;     /*!< ADC output           unit: mV           */
  };
} sl_sensor_data_t;

//Sensor data group structure
typedef struct {
  uint8_t number;                /*!< effective data number */
  sl_sensor_data_t *sensor_data; /*!< data buffer */
} sl_sensor_data_group_t;

#endif
