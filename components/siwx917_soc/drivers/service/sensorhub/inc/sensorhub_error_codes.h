/***************************************************************************/ /**
* @file sensorhub_error_codes.h
* @brief sensorhub_error_codes example
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

#ifndef ERROR_CODES_H_
#define ERROR_CODES_H_

/* ERROR CODES */

/****************************ERRORS MASK******************************/

#define SL_SH_SENSORHUB_ERRORS_MASK 0

/****************************TIMER ERRORS******************************/

#define SL_SH_CREATE_TIMER_FAIL (1 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_DELETE_TIMER_FAIL (2 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_START_TIMER_FAIL  (3 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_STOP_TIMER_FAIL   (4 << SL_SH_SENSORHUB_ERRORS_MASK)

/****************************SENSORHUB ERRORS******************************/

#define SL_SH_MAX_SENSORS_REACHED             (5 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_MEMORY_LIMIT_EXCEEDED           (6 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_SENSOR_CREATE_FAIL              (7 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_COMMAND_SET_POWER_FAIL          (8 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_COMMAND_SET_RANGE_FAIL          (9 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_COMMAND_SELF_TEST_FAIL          (10 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_INVALID_PARAMETERS              (11 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_GPIO_OUT_OF_RANGE               (12 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_SENSOR_IMPLEMENTATION_NOT_FOUND (13 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_INTERRUPT_TYPE_CONFIG_FAIL      (14 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_FAILED_TO_ALLOCATE_MEMORY       (15 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_SENSOR_INDEX_NOT_FOUND          (0xFF)

/****************************SENSOR CONFIGURATION ERRORS******************************/

#define SL_SH_CONFIG_NOT_FOUND      (16 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_INVALID_ADDRESS       (17 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_WRONG_INTERRUPT_TYPE  (18 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_INVALID_MODE          (19 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_INVALID_DELIVERY_MODE (20 << SL_SH_SENSORHUB_ERRORS_MASK)

/****************************HAL ERRORS******************************/

#define SL_SH_HAL_CREATE_SENSOR_FAIL  (21 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_HAL_DELETE_SENSOR_FAIL  (22 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_HAL_SAMPLE_SENSOR_FAIL  (23 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_HAL_CONTROL_SENSOR_FAIL (24 << SL_SH_SENSORHUB_ERRORS_MASK)

/******************************Blocking Errors********************************/

#define SL_SH_POWER_TASK_CREATE_FAIL  (25 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_SENSOR_TASK_CREATE_FAIL (26 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_SH_EM_TASK_CREATE_FAIL     (27 << SL_SH_SENSORHUB_ERRORS_MASK)
#define SL_ALL_PERIPHERALS_INIT_FAIL  (28 << SL_SH_SENSORHUB_ERRORS_MASK)

#define SL_DRIVER_OK ARM_DRIVER_OK ///< Operation succeeded

#endif