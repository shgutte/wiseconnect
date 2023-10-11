/***************************************************************************/ /**
 * # License
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 *
 ******************************************************************************/
/**************************************************************************/  /**
 * @file unity_usart.h
 * @brief USART_Setup function that enables USART for Unity test reporting
 * @version 1.0.0
 ******************************************************************************
 * # License
 * <b>(C) Copyright 2014 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#ifndef UNITY_USART_H
#define UNITY_USART_H

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************/ /**
 * @brief Configure USART for Unity test reporting
 *****************************************************************************/
void UNITY_UsartSetup(void);

#ifdef __cplusplus
}
#endif

#endif // UNITY_USART_H
