<<<<<<< HEAD:components/device/silabs/si91x/mcu/drivers/unified_api/config/sl_si91x_i2c_inst_config.h
/***************************************************************************/ /**
 * @file sl_si91x_i2c_inst_config.h
 * @brief I2c driver configuration file.
=======
/***************************************************************************//**
 * @file
 * @brief Watchdog Timer configuration file.
>>>>>>> c88d0731d (added example folder):components/siwx917_soc/drivers/unified_api/config/sl_si91x_i2c_inst_config.h
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

<<<<<<< HEAD:components/device/silabs/si91x/mcu/drivers/unified_api/config/sl_si91x_i2c_inst_config.h
#ifndef SL_I2C_INSTANCE_CONFIG_H
#define SL_I2C_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
#ifdef __cplusplus
extern "C" {
#endif

#include "sl_si91x_i2c.h"
/******************************************************************************/
/******************************* I2C Configuration **************************/
// <h> I2C INSTANCE Configuration

// <<< Use Configuration Wizard in Context Menu >>>
//<h>I2C Configuration

// <o SL_I2C_INSTANCE_NUMBER> I2C instance
//   <SL_I2C_INSTANCE_0=> I2C0
//   <SL_I2C_INSTANCE_1=> I2C1
//   <SL_I2C_INSTANCE_2=> I2C2
// <i> Selection of the I2C Instance.
#define SL_I2C_INSTANCE_NUMBER SL_I2C_INSTANCE_0

// <o SL_I2C_INSTANCE_MODE> Mode
//   <SL_I2C_LEADER_MODE=> Leader mode
//   <SL_I2C_FOLLOWER_MODE=> Follower mode
// <i> Selection of the I2C Mode.
#define SL_I2C_INSTANCE_MODE SL_I2C_LEADER_MODE

// <o SL_I2C_INSTANCE_OPERATING_MODE> Operating Mode
//   <SL_I2C_STANDARD_MODE=> Standard mode
//   <SL_I2C_FAST_MODE=> Fast mode
//   <SL_I2C_FAST_PLUS__MODE=> Fast plus mode
//   <SL_I2C_HIGH_SPEED_MODE=> High speed mode
// <i> Selection of the I2C Mode.
#define SL_I2C_INSTANCE_OPERATING_MODE SL_I2C_STANDARD_MODE

// <o SL_I2C_INSTANCE_TRANSFER_TYPE> Transfer Type
//   <SL_I2C_USING_INTERRUPT=> Using Interrupt
//   <SL_I2C_USING_DMA=> Using DMA
// <i> Selection of the I2C Mode.
#define SL_I2C_INSTANCE_TRANSFER_TYPE SL_I2C_USING_INTERRUPT

// </h> End I2C INSTANCE Configuration
/******************************************************************************/
// <<< end of configuration section >>>

#define SL_I2C_INSTANCE_SCL_PORT SL_SI91X_I2C0_SCL_PORT
#define SL_I2C_INSTANCE_SCL_PIN  SL_SI91X_I2C0_SCL_PIN
#define SL_I2C_INSTANCE_SCL_MUX  SL_SI91X_I2C0_SCL_MUX
#define SL_I2C_INSTANCE_SCL_PAD  SL_SI91X_I2C0_SCL_PAD
#define SL_I2C_INSTANCE_SCL_REN  SL_SI91X_I2C0_SCL_REN

#define SL_I2C_INSTANCE_SDA_PORT SL_SI91X_I2C0_SDA_PORT
#define SL_I2C_INSTANCE_SDA_PIN  SL_SI91X_I2C0_SDA_PIN
#define SL_I2C_INSTANCE_SDA_MUX  SL_SI91X_I2C0_SDA_MUX
#define SL_I2C_INSTANCE_SDA_PAD  SL_SI91X_I2C0_SDA_PAD
#define SL_I2C_INSTANCE_SDA_REN  SL_SI91X_I2C0_SDA_REN

#ifdef __cplusplus
}
#endif

#endif // SL_I2C_CONFIG_H
=======
#ifndef SL_SI91X_WATCHDOG_TIMER_INSTANCE_CONFIG_H
#define SL_SI91X_WATCHDOG_TIMER_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
>>>>>>> c88d0731d (added example folder):components/siwx917_soc/drivers/unified_api/config/sl_si91x_i2c_inst_config.h
