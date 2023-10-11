/***************************************************************************/ /**
 * @file app.h
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef APP_H
#define APP_H

/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init(void);
#include <stdio.h>
#include <stdint.h>
#define SL_SI91X_APP_BUF_SIZE 1600
#define TX_RX_RATIO_ENABLE    1

/*=======================================================================*/
// TA buffer allocation parameters
/*=======================================================================*/

#ifndef TX_POOL_RATIO
#define TX_POOL_RATIO 1
#endif

#ifndef RX_POOL_RATIO
#define RX_POOL_RATIO 1
#endif

#ifndef GLOBAL_POOL_RATIO
#define GLOBAL_POOL_RATIO 1
#endif
/*=======================================================================*/

//! Enumeration for states in application
typedef enum sl_si91x_wlan_app_state_e {
  SL_SI91X_WLAN_INITIAL_STATE = 0,
  SL_SI91X_WLAN_UNCONNECTED_STATE,
  SL_SI91X_WLAN_NET_UP_STATE,
  SL_SI91X_POWERSAVE_STATE,
  SL_SI91X_WLAN_IP_CONFIG_RETRY_STATE,
  SL_SI91X_WLAN_SOCKET_CREATE_STATE,
  SL_SI91X_SEND_SOCKET_DATA_STATE,
  SL_SI91X_SOCKET_CLOSE_STATE,
  SL_SI91X_WLAN_NET_DOWN_STATE,
} sl_si91x_app_state_t;

//! WLAN application control block
typedef struct rsi_wlan_app_cb_s {
  volatile sl_si91x_app_state_t state;   //! WLAN application state
  uint32_t length;                       //! length of buffer to copy
  uint8_t buffer[SL_SI91X_APP_BUF_SIZE]; //! application buffer
  uint8_t buf_in_use;                    //! to check application buffer availability
  uint32_t event_map;                    //! application events bit map
} sl_si91x_app_cb_t;

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

#endif // APP_H
