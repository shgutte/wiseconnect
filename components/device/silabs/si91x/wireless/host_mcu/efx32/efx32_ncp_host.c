/*******************************************************************************
* @file  efx32_ncp_host.c
* @brief 
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

#include "sl_wifi_constants.h"
#include "sl_si91x_host_interface.h"
#include "sl_board_configuration.h"
#include "sl_status.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "cmsis_os2.h"
#include "dmadrv.h"
#include "gpiointerrupt.h"
#include "sl_si91x_status.h"
#include "sl_rsi_utility.h"
#include "sl_constants.h"
#include <stdbool.h>
#include <string.h>
#include "FreeRTOS.h"

static bool dma_callback(unsigned int channel, unsigned int sequenceNo, void *userParam);

unsigned int rx_ldma_channel;
unsigned int tx_ldma_channel;
osMutexId_t spi_transfer_mutex = 0;

static uint32_t dummy_buffer;

// LDMA descriptor and transfer configuration structures for USART TX channel
LDMA_Descriptor_t ldmaTXDescriptor;
LDMA_TransferCfg_t ldmaTXConfig;

// LDMA descriptor and transfer configuration structures for USART RX channel
LDMA_Descriptor_t ldmaRXDescriptor;
LDMA_TransferCfg_t ldmaRXConfig;

static osSemaphoreId_t transfer_done_semaphore = NULL;

static bool dma_callback(unsigned int channel, unsigned int sequenceNo, void *userParam)
{
  UNUSED_PARAMETER(channel);
  UNUSED_PARAMETER(sequenceNo);
  UNUSED_PARAMETER(userParam);
  osSemaphoreRelease(transfer_done_semaphore);
  return false;
}

static void gpio_interrupt(uint8_t interrupt_number)
{
  UNUSED_PARAMETER(interrupt_number);
  sl_si91x_host_set_bus_event(NCP_HOST_BUS_RX_EVENT);
  //  GPIO_IntClear(0xAAAA);
}

void sl_si91x_host_set_sleep_indicator(void)
{
  GPIO_PinOutSet(SLEEP_CONFIRM_PIN.port, SLEEP_CONFIRM_PIN.pin);
}

void sl_si91x_host_clear_sleep_indicator(void)
{
  GPIO_PinOutClear(SLEEP_CONFIRM_PIN.port, SLEEP_CONFIRM_PIN.pin);
}

uint32_t sl_si91x_host_get_wake_indicator(void)
{
  return GPIO_PinInGet(WAKE_INDICATOR_PIN.port, WAKE_INDICATOR_PIN.pin);
}

sl_status_t sl_si91x_host_init(void)
{
  // Enable clock (not needed on xG21)
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure SPI bus pins
  GPIO_PinModeSet(SPI_MISO_PIN.port, SPI_MISO_PIN.pin, gpioModeInput, 0);
  GPIO_PinModeSet(SPI_MOSI_PIN.port, SPI_MOSI_PIN.pin, gpioModePushPull, 0);
  GPIO_PinModeSet(SPI_CLOCK_PIN.port, SPI_CLOCK_PIN.pin, gpioModePushPullAlternate, 0);
  GPIO_PinModeSet(SPI_CS_PIN.port, SPI_CS_PIN.pin, gpioModePushPull, 1);
#if (defined(EFR32MG24_BRD4187C) || defined(BRD4187C) || defined(EFR32MG24_BRD4186C) || defined(BRD4186C))
  // Enable clock (not needed on xG21)
  CMU_ClockEnable(cmuClock_USART0, true);
#else
  // Enable clock (not needed on xG21)
  CMU_ClockEnable(cmuClock_USART2, true);
#endif

  // Default asynchronous initializer (master mode, 1 Mbps, 8-bit data)
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  init.msbf         = true; // MSB first transmission for SPI compatibility
  init.autoCsEnable = true; // Allow the USART to assert CS
  init.baudrate     = 12500000;
  /*
	 * Route USART0 RX, TX, and CLK to the specified pins.  Note that CS is
	 * not controlled by USART0 so there is no write to the corresponding
	 * USARTROUTE register to do this.
	 */
  GPIO->USARTROUTE[2].RXROUTE = (SPI_MISO_PIN.port << _GPIO_USART_RXROUTE_PORT_SHIFT)
                                | (SPI_MISO_PIN.pin << _GPIO_USART_RXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[2].TXROUTE = (SPI_MOSI_PIN.port << _GPIO_USART_TXROUTE_PORT_SHIFT)
                                | (SPI_MOSI_PIN.pin << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[2].CLKROUTE = (SPI_CLOCK_PIN.port << _GPIO_USART_CLKROUTE_PORT_SHIFT)
                                 | (SPI_CLOCK_PIN.pin << _GPIO_USART_CLKROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[2].CSROUTE = (SPI_CS_PIN.port << _GPIO_USART_CSROUTE_PORT_SHIFT)
                                | (SPI_CS_PIN.pin << _GPIO_USART_CSROUTE_PIN_SHIFT);

  // Enable USART interface pins
  GPIO->USARTROUTE[2].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | // MISO
                                GPIO_USART_ROUTEEN_TXPEN | // MOSI
                                GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_CSPEN;

  // Set slew rate for alternate usage pins
  GPIO_SlewrateSet(SPI_CLOCK_PIN.port, 7, 7);

#if (defined(EFR32MG24_BRD4187C) || defined(BRD4187C) || defined(EFR32MG24_BRD4186C) || defined(BRD4186C))
  // Configure and enable USART0
  USART_InitSync(USART0, &init);
  USART0->TIMING |= /*USART_TIMING_TXDELAY_ONE | USART_TIMING_CSSETUP_ONE |*/ USART_TIMING_CSHOLD_ONE;
#else
  USART_InitSync(USART2, &init);
  USART2->TIMING |= /*USART_TIMING_TXDELAY_ONE | USART_TIMING_CSSETUP_ONE |*/ USART_TIMING_CSHOLD_ONE;
#endif
  //USART2->CTRL_SET |= USART_CTRL_SMSDELAY;
  if (transfer_done_semaphore == NULL) {
    transfer_done_semaphore = osSemaphoreNew(1, 0, NULL);
  }

  if (spi_transfer_mutex == 0) {
    spi_transfer_mutex = osMutexNew(NULL);
  }

  DMADRV_Init();
  DMADRV_AllocateChannel(&rx_ldma_channel, NULL);
  DMADRV_AllocateChannel(&tx_ldma_channel, NULL);

  // Start reset line low
  GPIO_PinModeSet(RESET_PIN.port, RESET_PIN.pin, gpioModePushPull, 0);

  // configure packet pending interrupt priority
  NVIC_SetPriority(GPIO_ODD_IRQn, PACKET_PENDING_INT_PRI);

  // Configure interrupt, sleep and wake confirmation pins
  GPIOINT_CallbackRegister(INTERRUPT_PIN.pin, gpio_interrupt);
  GPIO_PinModeSet(INTERRUPT_PIN.port, INTERRUPT_PIN.pin, gpioModeInputPullFilter, 0);
  GPIO_ExtIntConfig(INTERRUPT_PIN.port, INTERRUPT_PIN.pin, INTERRUPT_PIN.pin, true, false, true);
  GPIO_PinModeSet(SLEEP_CONFIRM_PIN.port, SLEEP_CONFIRM_PIN.pin, gpioModeWiredOrPullDown, 1);
  GPIO_PinModeSet(WAKE_INDICATOR_PIN.port, WAKE_INDICATOR_PIN.pin, gpioModeWiredOrPullDown, 0);

  return SL_STATUS_OK;
}

sl_status_t sl_si91x_host_deinit(void)
{
  return SL_STATUS_OK;
}

//void sl_si91x_host_enable_high_speed_bus()
//{
//#if (defined(EFR32MG24_BRD4187C) || defined(BRD4187C) || defined(EFR32MG24_BRD4186C) || defined(BRD4186C))
//  USART0->CTRL_SET |= USART_CTRL_SMSDELAY | USART_CTRL_SSSEARLY;
//  USART_BaudrateSyncSet(USART0, 0, 20000000);
//#else
//  USART2->CTRL_SET |= USART_CTRL_SMSDELAY | USART_CTRL_SSSEARLY;
//  USART_BaudrateSyncSet(USART2, 0, 20000000);
//#endif
//}
//
///*==================================================================*/
///**
// * @fn         sl_status_t sl_si91x_host_spi_transfer(const void *tx_buffer, void *rx_buffer, uint16_t buffer_length)
// * @param[in]  uint8_t *tx_buff, pointer to the buffer with the data to be transferred
// * @param[in]  uint8_t *rx_buff, pointer to the buffer to store the data received
// * @param[in]  uint16_t transfer_length, Number of bytes to send and receive
// * @param[in]  uint8_t mode, To indicate mode 8 BIT/32 BIT mode transfers.
// * @param[out] None
// * @return     0, 0=success
// * @section description
// * This API is used to transfer/receive data to the Wi-Fi module through the SPI interface.
// */
//sl_status_t sl_si91x_host_spi_transfer(const void *tx_buffer, void *rx_buffer, uint16_t buffer_length)
//{
//  osMutexAcquire(spi_transfer_mutex, 0xFFFFFFFFUL);
//
//  if (buffer_length < 16) {
//    uint8_t *tx = (tx_buffer != NULL) ? (uint8_t *)tx_buffer : (uint8_t *)&dummy_buffer;
//    uint8_t *rx = (rx_buffer != NULL) ? (uint8_t *)rx_buffer : (uint8_t *)&dummy_buffer;
//
//    while (buffer_length > 0) {
//#if (defined(EFR32MG24_BRD4187C) || defined(BRD4187C) || defined(EFR32MG24_BRD4186C) || defined(BRD4186C))
//      while (!(USART0->STATUS & USART_STATUS_TXBL)) {
//      }
//      USART0->TXDATA = (uint32_t)*tx;
//      while (!(USART0->STATUS & USART_STATUS_TXC)) {
//      }
//      *rx = (uint8_t)USART0->RXDATA;
//#else
//      while (!(USART2->STATUS & USART_STATUS_TXBL)) {
//      }
//      USART2->TXDATA = (uint32_t)*tx;
//      while (!(USART2->STATUS & USART_STATUS_TXC)) {
//      }
//      *rx = (uint8_t)USART2->RXDATA;
//#endif
//      if (tx_buffer != NULL) {
//        tx++;
//      }
//      if (rx_buffer != NULL) {
//        rx++;
//      }
//      buffer_length--;
//    }
//  } else {
//#if (defined(EFR32MG24_BRD4187C) || defined(BRD4187C) || defined(EFR32MG24_BRD4186C) || defined(BRD4186C))
//    if (tx_buffer == NULL) {
//      dummy_buffer = 0;
//      ldmaTXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2P_BYTE(&dummy_buffer, &(USART0->TXDATA), buffer_length);
//    } else {
//      ldmaTXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(tx_buffer, &(USART0->TXDATA), buffer_length);
//    }
//
//    if (rx_buffer == NULL) {
//      ldmaRXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2P_BYTE(&(USART0->RXDATA), &dummy_buffer, buffer_length);
//    } else {
//      ldmaRXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(USART0->RXDATA), rx_buffer, buffer_length);
//    }
//    // Transfer a byte on free space in the USART buffer
//    ldmaTXConfig = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART0_TXBL);
//
//    // Transfer a byte on receive data valid
//    ldmaRXConfig = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART0_RXDATAV);
//#else
//
//    if (tx_buffer == NULL) {
//      dummy_buffer = 0;
//      ldmaTXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2P_BYTE(&dummy_buffer, &(USART2->TXDATA), buffer_length);
//    } else {
//      ldmaTXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(tx_buffer, &(USART2->TXDATA), buffer_length);
//    }
//
//    if (rx_buffer == NULL) {
//      ldmaRXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2P_BYTE(&(USART2->RXDATA), &dummy_buffer, buffer_length);
//    } else {
//      ldmaRXDescriptor =
//        (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(USART2->RXDATA), rx_buffer, buffer_length);
//    }
//
//    // Transfer a byte on free space in the USART buffer
//    ldmaTXConfig = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART2_TXBL);
//
//    // Transfer a byte on receive data valid
//    ldmaRXConfig = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART2_RXDATAV);
//#endif
//    // Start both channels
//    DMADRV_LdmaStartTransfer(rx_ldma_channel, &ldmaRXConfig, &ldmaRXDescriptor, dma_callback, NULL);
//    DMADRV_LdmaStartTransfer(tx_ldma_channel, &ldmaTXConfig, &ldmaTXDescriptor, NULL, NULL);
//
//    if (osSemaphoreAcquire(transfer_done_semaphore, 1000) != osOK) {
//      BREAKPOINT();
//    }
//  }
//
//  osMutexRelease(spi_transfer_mutex);
//  return SL_STATUS_OK;
//}

void sl_si91x_host_hold_in_reset(void)
{
  GPIO_PinModeSet(RESET_PIN.port, RESET_PIN.pin, gpioModePushPull, 1);
  GPIO_PinOutClear(RESET_PIN.port, RESET_PIN.pin);
}

void sl_si91x_host_release_from_reset(void)
{
  GPIO_PinModeSet(RESET_PIN.port, RESET_PIN.pin, gpioModeWiredOrPullDown, 1);
}

void sl_si91x_host_enable_bus_interrupt(void)
{
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
}

void sl_si91x_host_disable_bus_interrupt(void)
{
  NVIC_DisableIRQ(GPIO_ODD_IRQn);
}
