#pragma once

#ifdef SL_UART
#include "sl_device_registers.h"
#include "sl_uart.h"

// Use HFRCO directly with no DPLL
//#define PLATFORM_CLOCK_USE_HFRCO
//#define PLATFORM_CLOCK_USE_HFXO
//#define PLATFORM_CLOCK_USE_LFXO

//#define PLATFORM_CPU_CLOCK           72000000UL
//#define SL_CYCLE_COUNT_PER_MILLISECOND (PLATFORM_CPU_CLOCK / 1000)

//#define PLATFORM_SDIO_USE_AUXHFRCO
//#define PLATFORM_SDIO_CLOCK_DIVIDER     ( 1 )
//#define PLATFORM_SDIO_NEEDS_PULLUPS
//#define PLATFORM_AUXHFRCO_CLOCK      16000000U

//#define BSP_CLK_LFXO_PRESENT         (1)
//#define BSP_CLK_LFXO_INIT             CMU_LFXOINIT_DEFAULT
//#define BSP_CLK_LFXO_CTUNE           (32U)
//#define BSP_CLK_LFXO_FREQ            (32768U)
//
//#define BSP_CLK_HFXO_PRESENT         (1)
//#define BSP_CLK_HFXO_FREQ            (50000000UL)
//#define BSP_CLK_HFXO_CTUNE           (342)
//#define BSP_CLK_HFXO_INIT             CMU_HFXOINIT_DEFAULT
//#define BSP_CLK_HFXO_CTUNE_TOKEN     (0)

#define DEFAULT_UART USART0

//#define SL_WIFI_RESET_PORT SL_GPIO_PORT_C
//#define SL_WIFI_RESET_PIN  4

//#define SL_WIFI_WAKE_PORT SL_GPIO_PORT_A
//#define SL_WIFI_WAKE_PIN  12

#define SL_UART_VCOM_PORT SL_GPIO_PORT_D
#define SL_UART_VCOM_PIN  4
static const sl_gpio_t vcom_enable_pin = { SL_UART_VCOM_PORT, SL_UART_VCOM_PIN };

#define DEFAULT_UART_PIN_CONFIG &default_uart_pin_configuration

#define UART_CLOCK  cmuClock_USART0
#define UART_RX_IRQ USART0_RX_IRQn

/* Note: This creates a static instance for each C file that includes this header and references the variable */
static const sl_uart_pin_configuration_t default_uart_pin_configuration = {
  .tx_port     = SL_GPIO_PORT_A,
  .tx_pin      = 5,
  .rx_port     = SL_GPIO_PORT_A,
  .rx_pin      = 6,
  .cts_port    = SL_GPIO_PORT_A,
  .cts_pin     = 4,
  .rts_port    = SL_GPIO_PORT_C,
  .rts_pin     = 1,
  .uart_number = 0,
  //.route_loc = USART_ROUTELOC0_RXLOC_LOC4 | USART_ROUTELOC0_TXLOC_LOC4,
};
#endif

typedef struct {
  unsigned char port;
  unsigned char pin;
} sl_pin_t;

#define PIN(port_id, pin_id)                 \
  (sl_pin_t)                                 \
  {                                          \
    .port = gpioPort##port_id, .pin = pin_id \
  }

#define SLEEP_CONFIRM_PIN  PIN(D, 2)
#define WAKE_INDICATOR_PIN PIN(D, 3)
#define RESET_PIN          PIN(B, 0)
#define INTERRUPT_PIN      PIN(B, 1)

#define SPI_CLOCK_PIN PIN(C, 2)
#define SPI_MOSI_PIN  PIN(C, 0)
#define SPI_MISO_PIN  PIN(C, 1)
#define SPI_CS_PIN    PIN(C, 3)

#define PACKET_PENDING_INT_PRI 3
