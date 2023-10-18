/*******************************************************************************
* @file  app.c
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
/**
 * @file    app.c
 * @version 0.1
 *
 *  @brief : This file contains example application for WLAN BLE coex power save.
 *
 *  @section Description  This file contains example application for WLAN BLE coex power save. 
 */

/**
 * Include files
 **/
//! SL Wi-Fi SDK includes
#include "sl_board_configuration.h"
#include "sl_wifi.h"
#include "sl_wifi_callback_framework.h"
#include "cmsis_os2.h"

// BLE Specific inclusions
#include "ble_config.h"
#include <rsi_ble_apis.h>
#include "rsi_ble_common_config.h"
#include <rsi_common_apis.h>
#ifdef RSI_M4_INTERFACE
#include "sl_si91x_m4_ps.h"
#endif
#include "wifi_app.h"

static const sl_wifi_device_configuration_t config = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = NULL,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .region_code = US,
  .boot_config = { .oper_mode              = SL_SI91X_CLIENT_MODE,
                   .coex_mode              = SL_SI91X_WLAN_BLE_MODE,
                   .feature_bit_map        = (SL_SI91X_FEAT_WPS_DISABLE | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
                                       | SL_SI91X_FEAT_DEV_TO_HOST_ULP_GPIO_1),
                   .tcp_ip_feature_bit_map = (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID
                                              | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT | SL_SI91X_TCP_IP_FEAT_SSL),
                   .custom_feature_bit_map = (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID),
                   .ext_custom_feature_bit_map =
                     (SL_SI91X_EXT_FEAT_LOW_POWER_MODE | SL_SI91X_EXT_FEAT_XTAL_CLK
#ifdef CHIP_917
                      | RAM_LEVEL_NWP_ADV_MCU_BASIC | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#else //defaults
#ifdef RSI_M4_INTERFACE
                      | SL_SI91X_EXT_FEAT_256K_MODE
#else
                      | SL_SI91X_EXT_FEAT_384K_MODE
#endif
#endif
                      | SL_SI91X_EXT_FEAT_BT_CUSTOM_FEAT_ENABLE // Enable BT feature
#if (defined A2DP_POWER_SAVE_ENABLE)
                      | SL_SI91X_EXT_FEAT_XTAL_CLK
#endif
                      ),
                   .ext_tcp_ip_feature_bit_map =
                     (SL_SI91X_CONFIG_FEAT_EXTENTION_VALID | SL_SI91X_EXT_TCP_IP_TOTAL_SELECTS(10)),
                   .bt_feature_bit_map = (SL_SI91X_BT_RF_TYPE | SL_SI91X_ENABLE_BLE_PROTOCOL
#if (RSI_BT_GATT_ON_CLASSIC)
                                          | SL_SI91X_BT_ATT_OVER_CLASSIC_ACL /* to support att over classic acl link */
#endif
                                          ),
                   /*Enable BLE custom feature bitmap*/
                   .ble_feature_bit_map =
                     (SL_SI91X_BLE_MAX_NBR_PERIPHERALS(RSI_BLE_MAX_NBR_PERIPHERALS)
                      | SL_SI91X_BLE_MAX_NBR_CENTRALS(RSI_BLE_MAX_NBR_CENTRALS)
                      | SL_SI91X_BLE_MAX_NBR_ATT_SERV(RSI_BLE_MAX_NBR_ATT_SERV)
                      | SL_SI91X_BLE_MAX_NBR_ATT_REC(RSI_BLE_MAX_NBR_ATT_REC)
                      | SL_SI91X_FEAT_BLE_CUSTOM_FEAT_EXTENTION_VALID | SL_SI91X_BLE_PWR_INX(RSI_BLE_PWR_INX)
                      | SL_SI91X_BLE_PWR_SAVE_OPTIONS(RSI_BLE_PWR_SAVE_OPTIONS)
                      | SL_SI91X_916_BLE_COMPATIBLE_FEAT_ENABLE
#if RSI_BLE_GATT_ASYNC_ENABLE
                      | SL_SI91X_BLE_GATT_ASYNC_ENABLE
#endif
                      ),
                   .ble_ext_feature_bit_map =
                     (SL_SI91X_BLE_NUM_CONN_EVENTS(RSI_BLE_NUM_CONN_EVENTS)
                      | SL_SI91X_BLE_NUM_REC_BYTES(RSI_BLE_NUM_REC_BYTES)
#if RSI_BLE_INDICATE_CONFIRMATION_FROM_HOST
                      | SL_SI91X_BLE_INDICATE_CONFIRMATION_FROM_HOST //indication response from app
#endif
#if RSI_BLE_MTU_EXCHANGE_FROM_HOST
                      | SL_SI91X_BLE_MTU_EXCHANGE_FROM_HOST //MTU Exchange request initiation from app
#endif
#if RSI_BLE_SET_SCAN_RESP_DATA_FROM_HOST
                      | (SL_SI91X_BLE_SET_SCAN_RESP_DATA_FROM_HOST) //Set SCAN Resp Data from app
#endif
#if RSI_BLE_DISABLE_CODED_PHY_FROM_HOST
                      | (SL_SI91X_BLE_DISABLE_CODED_PHY_FROM_HOST) //Disable Coded PHY from app
#endif
#if BLE_SIMPLE_GATT
                      | SL_SI91X_BLE_GATT_INIT
#endif
                      ),
                   .config_feature_bit_map = (SL_SI91X_FEAT_SLEEP_GPIO_SEL_BITMAP) }
};

const osThreadAttr_t thread_attributes = {
  .name       = "application_thread",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 3072,
  .priority   = 0,
  .tz_module  = 0,
  .reserved   = 0,
};

uint8_t volatile ble_connection_done = 0, wlan_connection_done = 0;
int32_t no_ble_events = 0;
extern wifi_app_cb_t wifi_app_cb;
//! Function prototypes
extern void rsi_wlan_app_task(void);
extern void rsi_ble_app_init(void);
extern void rsi_ble_app_task(void);
sl_status_t wifi_app_event_handler(sl_wifi_event_t event, sl_wifi_buffer_t *buffer);
extern int32_t rsi_ble_app_get_event(void);

void rsi_wlan_ble_app(void *argument)
{
  UNUSED_PARAMETER(argument);
  int32_t status                   = SL_STATUS_OK;
  sl_wifi_version_string_t version = { 0 };

  //! Wi-Fi initialization
  status = sl_wifi_init(&config, default_wifi_event_handler);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\nWi-Fi Initialization Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  printf("\r\n Wi-Fi initialization is successful\n");

  //! Firmware version Prints
  status = sl_wifi_get_firmware_version(&version);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\nFirmware version Failed, Error Code : 0x%lX\r\n", status);
  } else {
    LOG_PRINT("\r\nfirmware_version = %s\r\n", version.version);
  }

  //! BLE initialization
  rsi_ble_app_init();
#ifdef RSI_M4_INTERFACE
#if ALARM_TIMER_BASED_WAKEUP
  initialize_m4_alarm();
#endif
#endif

  while (1) {
    //! WLAN application tasks
    rsi_wlan_app_task();

    //! BLE application tasks
    rsi_ble_app_task();

#ifdef RSI_M4_INTERFACE
#if ENABLE_POWER_SAVE
    if ((wlan_connection_done == 1) && (ble_connection_done == 1)) {
      no_ble_events = rsi_ble_app_get_event();
      if (!(wifi_app_cb.event_map & RSI_SEND_EVENT) && (no_ble_events == -1)) {
        if ((!(P2P_STATUS_REG & TA_wakeup_M4))) {
          P2P_STATUS_REG &= ~M4_wakeup_TA;
          LOG_PRINT("M4 in Sleep\r\n");
          sl_si91x_m4_sleep_wakeup();
          LOG_PRINT("M4 wake up\r\n");
#if (ALARM_TIMER_BASED_WAKEUP || BUTTON_BASED_WAKEUP)
          wifi_ble_send_data();
#endif
        }
      }
    }
#endif
#endif
  }

  return;
}

void app_init(void)
{
  osThreadNew((osThreadFunc_t)rsi_wlan_ble_app, NULL, &thread_attributes);
  return;
}
