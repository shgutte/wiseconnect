/***************************************************************************/ /**
 * @file
 * @brief System Real Time Counter (SYSRTC) Peripheral API
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "rsi_sysrtc.h"
#if defined(SI91X_SYSRTC_COUNT) && (SI91X_SYSRTC_COUNT > 0)

#include "stddef.h"

/***************************************************************************/ /**
 * @addtogroup sysrtc SYSRTC - System Real Time Counter
 * @brief System Real Time Counter (SYSRTC) Peripheral API
 * @details
 *  This module contains functions to control the SYSRTC peripheral of Silicon
 *  Labs 32-bit MCUs and SoCs. The SYSRTC ensures timekeeping in low energy modes.
 * @{
 ******************************************************************************/

/***************************************************************************/ /**
 * Initializes SYSRTC module.
 ******************************************************************************/
void rsi_sysrtc_init(const rsi_sysrtc_config_t *p_config)
{
  // Wait to be ready
  rsi_sysrtc_wait_ready();

  if (SYSRTC0->EN == SYSRTC_EN_EN) {
    // Disable the module
    rsi_sysrtc_disable();
    // Wait to be ready
    rsi_sysrtc_wait_ready();
  }

  // Set configuration
  SYSRTC0->CFG = (p_config->enable_debug_run ? 1UL : 0UL) << _SYSRTC_CFG_DEBUGRUN_SHIFT;
}

/***************************************************************************/ /**
 * Initialise the clocks for  SYSRTC module.
 ******************************************************************************/
void rsi_sysrtc_clk_set(rsi_sysrtc_clk_inp_t sysrtc_clk, uint32_t div)
{
  MCU_AON->MCUAON_KHZ_CLK_SEL_POR_RESET_STATUS_b.SYSRTC_32KHZ_RC_CLK_DIV_FACTOR = div;

  MCU_AON->MCUAON_KHZ_CLK_SEL_POR_RESET_STATUS_b.AON_KHZ_CLK_SEL_SYSRTC = sysrtc_clk;

  while (MCU_AON->MCUAON_KHZ_CLK_SEL_POR_RESET_STATUS_b.AON_KHZ_CLK_SEL_CLOCK_SWITCHED_SYSRTC != 1) {
  }
}

/***************************************************************************/ /**
 * Configures SYSRTC Input and Ouput GPIO setting.
 ******************************************************************************/
void rsi_sysrtc_set_gpio(const bool set_gpio)
{
  SYSRTC0->MCUSYSRTC_REG1 = set_gpio ? 0x0UL : 0x01UL;
}

/***************************************************************************/ /**
 * Configures SYSRTC Input(Capture) from register
 ******************************************************************************/
void rsi_sysrtc_set_capture_reg(const uint32_t group)
{
  // Wait for synchronisation to be done
  uint32_t val;
  switch (group) {
    case 0:
      val = SYSRTC_GRP0_CAP_INPUT_SET;
      break;
    case 1:
      val = SYSRTC_GRP1_CAP_INPUT_SET;
      break;
    default:
      val = 0;
      break;
  }
  SYSRTC0->MCUSYSRTC_REG1 |= val;
}

/***************************************************************************/ /**
 * Configures SYSRTC Input(Capture) from gpio
 ******************************************************************************/
void rsi_sysrtc_set_capture_gpio(const uint32_t group)
{
  switch (group) {
    case 0:
      MCU_RET->NPSS_GPIO_CNTRL[0].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x03UL;
      // Group 0 input can be changed from two different pins.
      //  MCU_RET->NPSS_GPIO_CNTRL[1].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x04UL;

      break;
    case 1:
      MCU_RET->NPSS_GPIO_CNTRL[0].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x05UL;
      break;
    default:

      break;
  }
}

/***************************************************************************/ /**
 * Configures SYSRTC Input(Capture) from gpio
 ******************************************************************************/
void rsi_sysrtc_set_compare_gpio(const uint32_t group, const uint32_t chan)
{
  switch (group) {
    case 0:
      switch (chan) {
        case 0:
          MCU_RET->NPSS_GPIO_CNTRL[3].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x03UL;
          // Group 0 output can be viewed from two different pins.
          //  MCU_RET->NPSS_GPIO_CNTRL[4].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x04UL;
          break;
        case 1:
          MCU_RET->NPSS_GPIO_CNTRL[4].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x03UL;
      }
      break;
    case 1:
      switch (chan) {
        case 0:
          MCU_RET->NPSS_GPIO_CNTRL[1].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x05UL;
          break;
        case 1:
          MCU_RET->NPSS_GPIO_CNTRL[2].NPSS_GPIO_CTRLS_b.NPSS_GPIO_MODE = 0x05UL;
          break;
      }
      break;
    default:

      break;
  }
}

/***************************************************************************/ /**
 * Read SYSRTC Output(compare) from register
 ******************************************************************************/
uint32_t rsi_sysrtc_get_compare_bit(const uint32_t group, const uint32_t channel)
{
  uint32_t shift, val;
  switch (group) {
    case 0:
      shift = SYSRTC_GRP0_CMP_SHIFT;
      break;
    case 1:
      shift = SYSRTC_GRP1_CMP_SHIFT;
      break;
    default:
      shift = 0;
      break;
  }

  switch (channel) {
    case 0:
      val = SYSRTC_GRPx_CMP0_OUT_BIT;
      break;
    case 1:
      val = SYSRTC_GRPx_CMP1_OUT_BIT;
      break;
    default:
      val = 0;
      break;
  }

  return (SYSRTC0->MCUSYSRTC_REG1) & (val << shift);
}

/***************************************************************************/ /**
 * Enables SYSRTC module
 ******************************************************************************/
void rsi_sysrtc_enable(void)
{
  // Enable SYSRTC module
  SYSRTC0->EN_SET = SYSRTC_EN_EN;
}

/***************************************************************************/ /**
 * Disables SYSRTC counting.
 ******************************************************************************/
void rsi_sysrtc_disable(void)
{
  if (SYSRTC0->EN != SYSRTC_EN_EN) {
    return;
  }

  // Stop counter
  rsi_sysrtc_stop();

  // Disable module
  SYSRTC0->EN_CLR = SYSRTC_EN_EN;

  // Need to reset timer - for disable sync to be set TODO: Design change maybe?
  SYSRTC0->SWRST = SYSRTC_SWRST_SWRST;

  rsi_sysrtc_wait_ready();
}

/***************************************************************************/ /**
 * Restores SYSRTC to its reset state.
 ******************************************************************************/
void rsi_sysrtc_reset(void)
{
  // Reset timer
  SYSRTC0->SWRST = SYSRTC_SWRST_SWRST;
}

/***************************************************************************/ /**
 * Initializes the selected SYSRTC group.
 ******************************************************************************/
void rsi_sysrtc_init_group(uint8_t group_number, rsi_sysrtc_group_config_t const *p_group_config)
{
  uint32_t temp = 0;

  switch (group_number) {
    case 0:
      temp = ((p_group_config->compare_channel0_enable ? 1UL : 0UL) << _SYSRTC_GRP0_CTRL_CMP0EN_SHIFT);
      if (p_group_config->p_compare_channel0_config != NULL) {
        temp |= ((uint32_t)p_group_config->p_compare_channel0_config->compare_match_out_action
                 << _SYSRTC_GRP0_CTRL_CMP0CMOA_SHIFT);
      }

#ifdef SYSRTC_GRP0_CTRL_CMP1EN
      temp |= ((p_group_config->compare_channel1_enable ? 1UL : 0UL) << _SYSRTC_GRP0_CTRL_CMP1EN_SHIFT);
      if (p_group_config->p_compare_channel1_config != NULL) {
        temp |= ((uint32_t)p_group_config->p_compare_channel1_config->compare_match_out_action
                 << _SYSRTC_GRP0_CTRL_CMP1CMOA_SHIFT);
      }
#endif
#ifdef SYSRTC_GRP0_CTRL_CAP0EN
      temp |= ((p_group_config->capture_channel0_enable ? 1UL : 0UL) << _SYSRTC_GRP0_CTRL_CAP0EN_SHIFT);
      if (p_group_config->p_capture_channel0_config != NULL) {
        temp |=
          ((uint32_t)p_group_config->p_capture_channel0_config->capture_input_edge << _SYSRTC_GRP0_CTRL_CAP0EDGE_SHIFT);
      }
#endif
      SYSRTC0->GRP0_CTRL = temp;
      rsi_sysrtc_grp0_sync();
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      temp = ((p_group_config->compare_channel0_enable ? 1UL : 0UL) << _SYSRTC_GRP1_CTRL_CMP0EN_SHIFT);
      if (p_group_config->p_compare_channel0_config != NULL) {
        temp |= ((uint32_t)p_group_config->p_compare_channel0_config->compare_match_out_action
                 << _SYSRTC_GRP1_CTRL_CMP0CMOA_SHIFT);
      }
#ifdef SYSRTC_GRP1_CTRL_CMP1EN
      temp |= ((p_group_config->compare_channel1_enable ? 1UL : 0UL) << _SYSRTC_GRP1_CTRL_CMP1EN_SHIFT);
      if (p_group_config->p_compare_channel1_config != NULL) {
        temp |= ((uint32_t)p_group_config->p_compare_channel1_config->compare_match_out_action
                 << _SYSRTC_GRP1_CTRL_CMP1CMOA_SHIFT);
      }
#endif
#ifdef SYSRTC_GRP1_CTRL_CAP0EN
      temp |= ((p_group_config->capture_channel0_enable ? 1UL : 0UL) << _SYSRTC_GRP1_CTRL_CAP0EN_SHIFT);
      if (p_group_config->p_capture_channel0_config != NULL) {
        temp |=
          ((uint32_t)p_group_config->p_capture_channel0_config->capture_input_edge << _SYSRTC_GRP1_CTRL_CAP0EDGE_SHIFT);
      }
#endif
      SYSRTC0->GRP1_CTRL = temp;
      rsi_sysrtc_grp1_sync();
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Enables one or more SYSRTC interrupts for the given group.
 ******************************************************************************/
void rsi_sysrtc_enable_group_interrupts(uint8_t group_number, uint32_t flags)
{

  switch (group_number) {
    case 0:
      SYSRTC0->GRP0_IEN_SET = flags;
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      SYSRTC0->GRP1_IEN_SET = flags;
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Disables one or more SYSRTC interrupts for the given group.
 ******************************************************************************/
void rsi_sysrtc_disable_group_interrupts(uint8_t group_number, uint32_t flags)
{

  switch (group_number) {
    case 0:
      SYSRTC0->GRP0_IEN_CLR = flags;
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      SYSRTC0->GRP1_IEN_CLR = flags;
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Clears one or more pending SYSRTC interrupts for the given group.
 ******************************************************************************/
void rsi_sysrtc_clear_group_interrupts(uint8_t group_number, uint32_t flags)
{

  switch (group_number) {
    case 0:
      SYSRTC0->GRP0_IF_CLR = flags;
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      SYSRTC0->GRP1_IF_CLR = flags;
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Gets pending SYSRTC interrupt flags for the given group.
 ******************************************************************************/
uint32_t rsi_sysrtc_get_group_interrupts(uint8_t group_number)
{

  switch (group_number) {
    case 0:
      return SYSRTC0->GRP0_IF;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      return SYSRTC0->GRP1_IF;

#endif

    default:
      return 0;
  }
}

/***************************************************************************/ /**
 * Gets enabled and pending SYSRTC interrupt flags.
 ******************************************************************************/
uint32_t rsi_sysrtc_get_group_enabled_interrupts(uint8_t group_number)
{
  uint32_t ien = 0;

  switch (group_number) {
    case 0:
      ien = SYSRTC0->GRP0_IEN;
      return SYSRTC0->GRP0_IF & ien;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      ien = SYSRTC0->GRP1_IEN;
      return SYSRTC0->GRP1_IF & ien;

#endif

    default:
      return 0;
  }
}

/***************************************************************************/ /**
 * Sets one or more pending SYSRTC interrupts for the given group from Software.
 ******************************************************************************/
void rsi_sysrtc_set_group_interrupts(uint8_t group_number, uint32_t flags)
{

  switch (group_number) {
    case 0:
      SYSRTC0->GRP0_IF_SET = flags;
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      SYSRTC0->GRP1_IF_SET = flags;
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Gets SYSRTC compare register value for selected channel of given group.
 ******************************************************************************/
uint32_t rsi_sysrtc_get_group_compare_channel_value(uint8_t group_number, uint8_t channel)
{

  switch (group_number) {
    case 0:
      switch (channel) {
        case 0:
          return SYSRTC0->GRP0_CMP0VALUE;

#ifdef SYSRTC_GRP0_CTRL_CMP1EN
        case 1:
          return SYSRTC0->GRP0_CMP1VALUE;
#endif

        default:
          break;
      }

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      switch (channel) {
        case 0:
          return SYSRTC0->GRP1_CMP0VALUE;

#ifdef SYSRTC_GRP1_CTRL_CMP1EN
        case 1:
          return SYSRTC0->GRP1_CMP1VALUE;
#endif

        default:
          break;
      }

#endif

    default:
      return 0;
  }
}

/***************************************************************************/ /**
 * Sets SYSRTC compare register value for selected channel of given group.
 ******************************************************************************/
void rsi_sysrtc_set_compare_value(uint8_t group_number, uint8_t channel, uint32_t value)
{

  switch (group_number) {
    case 0:
      switch (channel) {
        case 0:
          SYSRTC0->GRP0_CMP0VALUE = value;
          break;

#ifdef SYSRTC_GRP0_CTRL_CMP1EN
        case 1:
          SYSRTC0->GRP0_CMP1VALUE = value;
          break;
#endif
        default:
          break;
      }
      rsi_sysrtc_grp0_sync();
      break;

#if SYSRTC_GROUP_NUMBER > 1
    case 1:
      switch (channel) {
        case 0:
          SYSRTC0->GRP1_CMP0VALUE = value;
          break;

#ifdef SYSRTC_GRP1_CTRL_CMP1EN
        case 1:
          SYSRTC0->GRP1_CMP1VALUE = value;
          break;
#endif

        default:
          break;
      }
      rsi_sysrtc_grp1_sync();
      break;

#endif

    default:
      break;
  }
}

/***************************************************************************/ /**
 * Gets SYSRTC input capture register value for selected channel of given group.
 ******************************************************************************/
uint32_t rsi_sysrtc_get_capture_val(uint8_t group_number)
{

  switch (group_number) {
#ifdef SYSRTC_GRP0_CTRL_CAP0EN
    case 0:
      return SYSRTC0->GRP0_CAP0VALUE;
#endif

#if SYSRTC_GROUP_NUMBER > 1
#ifdef SYSRTC_GRP1_CTRL_CAP0EN
    case 1:
      return SYSRTC0->GRP1_CAP0VALUE;
#endif

#endif

    default:
      return 0;
  }
}
/***************************************************************************/ /**
 * Sets  SYSRTC interrupts
 ******************************************************************************/
void rsi_sysrtc_enable_interrupts(void)
{
  // Enable interrupts
  RSI_NpssIntrUnMask(NPSS_TO_MCU_SYSRTC_INTR);
  NVIC_EnableIRQ(NPSS_TO_MCU_SYRTC_INTR_IRQn);
}

/***************************************************************************/ /**
 * Disables  SYSRTC interrupts
 ******************************************************************************/
void rsi_sysrtc_disable_interrupts(void)
{
  //Disable Interrupts
  NVIC_DisableIRQ(NPSS_TO_MCU_SYRTC_INTR_IRQn);
  RSI_NpssIntrClear(NPSS_TO_MCU_SYSRTC_INTR);
  RSI_NpssIntrMask(NPSS_TO_MCU_SYSRTC_INTR);
  rsi_sysrtc_clear_npss_mcu_intr();
}

/** @} (end addtogroup sysrtc) */
#endif /* defined(SYSRTC_COUNT) && (SYSRTC_COUNT > 0) */
