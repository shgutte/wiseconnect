/***************************************************************************/ /**
 * @file sli_si91x_power_manager.c
 * @brief Power Manager Internal API implementation
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

#include "sli_si91x_power_manager.h"
#include "sli_si91x_power_manager_board_config.h"
#include "sl_si91x_types.h"
#include "sl_si91x_host_interface.h"
#include "clock_update.h"
#include "rsi_m4.h"
#include "rsi_pll.h"
#include "rsi_power_save.h"
#include "rsi_rom_clks.h"
#include "rsi_rom_power_save.h"
#include "rsi_rom_ulpss_clk.h"

/*******************************************************************************
 ***************************  DEFINES / MACROS   ********************************
 ******************************************************************************/
#define P2P_STATUS_REG           *(volatile uint32_t *)(M4SS_P2P_INT_BASE_ADDRESS + 0x174) // P2P status register
#define JUMP_CB_ADDRESS          (uint32_t) RSI_PS_RestoreCpuContext // Callback Address to restore CPU context
#define MAX_M4SS_RAM_SIZE        320                                 // Maximum m4ss RAM size
#define MAX_ULPSS_RAM_SIZE       8                                   // Maximum ulpss RAM size
#define SOC_PLL_REF_FREQUENCY    32000000                            // SOC Pll reference frequency
#define PS4_HP_FREQUENCY         180000000                           // PS4 high power clock frequency
#define PS4_LP_FREQUENCY         100000000                           // PS4 low power clock frequency
#define PS3_HP_FREQUENCY         80000000                            // PS3 high power clock frequency
#define PS3_LP_FREQUENCY         32000000                            // PS3 low power clock frequency
#define DIVISION_FACTOR          0                                   // Division Factor for clock
#define PMU_WAIT_TIME            15                                  // Max PMU turn on wait time
#define LDO_WAIT_TIME            15                                  // Max LDO turn on wait time
#define VALID_M4SS_PERIPHERAL    0x466A10                            // Valid bits for M4SS peripheral
#define VALID_ULPSS_PERIPHERAL   0x1FEC0000                          // Valid bits for ULPSS peripheral
#define VALID_NPSS_PERIPHERAL    0x107FE                             // Valid bits for NPSS peripheral
#define VALID_WAKEUP_SOURCES     0x3F7F0000                          // Valid bits for Wakeup sources
#define VALID_RAM_RETENTION_MODE 0xFC                                // Valid bits for RAM retention mode
#define VALID_M4SS_RAM           0x3FF                               // Valid bits for M4SS RAM Banks
#define VALID_ULPSS_RAM          0xF                                 // Valid bits for ULPSS RAM Banks
#define VALID                    1                                   // Valid
#define INVALID                  0                                   // Invalid
#define NO_OF_ACTIVE_STATES      3                                   // Number of active states
#define PS_OFFSET                2                                   // Power State offset
#define NO_OF_TRANSITIONS        7 // Number of all possible transitions, i.e., PS0, PS1, PS2, PS3, PS4, Sleep and Standby
#define NO_OF_STATE_TRANSITIONS  5 // Number of all state transitions, i.e., PS0, PS1, PS2, PS3, PS4.

/*******************************************************************************
 ***************************  Local Types  ********************************
 ******************************************************************************/
typedef void (*power_state_fptr)(void);

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/
static void ps4_to_ps2_state_change(void);
static void ps4_to_ps3_state_change(void);
static void ps4_to_ps0_state_change(void);
static void ps3_to_ps4_state_change(void);
static void ps3_to_ps2_state_change(void);
static void ps3_to_ps0_state_change(void);
static void ps2_to_ps4_state_change(void);
static void ps2_to_ps3_state_change(void);
static void ps2_to_ps1_state_change(void);
static void low_power_hardware_configuration(void);
static sl_status_t configure_ram_memory(sl_power_ram_retention_config_t *config,
                                        uint32_t *m4ss_ram,
                                        uint32_t *ulpss_ram);
static sl_status_t trigger_sleep(sli_power_sleep_config_t *config, uint8_t sleep_type);
static sl_status_t convert_rsi_to_sl_error_code(rsi_error_t error);

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
uint32_t ramVector[SI91X_VECTOR_TABLE_ENTRIES] __attribute__((aligned(256)));

// Power state transition structure
typedef struct {
  boolean_t is_valid;    // State is valid or not
  power_state_fptr fptr; // State change function pointer
} power_state_transition_t;

typedef struct {
  uint8_t from_ps;                                   // From the power state it transits
  power_state_transition_t to_ps[NO_OF_TRANSITIONS]; // All possible transition states
} power_state_struct_t;

// Power State transition
static const power_state_struct_t ps_transition[NO_OF_ACTIVE_STATES] = {
  {
    .from_ps                               = SL_SI91X_POWER_MANAGER_PS2,
    .to_ps[SL_SI91X_POWER_MANAGER_PS0]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_PS1]     = { .is_valid = VALID, .fptr = ps2_to_ps1_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS2]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_PS3]     = { .is_valid = VALID, .fptr = ps2_to_ps3_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS4]     = { .is_valid = VALID, .fptr = ps2_to_ps4_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_SLEEP]   = { .is_valid = VALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_STANDBY] = { .is_valid = VALID, .fptr = NULL },
  },
  {
    .from_ps                               = SL_SI91X_POWER_MANAGER_PS3,
    .to_ps[SL_SI91X_POWER_MANAGER_PS0]     = { .is_valid = VALID, .fptr = ps3_to_ps0_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS1]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_PS2]     = { .is_valid = VALID, .fptr = ps3_to_ps2_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS3]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_PS4]     = { .is_valid = VALID, .fptr = ps3_to_ps4_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_SLEEP]   = { .is_valid = VALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_STANDBY] = { .is_valid = VALID, .fptr = NULL },
  },
  {
    .from_ps                               = SL_SI91X_POWER_MANAGER_PS4,
    .to_ps[SL_SI91X_POWER_MANAGER_PS0]     = { .is_valid = VALID, .fptr = ps4_to_ps0_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS1]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_PS2]     = { .is_valid = VALID, .fptr = ps4_to_ps2_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS3]     = { .is_valid = VALID, .fptr = ps4_to_ps3_state_change },
    .to_ps[SL_SI91X_POWER_MANAGER_PS4]     = { .is_valid = INVALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_SLEEP]   = { .is_valid = VALID, .fptr = NULL },
    .to_ps[SL_SI91X_POWER_MANAGER_STANDBY] = { .is_valid = VALID, .fptr = NULL },
  }
};

/*******************************************************************************
***********************  Global function Definitions *************************
 ******************************************************************************/

/*******************************************************************************
 * Updates the Power State as per the from and to parameters.
 * Calls the static functions from the constant structure
 * according to the state change requirement.
 * By default it returns SL_STATUS_INVALID_PARAMETER
 ******************************************************************************/
sl_status_t sli_si91x_power_manager_change_power_state(sl_power_state_t from, sl_power_state_t to)
{
  sl_status_t status = SL_STATUS_OK;
  if ((from > SL_SI91X_POWER_MANAGER_PS4) || (from < SL_SI91X_POWER_MANAGER_PS2) || (to >= LAST_ENUM_POWER_STATE)) {
    // Validate the power state, if not in range returns error code.
    status = SL_STATUS_INVALID_PARAMETER;
    return status;
  }

  if (ps_transition[from - PS_OFFSET].to_ps[to].fptr != NULL) {
    // If the from and to state transition function pointer is not null,
    // then it calls the function and state change is performed.
    ps_transition[from - PS_OFFSET].to_ps[to].fptr();
    status = SL_STATUS_OK;
  } else {
    // If it reached here, returns Null pointer
    status = SL_STATUS_NULL_POINTER;
  }
  return status;
}

/*******************************************************************************
 * To set the sleep configurations.
 * It takes macro from the sli_si91x_power_manager_board_config.h file where
 * stack address, callback address, vector offset are configured according to the
 * board.
 * It switches off the components which are not required and goes to sleep with retention.
 ******************************************************************************/
sl_status_t sli_si91x_power_manager_set_sleep_configuration(sl_power_state_t state)
{
  if ((state < SL_SI91X_POWER_MANAGER_PS2) || (state > SL_SI91X_POWER_MANAGER_PS4)) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  sli_power_sleep_config_t config;
  config.low_freq_clock          = SLI_SI91X_POWER_MANAGER_DISABLE_LF_MODE;
  config.stack_address           = SL_SLEEP_RAM_USAGE_ADDRESS;
  config.vector_offset           = SL_SLEEP_VECTOR_OFFSET_WITH_RETENTION;
  config.wakeup_callback_address = JUMP_CB_ADDRESS;
  if (state == SL_SI91X_POWER_MANAGER_PS2) {
    config.mode = SLI_SI91X_POWER_MANAGER_WAKEUP_WITH_RETENTION;
  } else {
    config.mode = SLI_SI91X_POWER_MANAGER_WAKEUP_FROM_FLASH_MODE;
    // Low power hardware configuration to switch off the components which are not required.
    low_power_hardware_configuration();
  }
  P2P_STATUS_REG &= ~M4_is_active;

  if ((P2P_STATUS_REG & TA_wakeup_M4) || (P2P_STATUS_REG & M4_wakeup_TA)
      || ((sl_si91x_host_queue_status((sl_si91x_queue_type_t)SI91X_COMMON_CMD)
           | sl_si91x_host_queue_status((sl_si91x_queue_type_t)SI91X_WLAN_CMD)
           | sl_si91x_host_queue_status((sl_si91x_queue_type_t)SI91X_NETWORK_CMD)
           | sl_si91x_host_queue_status((sl_si91x_queue_type_t)SI91X_SOCKET_CMD)
           | sl_si91x_host_queue_status((sl_si91x_queue_type_t)SI91X_BT_CMD)))) {
    P2P_STATUS_REG |= M4_is_active;
  }
  // If any error code, it returns it otherwise goes to sleep with retention.
  return trigger_sleep(&config, SLEEP_WITH_RETENTION);
}

/*******************************************************************************
 * Updates the peripheral power state, i.e., enables and disables the peripheral
 * as per requirements. 
 * Validates the members of sl_power_peripheral_t structure and it is passed to 
 * equivalent rsi apis to power-on / power-off the peripherals/components as per
 * the value of add.
 ******************************************************************************/
sl_status_t sli_power_manager_update_peripheral(sl_power_peripheral_t *peripheral, boolean_t add)
{
  if (peripheral == NULL) {
    // Validates peripheral, if null returns error code.
    return SL_STATUS_NULL_POINTER;
  }
  // Validates the M4SS peripherals, if invalid returns error code.
  if ((peripheral->m4ss_peripheral) && !(peripheral->m4ss_peripheral & VALID_M4SS_PERIPHERAL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  // Validates the ULPSS peripherals, if invalid returns error code.
  if ((peripheral->ulpss_peripheral) && !(peripheral->ulpss_peripheral & VALID_ULPSS_PERIPHERAL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  // Validates the NPSS peripherals, if invalid returns error code.
  if ((peripheral->npss_peripheral) && !(peripheral->npss_peripheral & VALID_NPSS_PERIPHERAL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (add) {
    // RSI APIs to power on the peripherals.
    if (peripheral->m4ss_peripheral != 0) {
      RSI_PS_M4ssPeriPowerUp(peripheral->m4ss_peripheral);
    }
    if (peripheral->ulpss_peripheral != 0) {
      RSI_PS_UlpssPeriPowerUp(peripheral->ulpss_peripheral);
    }
    if (peripheral->npss_peripheral != 0) {
      RSI_PS_NpssPeriPowerUp(peripheral->npss_peripheral);
    }
  } else {
    // RSI APIs to power off the peripherals.
    if (peripheral->m4ss_peripheral != 0) {
      RSI_PS_M4ssPeriPowerDown(peripheral->m4ss_peripheral);
    }
    if (peripheral->ulpss_peripheral != 0) {
      RSI_PS_UlpssPeriPowerDown(peripheral->ulpss_peripheral);
    }
    if (peripheral->npss_peripheral != 0) {
      RSI_PS_NpssPeriPowerDown(peripheral->npss_peripheral);
    }
  }
  return SL_STATUS_OK;
}

/*******************************************************************************
 * Validates the power state transitions. If invalid, returns false.
 * It verifies all the possible state transitions, if valid returns true otherwise
 * returns false.
 ******************************************************************************/
boolean_t sli_si91x_power_manager_is_valid_transition(sl_power_state_t from, sl_power_state_t to)
{
  boolean_t status = false;

  if ((from >= LAST_ENUM_POWER_STATE) || (to >= LAST_ENUM_POWER_STATE)) {
    // Validate the power state, if not in range returns error code.
    status = SL_STATUS_INVALID_PARAMETER;
    return status;
  }
  if (ps_transition[from - PS_OFFSET].to_ps[to].is_valid) {
    // If state change is valid, return true, otherwise return false
    status = true;
  }
  return status;
}

/*******************************************************************************
 * Configures the wakeup sources.
 * As per the flag, wakeup sources are set or cleared.
 * The source is the ored value of wakeup sources from \ref sl_power_wakeup_sources_t enum.
 ******************************************************************************/
sl_status_t sli_si91x_power_configure_wakeup_resource(uint32_t source, boolean_t add)
{
  if (!(source & VALID_WAKEUP_SOURCES)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (add) {
    // If flag is true, rsi API to set the wakeup sources is called.
    RSI_PS_SetWkpSources(source);
  } else {
    // If flag is false, rsi API to clear the wakeup sources is called.
    RSI_PS_ClrWkpSources(source);
  }
  return SL_STATUS_OK;
}

/*******************************************************************************
 * Sets the RAM retention as well as configures the RAM banks which needs to be retained.
 * Validation of all the parameters is performed, if invalid then error code is returned.
 * If configure_ram_banks is enabled, user can configure RAM_BANKS using bank number.
 * If configure_ram_banks is disabled, user can enter the size of RAM to be retained.
 * If configure_ram_retention is enabled, user can set the RAM retention mode using ram_retention_mode.
 * If configure_ram_retention is disabled, user can clear the RAM retention using ram_retention_mode.
 ******************************************************************************/
sl_status_t sli_si91x_power_manager_set_ram_retention_configuration(sl_power_ram_retention_config_t *config)
{
  sl_status_t status;
  uint32_t m4ss_ram, ulpss_ram;
  m4ss_ram = ulpss_ram = 0;
  if (config == NULL) {
    // Validates config, if null, returns error code
    return SL_STATUS_NULL_POINTER;
  }
  if ((config->m4ss_ram_size_kb > MAX_M4SS_RAM_SIZE) || (config->ulpss_ram_size_kb > MAX_ULPSS_RAM_SIZE)) {
    // If m4ss ram size is more than 320KB or
    // If ulp4ss ram size is more than 8KB or , returns error code.
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((config->ram_retention_mode) && !(config->ram_retention_mode & VALID_RAM_RETENTION_MODE)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((config->m4ss_ram_banks) && !(config->m4ss_ram_banks & VALID_M4SS_RAM)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((config->ulpss_ram_banks) && !(config->ulpss_ram_banks & VALID_ULPSS_RAM)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (!config->configure_ram_banks) {
    // configure_ram_banks flag is false, i.e., memory size is provided.
    // static function to select appropriate RAM size and get the ored value of RAM banks
    status = configure_ram_memory(config, &m4ss_ram, &ulpss_ram);
    if (status != SL_STATUS_OK) {
      // If status is not OK, returns error code.
      return status;
    }
    // power down the ulpss RAM banks
    RSI_PS_UlpssRamBanksPeriPowerDown(~ulpss_ram);
    // power down the m4ss RAM banks
    RSI_PS_M4ssRamBanksPeriPowerDown(~m4ss_ram);
  } else {
    // configure_ram_banks flag is true, i.e., RAM bank number is provided.
    // power down the m4ss RAM banks
    if (config->m4ss_ram_banks != 0) {
      RSI_PS_M4ssRamBanksPeriPowerDown(config->m4ss_ram_banks);
    }
    // power down the ulpss RAM banks
    if (config->ulpss_ram_banks != 0) {
      RSI_PS_UlpssRamBanksPeriPowerDown(config->ulpss_ram_banks);
    }
  }
  if (config->configure_ram_retention) {
    // configure_ram_retention flag is true, i.e., RAM retention mode is provided, it sets the RAM retention.
    RSI_PS_SetRamRetention(config->ram_retention_mode);
  } else {
    // configure_ram_retention flag is false, i.e., RAM retention mode is not provided, it clears the RAM retention.
    RSI_PS_ClrRamRetention(config->ram_retention_mode);
  }
  return SL_STATUS_OK;
}

/*******************************************************************************
 * Configures the clock as per the input, i.e. powersave or performance.
 * PS4 PowerSave -> 100 MHz clock
 * PS4 Performance -> 180 MHz clock
 * PS3 PowerSave -> 32 MHz clock
 * PS3 Performance -> 80 MHz clock
 * PS2 -> 20 MHz clock
 ******************************************************************************/
sl_status_t sli_si91x_power_manager_configure_clock(sl_power_state_t state, boolean_t mode)
{
  if (state >= LAST_ENUM_POWER_STATE) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  switch (state) {
    case SL_SI91X_POWER_MANAGER_PS4:
      if (mode) {
        // Default keep M4 in reference clock
        RSI_CLK_M4SocClkConfig(M4CLK, M4_ULPREFCLK, DIVISION_FACTOR);
        // Configures the required registers for 180 Mhz clock in PS4
        RSI_PS_PS4SetRegisters();
        // Configure the PLL frequency
        // Configure the SOC PLL to 180MHz
        RSI_CLK_SetSocPllFreq(M4CLK, PS4_HP_FREQUENCY, SOC_PLL_REF_FREQUENCY);
        // Switch M4 clock to PLL clock for speed operations
        RSI_CLK_M4SocClkConfig(M4CLK, M4_SOCPLLCLK, DIVISION_FACTOR);
      } else {
        // Default keep M4 in reference clock
        RSI_CLK_M4SocClkConfig(M4CLK, M4_ULPREFCLK, DIVISION_FACTOR);
        // Configure the PLL frequency
        // Configure the SOC PLL to 100MHz
        RSI_CLK_SetSocPllFreq(M4CLK, PS4_LP_FREQUENCY, SOC_PLL_REF_FREQUENCY);
        // Switch M4 clock to PLL clock for speed operations
        RSI_CLK_M4SocClkConfig(M4CLK, M4_SOCPLLCLK, DIVISION_FACTOR);
      }
      break;
    case SL_SI91X_POWER_MANAGER_PS3:
      if (mode) {
        // Default keep M4 in reference clock
        RSI_CLK_M4SocClkConfig(M4CLK, M4_ULPREFCLK, DIVISION_FACTOR);
        // Configure the PLL frequency
        // Configure the SOC PLL to 80MHz
        RSI_CLK_SetSocPllFreq(M4CLK, PS3_HP_FREQUENCY, SOC_PLL_REF_FREQUENCY);
        // Switch M4 clock to PLL clock for speed operations
        RSI_CLK_M4SocClkConfig(M4CLK, M4_SOCPLLCLK, DIVISION_FACTOR);
      } else {
        // Default keep M4 in reference clock
        RSI_CLK_M4SocClkConfig(M4CLK, M4_ULPREFCLK, DIVISION_FACTOR);
        // Configure the PLL frequency
        // Configure the SOC PLL to 80MHz
        RSI_CLK_SetSocPllFreq(M4CLK, PS3_LP_FREQUENCY, SOC_PLL_REF_FREQUENCY);
        // Switch M4 clock to PLL clock for speed operations
        RSI_CLK_M4SocClkConfig(M4CLK, M4_SOCPLLCLK, DIVISION_FACTOR);
      }
      break;
    case SL_SI91X_POWER_MANAGER_PS2:
      // Configures the clock with 20 MHz.
      RSI_IPMU_M20rcOsc_TrimEfuse();
      // Sets FSM HF frequency to 20.
      RSI_PS_FsmHfFreqConfig(20);
      // Updated the clock global variables
      RSI_PS_PS2UpdateClockVariable();
      break;
    default:
      // If reaches here, returns error code.
      return SL_STATUS_INVALID_PARAMETER;
      break;
  }
  return SL_STATUS_OK;
}

/*******************************************************************************
 * Sets the initial hardware configuration.
 * Configures the system clock to PS4 powersave mode, i.e., 100 MHz
 * Enables the QSPI clock.
 ******************************************************************************/
void sli_si91x_power_manager_init_hardware(void)
{
  // Sets PS4 Power save mode, 100 MHz.
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS4, false);
  ROMAPI_M4SS_CLK_API->clk_qspi_clk_config(M4CLK, QSPI_SOCPLLCLK, 0, 0, DIVISION_FACTOR);
}

/*******************************************************************************
 **********************  Local Function Definition****************************
 ******************************************************************************/
/*******************************************************************************
 * Configures the hardware for low power mode.
 * Disables the components and clocks which are not required.
 ******************************************************************************/
static void low_power_hardware_configuration(void)
{
  // Change the TASS reference clock to 32MHz RC clock
  // NOTE: This should not be used in wisemcu mode , should be used in MCU only mode
  RSI_ChangeTassRefClock();

  // Disable OTHER_CLK which is enabled at Start-up
  RSI_CLK_PeripheralClkDisable3(M4CLK, M4_SOC_CLK_FOR_OTHER_ENABLE);
  // Disable Timer clock which is enabled in Bootloader
  RSI_ULPSS_TimerClkDisable(ULPCLK);
  // Disabling LF_RC Clocks
  RSI_ULPSS_DisableRefClks(MCU_ULP_32KHZ_RC_CLK_EN);
  // Power-Down Button Calibration
  RSI_PS_BodPwrGateButtonCalibDisable();
  // Disable PTAT for Analog Peripherals
  RSI_IPMU_ProgramConfigData(ana_perif_ptat_common_config2);
  // Disable PTAT for Brown-Out Detection Clocks
  RSI_IPMU_ProgramConfigData(ipmu_bod_clks_common_config2);

  // Power-Down Analog Peripherals
  RSI_IPMU_PowerGateClr(AUXDAC_PG_ENB | AUXADC_PG_ENB | WURX_CORR_PG_ENB | WURX_PG_ENB | ULP_ANG_CLKS_PG_ENB
                        | CMP_NPSS_PG_ENB);

  RSI_PS_PowerSupplyDisable(POWER_ENABLE_TIMESTAMPING);
  // Power-Down High-Frequency PLL Domain
  RSI_PS_SocPllSpiDisable();
  // Power-Down QSPI-DLL Domain
  RSI_PS_QspiDllDomainDisable();
  // Enable first boot up
  RSI_PS_EnableFirstBootUp(1);
  // XTAL wait time is skipped since RC_32MHZ Clock is used for Processor on wakeup
  RSI_PS_SkipXtalWaitTime(1);
  // by using this API we programmed the RTC timer clock in SOC
  // MSB 8 bits for the Integer part &
  // LSB 17bits for the Fractional part
  // Ex: 32Khz clock = 31.25us ==> 31.25*2^17 = 4096000 = 0x3E8000
  /* Time Period Programming */
  RSI_TIMEPERIOD_TimerClkSel(TIME_PERIOD, 0x003E7FFF);
}

/*******************************************************************************
 * State Change from PS4 to PS2.
 * Hardware is configured for low power mode.
 * System clock is changed to 20 Mhz.
 * LDO and other registers are taken care by RSI api.
 ******************************************************************************/
static void ps4_to_ps2_state_change(void)
{
  // Pointing the scb vtor to RAM vector
  memcpy(ramVector, (uint32_t *)SCB->VTOR, sizeof(uint32_t) * SI91X_VECTOR_TABLE_ENTRIES);
  SCB->VTOR = (uint32_t)ramVector;
  // Low power hardware configuration to switch off the components which are not required.
  low_power_hardware_configuration();

  // Change to 20MHz-RC to be used as Processor Clock in PS2 state
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS2, true);

  // Switching from PS4 to PS2 state
  RSI_PS_PowerStateChangePs4toPs2(ULP_MCU_MODE,
                                  PWR_MUX_SEL_ULPSSRAM_SCDC_0_9,
                                  PWR_MUX_SEL_M4_ULP_RAM_SCDC_0_9,
                                  PWR_MUX_SEL_M4_ULP_RAM16K_SCDC_0_9,
                                  PWR_MUX_SEL_M4ULP_SCDC_0_6,
                                  PWR_MUX_SEL_ULPSS_SCDC_0_9,
                                  DISABLE_BG_SAMPLE_ENABLE,
                                  DISABLE_DC_DC_ENABLE,
                                  DISABLE_SOCLDO_ENABLE,
                                  DISABLE_STANDBYDC,
                                  DISABLE_TA192K_RAM_RET,
                                  DISABLE_M464K_RAM_RET);
}

/*******************************************************************************
 * State Change from PS4 to PS3.
 * System clock is changed to 32 MHz.
 ******************************************************************************/
static void ps4_to_ps3_state_change(void)
{
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS3, false);
}

/*******************************************************************************
 * State Change from PS4 to PS0 (Sleep without retention).
 * It takes macro from the sli_si91x_power_manager_board_config.h file where
 * stack address, callback address, vector offset are configured according to the
 * board.
 * It switches off the components which are not required and goes to sleep without retention.
 ******************************************************************************/
static void ps4_to_ps0_state_change(void)
{
  sli_power_sleep_config_t config;
  config.low_freq_clock          = SLI_SI91X_POWER_MANAGER_DISABLE_LF_MODE;
  config.mode                    = SLI_SI91X_POWER_MANAGER_WAKEUP_WITHOUT_RETENTION;
  config.stack_address           = SL_SLEEP_STACK_USAGE_ADDRESS;
  config.vector_offset           = SL_SLEEP_VECTOR_OFFSET;
  config.wakeup_callback_address = SL_SLEEP_WAKEUP_CALLBACK_ADDRESS;
  // Low power hardware configuration to switch off the components which are not required.
  low_power_hardware_configuration();
  // If any error code, it returns it otherwise goes to sleep without retention.
  trigger_sleep(&config, SLEEP_WITHOUT_RETENTION);
}

/*******************************************************************************
 * State Change from PS3 to PS4.
 * System clock is changed to 100 MHz.
 ******************************************************************************/
static void ps3_to_ps4_state_change(void)
{
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS4, false);
  ROMAPI_M4SS_CLK_API->clk_qspi_clk_config(M4CLK, QSPI_SOCPLLCLK, 0, 0, DIVISION_FACTOR);
}

/*******************************************************************************
 * State Change from PS3 to PS2.
 * Hardware is configured for low power mode.
 * System clock is changed to 20 Mhz.
 * LDO and other registers are taken care by RSI api.
 ******************************************************************************/
static void ps3_to_ps2_state_change(void)
{
  // Pointing the scb vtor to RAM vector
  memcpy(ramVector, (uint32_t *)SCB->VTOR, sizeof(uint32_t) * SI91X_VECTOR_TABLE_ENTRIES);
  SCB->VTOR = (uint32_t)ramVector;

  // Low power hardware configuration to switch off the components which are not required.
  low_power_hardware_configuration();

  // Change to 20MHz-RC to be used as Processor Clock in PS2 state
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS2, true);

  // Switching from PS3 to PS2 state
  RSI_PS_PowerStateChangePs4toPs2(ULP_MCU_MODE,
                                  PWR_MUX_SEL_ULPSSRAM_SCDC_0_9,
                                  PWR_MUX_SEL_M4_ULP_RAM_SCDC_0_9,
                                  PWR_MUX_SEL_M4_ULP_RAM16K_SCDC_0_9,
                                  PWR_MUX_SEL_M4ULP_SCDC_0_6,
                                  PWR_MUX_SEL_ULPSS_SCDC_0_9,
                                  DISABLE_BG_SAMPLE_ENABLE,
                                  DISABLE_DC_DC_ENABLE,
                                  DISABLE_SOCLDO_ENABLE,
                                  DISABLE_STANDBYDC,
                                  DISABLE_TA192K_RAM_RET,
                                  DISABLE_M464K_RAM_RET);
}

/*******************************************************************************
 * State Change from PS3 to PS0 (Sleep without retention).
 * It takes macro from the sli_si91x_power_manager_board_config.h file where
 * stack address, callback address, vector offset are configured according to the
 * board.
 * It switches off the components which are not required and goes to sleep without retention.
 ******************************************************************************/
static void ps3_to_ps0_state_change(void)
{
  sli_power_sleep_config_t config;
  config.low_freq_clock          = SLI_SI91X_POWER_MANAGER_DISABLE_LF_MODE;
  config.mode                    = SLI_SI91X_POWER_MANAGER_WAKEUP_WITHOUT_RETENTION;
  config.stack_address           = SL_SLEEP_STACK_USAGE_ADDRESS;
  config.vector_offset           = SL_SLEEP_VECTOR_OFFSET;
  config.wakeup_callback_address = SL_SLEEP_WAKEUP_CALLBACK_ADDRESS;
  low_power_hardware_configuration();
  trigger_sleep(&config, SLEEP_WITHOUT_RETENTION);
}

/*******************************************************************************
 * State Change from PS2 to PS4.
 * System clock is changed to 100 Mhz.
 * LDO and other registers are taken care by RSI api.
 ******************************************************************************/
static void ps2_to_ps4_state_change(void)
{
  ps_power_state_change_ps2_to_Ps4(PMU_WAIT_TIME, LDO_WAIT_TIME);
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS4, false);
}

/*******************************************************************************
 * State Change from PS2 to PS3.
 * System clock is changed to 32 Mhz.
 * LDO and other registers are taken care by RSI api.
 ******************************************************************************/
static void ps2_to_ps3_state_change(void)
{
  ps_power_state_change_ps2_to_Ps4(PMU_WAIT_TIME, LDO_WAIT_TIME);
  sli_si91x_power_manager_configure_clock(SL_SI91X_POWER_MANAGER_PS3, false);
}

/*******************************************************************************
 * State Change from PS2 to PS1 (Sleep with retention).
 * It takes macro from the sli_si91x_power_manager_board_config.h file where
 * stack address, callback address, vector offset are configured according to the
 * board.
 * It switches off the components which are not required and goes to sleep with retention.
 * If the wakeup sources are configured as ULPSS or SDCSS then only it will transit to PS1.
 ******************************************************************************/
static void ps2_to_ps1_state_change(void)
{
  uint32_t get_wakeup_sources;
  get_wakeup_sources = RSI_PS_GetWkpSources();
  if ((get_wakeup_sources & SL_SI91X_POWER_MANAGER_ULPSS_WAKEUP)
      || (get_wakeup_sources & SL_SI91X_POWER_MANAGER_SDCSS_WAKEUP)) {
    sli_si91x_power_manager_set_sleep_configuration(SL_SI91X_POWER_MANAGER_PS2);
  }
}

/*******************************************************************************
 * Trigger sleep as per the parameters passed in the config structure and sleep type.
 * RSI APIs handles the retention as per parameters and enters deep sleep mode.
 * If any error is encountered, error code is returned.
 ******************************************************************************/
static sl_status_t trigger_sleep(sli_power_sleep_config_t *config, uint8_t sleep_type)
{
  sl_status_t status;
  rsi_error_t error_code;
  if (config == NULL) {
    // Validates config, if null returns error code
    return SL_STATUS_NULL_POINTER;
  }
  // Stack address, wakeup callback address, vector offset and mode is configured in it.
  RSI_PS_RetentionSleepConfig(config->stack_address,
                              config->wakeup_callback_address,
                              config->vector_offset,
                              config->mode);
  // According to the sleep type, with retention or without retention it enters the sleep mode.
  error_code = RSI_PS_EnterDeepSleep(sleep_type, config->low_freq_clock);
  // If error is encountered, it is converted to sl error code.
  status = convert_rsi_to_sl_error_code(error_code);
  return status;
}

/*******************************************************************************
 * As per the memory passed, it sets the bits of RAM banks in m4ss and ulpss 
 * registers and updates it.
 ******************************************************************************/
static sl_status_t configure_ram_memory(sl_power_ram_retention_config_t *config,
                                        uint32_t *m4ss_ram,
                                        uint32_t *ulpss_ram)
{
  if ((config == NULL) || (m4ss_ram == NULL) || (ulpss_ram == NULL)) {
    // Validates config, m4ss_ram and ulpss_ram, if null pointer returns error code.
    return SL_STATUS_NULL_POINTER;
  }
  if (config->m4ss_ram_size_kb <= 4) {
    // If M4SS RAM Size is less than 4 KB, bit 0 is set.
    *m4ss_ram |= RAM_BANK_0;
  }
  if (config->m4ss_ram_size_kb <= 8) {
    // If M4SS RAM Size is less than 8 KB, bit 1 is set.
    *m4ss_ram |= RAM_BANK_1;
  }
  if (config->m4ss_ram_size_kb <= 12) {
    // If M4SS RAM Size is less than 12 KB, bit 2 is set.
    *m4ss_ram |= RAM_BANK_2;
  }
  if (config->m4ss_ram_size_kb <= 16) {
    // If M4SS RAM Size is less than 16 KB, bit 3 is set.
    *m4ss_ram |= RAM_BANK_3;
  }
  if (config->m4ss_ram_size_kb <= 32) {
    // If M4SS RAM Size is less than 32 KB, bit 4 is set.
    *m4ss_ram |= RAM_BANK_4;
  }
  if (config->m4ss_ram_size_kb <= 64) {
    // If M4SS RAM Size is less than 64 KB, bit 5 is set.
    *m4ss_ram |= RAM_BANK_5;
  }
  if (config->m4ss_ram_size_kb <= 128) {
    // If M4SS RAM Size is less than 128 KB, bit 6 is set.
    *m4ss_ram |= RAM_BANK_6;
  }
  if (config->m4ss_ram_size_kb <= 192) {
    // If M4SS RAM Size is less than 192 KB, bit 7 is set.
    *m4ss_ram |= RAM_BANK_7;
  }
  if (config->m4ss_ram_size_kb <= 256) {
    // If M4SS RAM Size is less than 256 KB, bit 8 is set.
    *m4ss_ram |= RAM_BANK_8;
  }
  if (config->m4ss_ram_size_kb <= 320) {
    // If M4SS RAM Size is less than 320 KB, bit 9 is set.
    *m4ss_ram |= RAM_BANK_9;
  }
  if (config->ulpss_ram_size_kb <= 2) {
    // If ULPSS RAM Size is less than 2 KB, bit 0 is set.
    *ulpss_ram |= ULPSS_2K_BANK_0;
  }
  if (config->ulpss_ram_size_kb <= 4) {
    // If ULPSS RAM Size is less than 4 KB, bit 1 is set.
    *ulpss_ram |= ULPSS_2K_BANK_1;
  }
  if (config->ulpss_ram_size_kb <= 6) {
    // If ULPSS RAM Size is less than 6 KB, bit 2 is set.
    *ulpss_ram |= ULPSS_2K_BANK_2;
  }
  if (config->ulpss_ram_size_kb <= 8) {
    // If ULPSS RAM Size is less than 8 KB, bit 3 is set.
    *ulpss_ram |= ULPSS_2K_BANK_3;
  }
  return SL_STATUS_OK;
}

/*******************************************************************************
 * To validate the RSI error code
 * While calling the RSI APIs, it returns the RSI Error codes.
 * This function converts the RSI error codes into SL error codes.
 * It takes argument as RSI error type and returns the SL error type.
 * It has a single switch statement which is mapped with the SL error code and
 * after successful conversion it breaks the switch statement.
 * If the error code is not listed, by default is SL_STATUS_FAIL.
 ******************************************************************************/
static sl_status_t convert_rsi_to_sl_error_code(rsi_error_t error)
{
  sl_status_t status;
  switch (error) {
    case RSI_OK:
      status = SL_STATUS_OK;
      break;
    case INVALID_PARAMETERS:
      status = SL_STATUS_INVALID_PARAMETER;
      break;
    case ERROR_INVALID_INPUT_FREQUENCY:
      status = SL_STATUS_INVALID_PARAMETER;
      break;
    case ERROR_CLOCK_NOT_ENABLED:
      status = SL_STATUS_NOT_INITIALIZED;
      break;
    default:
      status = SL_STATUS_FAIL;
      break;
  }
  return status;
}