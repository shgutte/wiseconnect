/***************************************************************************/ /**
 * @file i2c_follower_example.c
 * @brief I2C examples functions
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "sl_si91x_peripheral_i2c.h"
#include "i2c_follower_example.h"
#include "rsi_debug.h"
#include "rsi_rom_egpio.h"
#include "rsi_power_save.h"
#include "rsi_rom_clks.h"
#include "rsi_rom_ulpss_clk.h"

/*******************************************************************************
 ***************************  Defines / Macros  ********************************
 ******************************************************************************/
#define SIZE_BUFFERS     15           // Size of buffer
#define OWN_I2C_ADDR     0x50         // Own I2C address
#define RX_LENGTH        SIZE_BUFFERS // Number of bytes to receive
#define TX_LENGTH        SIZE_BUFFERS // Number of bytes to send
#define OFFSET_LENGTH    1            // Offset length
#define FIFO_THRESHOLD   0x0          // FIFO threshold
#define ZERO_FLAG        0            // Zero flag, No argument
#define PINMUX_MODE      6            // I2C pinmux mode
#define PORT_ZERO        0            // Port zero
#define HP_MAX_GPIO      64           // High Power GPIO Maximum number
#define LAST_DATA_COUNT  0            // Last read-write count
#define DATA_COUNT       1            // Last second data count for verification
#define BIT_SET          1            // Set bit
#define STOP_BIT         9            // Bit to send stop command
#define RW_MASK_BIT      8            // Bit to mask read and write
#define ULP_GPIO_SDA     10           // SDA ULP GPIO Pin number
#define ULP_GPIO_SCL     11           // SCL ULP GPIO Pin number
#define INTERNAL_PULLUP  1            // Internal Pull-up enable
#define I2C_INSTANCE     0            // I2C Instance for Pin configuration
#define I2C              I2C0         // I2C Instance
#define MAX_7BIT_ADDRESS 127          // Maximum 7-bit address
/*******************************************************************************
 ******************************  Data Types  ***********************************
 ******************************************************************************/
// Structure to hold the pin configuration
typedef const struct {
  uint8_t port;    // GPIO port
  uint8_t pin;     // GPIO pin
  uint8_t mode;    // GPIO mode
  uint8_t pad_sel; // GPIO pad selection
} I2C_PIN_;

// Enum for different transmission scenarios
typedef enum {
  SEND_DATA,              // Send mode
  RECEIVE_DATA,           // Receive mode
  TRANSMISSION_COMPLETED, // Transmission completed mode
} i2c_mode_enum_t;

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
#if (I2C_INSTANCE == 0)
// SCL, GPIO: 75, Exapansion Header: 5
// SDA, GPIO: 74, Exapansion Header: 3
static I2C_PIN scl = { RTE_I2C0_SCL_PORT, RTE_I2C0_SCL_PIN, RTE_I2C0_SCL_MUX, RTE_I2C0_SCL_PAD };
static I2C_PIN sda = { RTE_I2C0_SDA_PORT, RTE_I2C0_SDA_PIN, RTE_I2C0_SDA_MUX, RTE_I2C0_SDA_PAD };
#endif

#if (I2C_INSTANCE == 1)
// SCL, GPIO: 50, Board Pin: P19
// SDA, GPIO: 51, Board Pin: P20
static I2C_PIN scl = { RTE_I2C1_SCL_PORT, RTE_I2C1_SCL_PIN, RTE_I2C1_SCL_MUX, RTE_I2C1_SCL_PAD };
static I2C_PIN sda = { RTE_I2C1_SDA_PORT, RTE_I2C1_SDA_PIN, RTE_I2C1_SDA_MUX, RTE_I2C1_SDA_PAD };
#endif

#if (I2C_INSTANCE == 2)
// SCL, ULP_GPIO: 5, Exapansion Header: 13
// SDA, ULP_GPIO: 4, Exapansion Header: 11
static I2C_PIN scl = { RTE_I2C2_SCL_PORT, RTE_I2C2_SCL_PIN, RTE_I2C2_SCL_MUX, 0 };
static I2C_PIN sda = { RTE_I2C2_SDA_PORT, RTE_I2C2_SDA_PIN, RTE_I2C2_SDA_MUX, 0 };
#endif

static i2c_mode_enum_t current_mode = RECEIVE_DATA;
boolean_t i2c_send_complete         = false;
boolean_t i2c_receive_complete      = false;
boolean_t send_data_flag            = false;
boolean_t receive_data_flag         = false;

static uint32_t write_number = 0;
static uint32_t write_count  = 0;
static uint32_t read_number  = 0;
static uint32_t read_count   = 0;
static uint8_t *write_data;
static uint8_t *read_data;

static uint8_t write_buffer[SIZE_BUFFERS];
static uint8_t read_buffer[SIZE_BUFFERS + OFFSET_LENGTH];

/*******************************************************************************
 **********************  Local Function prototypes   ***************************
 ******************************************************************************/
static void pin_configurations(void);
static void i2c_send_data(const uint8_t *data, uint32_t data_length, uint16_t follower_address);
static void i2c_receive_data(uint8_t *data, uint32_t data_length, uint16_t follower_address);
static void i2c_clock_init(I2C_TypeDef *i2c);
static void compare_data(void);
static void handle_follower_transmit_irq(void);
static void handle_follower_receive_irq(void);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
/*******************************************************************************
 * I2C example initialization function
 ******************************************************************************/
void i2c_follower_example_init(void)
{
  i2c_clock_init(I2C);
  sl_i2c_init_params_t config;
  // Filling the structure with default values.
  config.clhr = SL_I2C_STANDARD_BUS_SPEED;
  config.freq = sl_si91x_i2c_get_frequency(I2C);
  config.mode = SL_I2C_FOLLOWER_MODE;
  // Passing the structure and i2c instance for the initialization.
  sl_si91x_i2c_init(I2C, &config);
  DEBUGOUT("I2C follower is initialized successfully \n");
  // Pin is configured here.
  pin_configurations();
  DEBUGOUT("Pins are configured successfully \n");
  // Generating a buffer with values that needs to be sent.
  for (uint32_t loop = 0; loop < SIZE_BUFFERS; loop++) {
    write_buffer[loop] = (loop + 0x1);
    read_buffer[loop]  = 0;
  }
  receive_data_flag = true;
}

/*******************************************************************************
 * Function will run continuously in while loop
 ******************************************************************************/
void i2c_follower_example_process_action(void)
{
  // In switch case, according to the current mode, the transmission is executed.
  // First EEPROM write is executes i.e., I2C send.
  // After that offset address is sent to the follower device.
  // Now data is read from the EEPROM using I2C recevie.
  switch (current_mode) {
    case RECEIVE_DATA:
      if (receive_data_flag) {
        // Validation for executing the API only once.
        i2c_receive_data(read_buffer, RX_LENGTH + OFFSET_LENGTH, OWN_I2C_ADDR);
        receive_data_flag = false;
      }
      if (i2c_receive_complete) {
        // It waits till i2c_receive_complete is true in IRQ handler.
        current_mode         = SEND_DATA;
        i2c_receive_complete = false;
        send_data_flag       = true;
      }
      break;
    case SEND_DATA:
      if (send_data_flag) {
        // Validation for executing the API only once.
        i2c_send_data(write_buffer, TX_LENGTH + OFFSET_LENGTH, OWN_I2C_ADDR);
        send_data_flag = false;
      }
      if (i2c_send_complete) {
        // It waits till i2c_send_complete is true in IRQ handler.
        current_mode      = TRANSMISSION_COMPLETED;
        send_data_flag    = true;
        i2c_send_complete = false;
        // After the receive is completed, input and output data is compared and
        // output is printed on console.
        compare_data();
      }
      break;
    case TRANSMISSION_COMPLETED:
      break;
    default:
      break;
  }
}

/*******************************************************************************
 * Function to send the data using I2C.
 * Here the FIFO threshold, direction and interrupts are configured.
 * 
 * @param[in] data (uint8_t) Constant pointer to the data which needs to be transferred.
 * @param[in] data_length (uint32_t) Length of the data that needs to be received.
 * @param[in] I2C device own address
 * @return none
 ******************************************************************************/
static void i2c_send_data(const uint8_t *data, uint32_t data_length, uint16_t follower_address)
{
  // Disables the interrupts.
  sl_si91x_i2c_disable_interrupts(I2C, ZERO_FLAG);
  // Updates the variables which are required for trasmission.
  write_data   = (uint8_t *)data;
  write_count  = 0;
  write_number = data_length;
  // Disables the I2C peripheral.
  sl_si91x_i2c_disable(I2C);
  // Setting the follower mask address, here leader behaves like follower.
  sl_si91x_i2c_set_follower_mask_address(I2C, follower_address);
  // Configures the FIFO threshold.
  sl_si91x_i2c_set_tx_threshold(I2C, FIFO_THRESHOLD);
  // Enables the I2C peripheral.
  sl_si91x_i2c_enable(I2C);
  // Configures the transmit empty interrupt.
  sl_si91x_i2c_set_interrupts(I2C, SL_I2C_EVENT_TRANSMIT_EMPTY);
  // Enables the interrupt.
  sl_si91x_i2c_enable_interrupts(I2C, ZERO_FLAG);
}

/*******************************************************************************
* Function to receive the data using I2C.
 * Here the FIFO threshold, direction and interrupts are configured.
 * 
 * @param[in] data (uint8_t) Constant pointer to the data which needs to be received.
 * @param[in] data_length (uint32_t) Length of the data that needs to be received.
 * @param[in] I2C device own address
 * @return none
 ******************************************************************************/
static void i2c_receive_data(uint8_t *data, uint32_t data_length, uint16_t follower_address)
{
  // Disables the interrupts.
  sl_si91x_i2c_disable_interrupts(I2C, ZERO_FLAG);
  // Updates the variables which are required for trasmission.
  read_data   = (uint8_t *)data;
  read_count  = 0;
  read_number = data_length;
  // Disables the I2C peripheral.
  sl_si91x_i2c_disable(I2C);
  // Setting the follower mask address, here leader behaves like follower.
  sl_si91x_i2c_set_follower_mask_address(I2C, follower_address);
  // Configures the FIFO threshold.
  sl_si91x_i2c_set_rx_threshold(I2C, FIFO_THRESHOLD);
  // Enables the I2C peripheral.
  sl_si91x_i2c_enable(I2C);
  // Sets the direction to read.
  sl_si91x_i2c_control_direction(I2C, SL_I2C_READ_MASK);
  // Configures the receive full interrupt.
  sl_si91x_i2c_set_interrupts(I2C, SL_I2C_EVENT_RECEIVE_FULL);
  // Enables the interrupt.
  sl_si91x_i2c_enable_interrupts(I2C, ZERO_FLAG);
}

/*******************************************************************************
 * Function to compare the input and output data
 * 
 * @param none
 * @return none
 ******************************************************************************/
static void compare_data(void)
{
  uint32_t data_index = 0;
  for (data_index = 0; data_index < SIZE_BUFFERS; data_index++) {
    // If the read_buffer and buffer are same, it will be continued else, the for
    // loop will be break.
    if (write_buffer[data_index] != read_buffer[data_index]) {
      break;
    }
  }
  if (data_index == SIZE_BUFFERS) {
    DEBUGOUT("Leader-follower read-write data comparison is successful, Test Case Passed \n");
  } else {
    DEBUGOUT("Leader-follower read-write data comparison is not successful, Test Case Failed \n");
  }
}

/*******************************************************************************
 * To configure the clock and power up the peripheral according to the 
 * I2C instance.
 * 
 * @param none
 * @return none
 ******************************************************************************/
static void i2c_clock_init(I2C_TypeDef *i2c)
{
  if ((uint32_t)i2c == I2C0_BASE) {
#if defined(CHIP_917)
    // Powering up the peripheral.
    RSI_PS_M4ssPeriPowerUp(M4SS_PWRGATE_ULP_EFUSE_PERI);
#else
    // Powering up the peripheral.
    RSI_PS_M4ssPeriPowerUp(M4SS_PWRGATE_ULP_PERI1);
#endif
    // Initialize the I2C clock.
    RSI_CLK_I2CClkConfig(M4CLK, 1, I2C1_INSTAN);
  }
  if ((uint32_t)i2c == I2C1_BASE) {
#if defined(CHIP_917)
    // Powering up the peripheral.
    RSI_PS_M4ssPeriPowerUp(M4SS_PWRGATE_ULP_EFUSE_PERI);
#else
    // Powering up the peripheral.
    RSI_PS_M4ssPeriPowerUp(M4SS_PWRGATE_ULP_PERI3);
#endif
    // Initialize the I2C clock.
    RSI_CLK_I2CClkConfig(M4CLK, 1, I2C2_INSTAN);
  }
  if ((uint32_t)i2c == I2C2_BASE) {
    // Powering up the peripheral.
    RSI_PS_UlpssPeriPowerUp(ULPSS_PWRGATE_ULP_I2C);
    // Initialize the I2C clock.
    RSI_ULPSS_PeripheralEnable(ULPCLK, ULP_I2C_CLK, ENABLE_STATIC_CLK);
  }
}

/*******************************************************************************
 * Function to set the Pin configuration for I2C.
 * It configures the SDA and SCL pins.
 * 
 * @param none
 * @return none
 ******************************************************************************/
static void pin_configurations(void)
{
#ifndef SI917_RADIO_BOARD_V2
#if (I2C_INSTANCE == 0)
  //SCL
  RSI_EGPIO_UlpPadReceiverEnable((uint8_t)(scl.pin - HP_MAX_GPIO));
  RSI_EGPIO_SetPinMux(EGPIO1, PORT_ZERO, (uint8_t)(scl.pin - HP_MAX_GPIO), PINMUX_MODE);
  RSI_EGPIO_PadSelectionEnable(scl.pad_sel);
  //configure DIN0 pin
  RSI_EGPIO_SetPinMux(EGPIO, scl.port, scl.pin, scl.mode);
#if defined(ROM_BYPASS)
  // Configuring internal pullup for follower mode
  egpio_ulp_pad_driver_disable_state(ULP_GPIO_SCL, INTERNAL_PULLUP);
#endif
  //SDA
  RSI_EGPIO_UlpPadReceiverEnable((uint8_t)(sda.pin - HP_MAX_GPIO));
  RSI_EGPIO_SetPinMux(EGPIO1, PORT_ZERO, (uint8_t)(sda.pin - HP_MAX_GPIO), PINMUX_MODE);
  RSI_EGPIO_PadSelectionEnable(sda.pad_sel);
  //configure DIN0 pin
  RSI_EGPIO_SetPinMux(EGPIO, sda.port, sda.pin, sda.mode);
#if defined(ROM_BYPASS)
  // Configuring internal pullup for follower mode
  egpio_ulp_pad_driver_disable_state(ULP_GPIO_SDA, INTERNAL_PULLUP);
#endif
#endif
#else
  RSI_EGPIO_PadSelectionEnable(scl.pad_sel);
  RSI_EGPIO_PadReceiverEnable(scl.pin);
  RSI_EGPIO_SetPinMux(EGPIO, scl.port, scl.pin, scl.mode);
#if defined(ROM_BYPASS)
  egpio_pad_driver_disable_state(scl.pin, INTERNAL_PULLUP);
#endif
  //SDA
  RSI_EGPIO_PadSelectionEnable(sda.pad_sel);
  RSI_EGPIO_PadReceiverEnable(sda.pin);
  RSI_EGPIO_SetPinMux(EGPIO, sda.port, sda.pin, sda.mode);
#if defined(ROM_BYPASS)
  egpio_pad_driver_disable_state(sda.pin, INTERNAL_PULLUP);
#endif
#endif // I2C_INSTANCE 0

#if (I2C_INSTANCE == 1)
  //SCL
  RSI_EGPIO_PadSelectionEnable(scl.pad_sel);
  RSI_EGPIO_PadReceiverEnable(scl.pin);
  RSI_EGPIO_SetPinMux(EGPIO, scl.port, scl.pin, scl.mode);
#if defined(ROM_BYPASS)
  egpio_pad_driver_disable_state(scl.pin, INTERNAL_PULLUP);
#endif
  //SDA
  RSI_EGPIO_PadSelectionEnable(sda.pad_sel);
  RSI_EGPIO_PadReceiverEnable(sda.pin);
  RSI_EGPIO_SetPinMux(EGPIO, sda.port, sda.pin, sda.mode);
#if defined(ROM_BYPASS)
  egpio_pad_driver_disable_state(sda.pin, INTERNAL_PULLUP);
#endif
#endif // I2C_INSTANCE 1

#if (I2C_INSTANCE == 2)
  // SCL
  RSI_EGPIO_UlpPadReceiverEnable(scl.pin);
  RSI_EGPIO_SetPinMux(EGPIO1, scl.port, scl.pin, scl.mode);
#if defined(ROM_BYPASS)
  egpio_ulp_pad_driver_disable_state(scl.pin, INTERNAL_PULLUP);
#endif
  // SDA
  RSI_EGPIO_UlpPadReceiverEnable(sda.pin);
  RSI_EGPIO_SetPinMux(EGPIO1, sda.port, sda.pin, sda.mode);
#if defined(ROM_BYPASS)
  egpio_ulp_pad_driver_disable_state(sda.pin, INTERNAL_PULLUP);
#endif
#endif // I2C_INSTANCE 2
}

/*******************************************************************************
 * Function to handle the transmit IRQ.
 * Transmit empty interrupt is monitored and byte by byte data is transmitted.
 * If the data transmission is completed, it clears and disables the interrupt.
 * 
 * @param none
 * @return none
 ******************************************************************************/
static void handle_follower_transmit_irq(void)
{
  if (write_number > LAST_DATA_COUNT) {
    if (write_number == DATA_COUNT) {
      I2C->IC_DATA_CMD = (uint32_t)write_data[write_count] | (BIT_SET << STOP_BIT);
    } else {
      // waiting for Slave to release SCL
      while (!I2C->IC_STATUS_b.SLV_HOLD_TX_FIFO_EMPTY)
        ;
      sl_si91x_i2c_tx(I2C, write_data[write_count]);
    }
    write_count++;
    write_number--;
  } else {
    sl_si91x_i2c_clear_interrupts(I2C, SL_I2C_EVENT_TRANSMIT_EMPTY);
    sl_si91x_i2c_disable_interrupts(I2C, ZERO_FLAG);
    i2c_send_complete = true;
  }
}

/*******************************************************************************
 * Function to handle the receive IRQ.
 * Receive full interrupt is monitored and byte by byte data is received.
 * If the data receive is completed, it clears and disables the interrupt.
 * 
 * @param none
 * @return none
 ******************************************************************************/
static void handle_follower_receive_irq(void)
{
  if (read_number > LAST_DATA_COUNT) {
    read_data[read_count] = I2C->IC_DATA_CMD_b.DAT;
    read_count++;
    read_number--;
  }
  if (read_number == LAST_DATA_COUNT) {
    sl_si91x_i2c_clear_interrupts(I2C, SL_I2C_EVENT_RECEIVE_FULL);
    sl_si91x_i2c_disable_interrupts(I2C, ZERO_FLAG);
    i2c_receive_complete = true;
  }
}

/*******************************************************************************
 * IRQ handler for I2C0.
 ******************************************************************************/
void I2C0_IRQHandler(void)
{
  uint32_t status = 0;
  // Checking interrupt status
  status = I2C0->IC_INTR_STAT;
  if (status & SL_I2C_EVENT_TRANSMIT_ABORT) {
    uint32_t tx_abrt = I2C0->IC_TX_ABRT_SOURCE;
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_NOACK) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C0->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_READ) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C0->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_10B_READ_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_DISABLED) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_FLUSH_TX_FIFO) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_READ_INTX) {
    }
    if (tx_abrt & SL_I2C_TX_TX_FLUSH_CNT) {
    }
    if (tx_abrt & SL_I2C_ABORT_USER_ABORT) {
    }
    if (tx_abrt & SL_I2C_ABORT_SDA_STUCK_AT_LOW) {
      I2C0->IC_ENABLE_b.SDA_STUCK_RECOVERY_ENABLE = 0x1;
    }
    // Clearing all interrupts
    uint32_t clear = I2C0->IC_CLR_INTR;
    // Disables the interrupts.
    sl_si91x_i2c_disable_interrupts(I2C0, SL_I2C_EVENT_TRANSMIT_EMPTY);
  }
  if (status & (SL_I2C_EVENT_SCL_STUCK_AT_LOW)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear       = I2C0->IC_CLR_INTR;
    I2C0->IC_ENABLE_b.EN = 0;
    return;
  }
  if (status & (SL_I2C_EVENT_MST_ON_HOLD)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C0->IC_CLR_INTR;
    return;
  }
  if (status & (SL_I2C_EVENT_START_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C0->IC_CLR_START_DET_b.CLR_START_DET;
    return;
  }
  if (status & (SL_I2C_EVENT_STOP_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear     = I2C0->IC_CLR_STOP_DET_b.CLR_STOP_DET;
    uint32_t maskReg   = 0;
    maskReg            = I2C0->IC_INTR_MASK;
    I2C0->IC_INTR_MASK = (maskReg & (~SL_I2C_EVENT_RECEIVE_FULL));
    return;
  }
  if (status & (SL_I2C_EVENT_ACTIVITY_ON_BUS)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C0->IC_CLR_ACTIVITY_b.CLR_ACTIVITY;
    return;
  }
  if (status & (SL_I2C_EVENT_READ_REQ)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C0->IC_CLR_RD_REQ_b.CLR_RD_REQ;
    return;
  }
  if (status & SL_I2C_EVENT_TRANSMIT_EMPTY) {
    handle_follower_transmit_irq();
  }
  if (status & SL_I2C_EVENT_RECEIVE_FULL) {
    handle_follower_receive_irq();
  }
  if (status & (SL_I2C_EVENT_RECEIVE_UNDER)) {
    uint32_t clear = I2C0->IC_CLR_RX_UNDER_b.CLR_RX_UNDER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_OVER)) {
    uint32_t clear = I2C0->IC_CLR_RX_OVER_b.CLR_RX_OVER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_DONE)) {
    sl_si91x_i2c_clear_interrupts(I2C0, SL_I2C_EVENT_RECEIVE_DONE);
    return;
  }
  if (status & (SL_I2C_EVENT_GENERAL_CALL)) {
    sl_si91x_i2c_clear_interrupts(I2C0, SL_I2C_EVENT_GENERAL_CALL);
    return;
  }
  if (status & (SL_I2C_EVENT_RESTART_DET)) {
    sl_si91x_i2c_clear_interrupts(I2C0, SL_I2C_EVENT_RESTART_DET);
    return;
  }
}

/*******************************************************************************
 * IRQ handler for I2C1.
 ******************************************************************************/
void I2C1_IRQHandler(void)
{
  uint32_t status = 0;
  // Checking interrupt status
  status = I2C1->IC_INTR_STAT;
  if (status & SL_I2C_EVENT_TRANSMIT_ABORT) {
    uint32_t tx_abrt = I2C1->IC_TX_ABRT_SOURCE;
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_NOACK) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C1->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_READ) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C1->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_10B_READ_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_DISABLED) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_FLUSH_TX_FIFO) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_READ_INTX) {
    }
    if (tx_abrt & SL_I2C_TX_TX_FLUSH_CNT) {
    }
    if (tx_abrt & SL_I2C_ABORT_USER_ABORT) {
    }
    if (tx_abrt & SL_I2C_ABORT_SDA_STUCK_AT_LOW) {
      I2C1->IC_ENABLE_b.SDA_STUCK_RECOVERY_ENABLE = 0x1;
    }
    // Clearing all interrupts
    uint32_t clear = I2C1->IC_CLR_INTR;
    // Disables the interrupts.
    sl_si91x_i2c_disable_interrupts(I2C1, SL_I2C_EVENT_TRANSMIT_EMPTY);
  }
  if (status & (SL_I2C_EVENT_SCL_STUCK_AT_LOW)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear       = I2C1->IC_CLR_INTR;
    I2C1->IC_ENABLE_b.EN = 0;
    return;
  }
  if (status & (SL_I2C_EVENT_MST_ON_HOLD)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C1->IC_CLR_INTR;
    return;
  }
  if (status & (SL_I2C_EVENT_START_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C1->IC_CLR_START_DET_b.CLR_START_DET;
    return;
  }
  if (status & (SL_I2C_EVENT_STOP_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear     = I2C1->IC_CLR_STOP_DET_b.CLR_STOP_DET;
    uint32_t maskReg   = 0;
    maskReg            = I2C1->IC_INTR_MASK;
    I2C0->IC_INTR_MASK = (maskReg & (~SL_I2C_EVENT_RECEIVE_FULL));
    return;
  }
  if (status & (SL_I2C_EVENT_ACTIVITY_ON_BUS)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C1->IC_CLR_ACTIVITY_b.CLR_ACTIVITY;
    return;
  }
  if (status & (SL_I2C_EVENT_READ_REQ)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C1->IC_CLR_RD_REQ_b.CLR_RD_REQ;
    return;
  }
  if (status & SL_I2C_EVENT_TRANSMIT_EMPTY) {
    handle_follower_transmit_irq();
  }
  if (status & SL_I2C_EVENT_RECEIVE_FULL) {
    handle_follower_receive_irq();
  }
  if (status & (SL_I2C_EVENT_RECEIVE_UNDER)) {
    uint32_t clear = I2C1->IC_CLR_RX_UNDER_b.CLR_RX_UNDER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_OVER)) {
    uint32_t clear = I2C1->IC_CLR_RX_OVER_b.CLR_RX_OVER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_DONE)) {
    sl_si91x_i2c_clear_interrupts(I2C1, SL_I2C_EVENT_RECEIVE_DONE);
    return;
  }
  if (status & (SL_I2C_EVENT_GENERAL_CALL)) {
    sl_si91x_i2c_clear_interrupts(I2C1, SL_I2C_EVENT_GENERAL_CALL);
    return;
  }
  if (status & (SL_I2C_EVENT_RESTART_DET)) {
    sl_si91x_i2c_clear_interrupts(I2C1, SL_I2C_EVENT_RESTART_DET);
    return;
  }
}

/*******************************************************************************
 * IRQ handler for I2C2.
 ******************************************************************************/
void I2C2_IRQHandler(void)
{
  uint32_t status = 0;
  // Checking interrupt status
  status = I2C2->IC_INTR_STAT;
  if (status & SL_I2C_EVENT_TRANSMIT_ABORT) {
    uint32_t tx_abrt = I2C2->IC_TX_ABRT_SOURCE;
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_NOACK) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C2->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_GENERAL_CALL_READ) {
      // Clearing interrupt by reading the respective bit
      uint32_t clear = I2C2->IC_CLR_GEN_CALL_b.CLR_GEN_CALL;
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_ACK) {
    }
    if (tx_abrt & SL_I2C_ABORT_HIGH_SPEED_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_START_BYTE_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_10B_READ_NO_RESTART) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_DISABLED) {
    }
    if (tx_abrt & SL_I2C_ABORT_MASTER_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_ARBITRATION_LOST) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_FLUSH_TX_FIFO) {
    }
    if (tx_abrt & SL_I2C_ABORT_SLAVE_READ_INTX) {
    }
    if (tx_abrt & SL_I2C_TX_TX_FLUSH_CNT) {
    }
    if (tx_abrt & SL_I2C_ABORT_USER_ABORT) {
    }
    if (tx_abrt & SL_I2C_ABORT_SDA_STUCK_AT_LOW) {
      I2C2->IC_ENABLE_b.SDA_STUCK_RECOVERY_ENABLE = 0x1;
    }
    // Clearing all interrupts
    uint32_t clear = I2C2->IC_CLR_INTR;
    // Disables the interrupts.
    sl_si91x_i2c_disable_interrupts(I2C2, SL_I2C_EVENT_TRANSMIT_EMPTY);
  }
  if (status & (SL_I2C_EVENT_SCL_STUCK_AT_LOW)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear       = I2C2->IC_CLR_INTR;
    I2C2->IC_ENABLE_b.EN = 0;
    return;
  }
  if (status & (SL_I2C_EVENT_MST_ON_HOLD)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C2->IC_CLR_INTR;
    return;
  }
  if (status & (SL_I2C_EVENT_START_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C2->IC_CLR_START_DET_b.CLR_START_DET;
    return;
  }
  if (status & (SL_I2C_EVENT_STOP_DETECT)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear     = I2C2->IC_CLR_STOP_DET_b.CLR_STOP_DET;
    uint32_t maskReg   = 0;
    maskReg            = I2C2->IC_INTR_MASK;
    I2C0->IC_INTR_MASK = (maskReg & (~SL_I2C_EVENT_RECEIVE_FULL));
    return;
  }
  if (status & (SL_I2C_EVENT_ACTIVITY_ON_BUS)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C2->IC_CLR_ACTIVITY_b.CLR_ACTIVITY;
    return;
  }
  if (status & (SL_I2C_EVENT_READ_REQ)) {
    // Clearing interrupt by reading the respective bit
    uint32_t clear = I2C2->IC_CLR_RD_REQ_b.CLR_RD_REQ;
    return;
  }
  if (status & SL_I2C_EVENT_TRANSMIT_EMPTY) {
    handle_follower_transmit_irq();
  }
  if (status & SL_I2C_EVENT_RECEIVE_FULL) {
    handle_follower_receive_irq();
  }
  if (status & (SL_I2C_EVENT_RECEIVE_UNDER)) {
    uint32_t clear = I2C2->IC_CLR_RX_UNDER_b.CLR_RX_UNDER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_OVER)) {
    uint32_t clear = I2C2->IC_CLR_RX_OVER_b.CLR_RX_OVER;
    return;
  }
  if (status & (SL_I2C_EVENT_RECEIVE_DONE)) {
    sl_si91x_i2c_clear_interrupts(I2C2, SL_I2C_EVENT_RECEIVE_DONE);
    return;
  }
  if (status & (SL_I2C_EVENT_GENERAL_CALL)) {
    sl_si91x_i2c_clear_interrupts(I2C2, SL_I2C_EVENT_GENERAL_CALL);
    return;
  }
  if (status & (SL_I2C_EVENT_RESTART_DET)) {
    sl_si91x_i2c_clear_interrupts(I2C2, SL_I2C_EVENT_RESTART_DET);
    return;
  }
}
