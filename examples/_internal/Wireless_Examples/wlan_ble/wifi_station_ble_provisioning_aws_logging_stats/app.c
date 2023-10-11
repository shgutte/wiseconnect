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
/*************************************************************************
 *
 */

/*================================================================================
 * @brief : This file contains example application for Wlan Station BLE
 * Provisioning
 * @section Description :
 * This application explains how to get the WLAN connection functionality using
 * BLE provisioning.
 * Silicon Labs Module starts advertising and with BLE Provisioning the Access Point
 * details are fetched.
 * Silicon Labs device is configured as a WiFi station and connects to an Access Point.
 =================================================================================*/

/**
 * Include files
 **/
//! SL Wi-Fi SDK includes
#include "sl_board_configuration.h"
#include "sl_wifi.h"
#include "sl_wifi_callback_framework.h"
#include "cmsis_os2.h"
#include "wifi_config.h"
//BLE Specific inclusions
#include "ble_config.h"
#include <rsi_ble_apis.h>
#include "rsi_ble_common_config.h"
#include <rsi_common_apis.h>

#define RSI_APPLICATION_TASK_PRIORITY   1
#define RSI_BLE_TASK_PRIORITY           2
#define RSI_APPLICATION_TASK_STACK_SIZE 3072
#define RSI_BLE_TASK_STACK_SIZE         1000

// APP version
#define APP_FW_VERSION "0.4"

// Function prototypes
extern void sl_wifi_app_task(void);
extern void rsi_ble_configurator_task(void *argument);
void rsi_ble_configurator_init(void);
extern int32_t rsi_wlan_mqtt_certs_init(void);
uint8_t magic_word;

osSemaphoreId_t wlan_thread_sem;
osSemaphoreId_t ble_thread_sem;
uint32_t wifi_connections, wifi_disconnections;

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
                   .custom_feature_bit_map =
                     (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID | SL_SI91X_CUSTOM_FEAT_ASYNC_CONNECTION_STATUS),
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
                      | (SL_SI91X_EXT_FEAT_BT_CUSTOM_FEAT_ENABLE)
#if (defined A2DP_POWER_SAVE_ENABLE)
                      | SL_SI91X_EXT_FEAT_XTAL_CLK
#endif
                      ),
                   .bt_feature_bit_map = (SL_SI91X_BT_RF_TYPE | SL_SI91X_ENABLE_BLE_PROTOCOL
#if (RSI_BT_GATT_ON_CLASSIC)
                                          | SL_SI91X_BT_ATT_OVER_CLASSIC_ACL /* to support att over classic acl link */
#endif
                                          ),
                   .ext_tcp_ip_feature_bit_map = (SL_SI91X_CONFIG_FEAT_EXTENTION_VALID),
                   //!ENABLE_BLE_PROTOCOL in bt_feature_bit_map
                   .ble_feature_bit_map =
                     ((SL_SI91X_BLE_MAX_NBR_PERIPHERALS(RSI_BLE_MAX_NBR_PERIPHERALS)
                       | SL_SI91X_BLE_MAX_NBR_CENTRALS(RSI_BLE_MAX_NBR_CENTRALS)
                       | SL_SI91X_BLE_MAX_NBR_ATT_SERV(RSI_BLE_MAX_NBR_ATT_SERV)
                       | SL_SI91X_BLE_MAX_NBR_ATT_REC(RSI_BLE_MAX_NBR_ATT_REC))
                      | SL_SI91X_FEAT_BLE_CUSTOM_FEAT_EXTENTION_VALID | SL_SI91X_BLE_PWR_INX(RSI_BLE_PWR_INX)
                      | SL_SI91X_BLE_PWR_SAVE_OPTIONS(RSI_BLE_PWR_SAVE_OPTIONS)
                      | SL_SI91X_916_BLE_COMPATIBLE_FEAT_ENABLE
#if RSI_BLE_GATT_ASYNC_ENABLE
                      | SL_SI91X_BLE_GATT_ASYNC_ENABLE
#endif
                      ),

                   .ble_ext_feature_bit_map =
                     ((SL_SI91X_BLE_NUM_CONN_EVENTS(RSI_BLE_NUM_CONN_EVENTS)
                       | SL_SI91X_BLE_NUM_REC_BYTES(RSI_BLE_NUM_REC_BYTES))
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
  .stack_size = RSI_APPLICATION_TASK_STACK_SIZE,
  .priority   = osPriorityNormal,
  .tz_module  = 0,
  .reserved   = 0,
};

const osThreadAttr_t ble_thread_attributes = {
  .name       = "ble_thread",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = RSI_BLE_TASK_STACK_SIZE,
  .priority   = osPriorityNormal,
  .tz_module  = 0,
  .reserved   = 0,
};

static sl_status_t sl_wifi_module_state_stats_callback(sl_wifi_event_t event,
                                                       void *data,
                                                       uint32_t data_length,
                                                       void *arg);

sl_status_t sl_wifi_module_state_stats_callback(sl_wifi_event_t event,
                                                void *payload,
                                                uint32_t payload_length,
                                                void *arg)
{
  UNUSED_PARAMETER(event);
  UNUSED_PARAMETER(arg);
  int i = 0, j = 0;
  char *unknown       = "unknown";
  char *higher_nibble = unknown;
  char *lower_nibble  = unknown;
  char *reason_code   = unknown;
  uint8_t bssid_string[18];

  if (payload_length != sizeof(rsi_state_notification_t))
    return SL_STATUS_FAIL;
  rsi_state_notification_t *state = (rsi_state_notification_t *)payload;
  for (i = 0; i < WLAN_MODULE_STATES; i++) {
    //higher nibble information
    if (STATE[i].bit == (state->StateCode & 0xF0)) {
      higher_nibble = STATE[i].string;
    }
    //lower nibble information
    if (STATE[i].bit == (state->StateCode & 0x0F)) {
      lower_nibble = STATE[i].string;
    }
  }
  for (j = 0; j < WLAN_REASON_CODES; j++) {
    //!reason code info
    if (REASONCODE[j].bit == (state->reason_code & 0xFF)) {
      reason_code = REASONCODE[j].string;
    }
  }
  if (higher_nibble == unknown && lower_nibble == unknown && reason_code == unknown)
    return SL_STATUS_INVALID_STATE;
  rsi_6byte_dev_address_to_ascii((uint8_t *)bssid_string, state->rsi_bssid);

  if (*higher_nibble == 'A') {
    wifi_connections++;
    printf("Wi-Fi connections %ld\n", wifi_connections);
  }
  if (*higher_nibble == 'U') {
    wifi_disconnections++;
    printf("Wi-Fi disconnections %ld\n", wifi_disconnections);
  }
  if (state->rsi_channel == 0 && state->rsi_rssi == 100) {

  } else if (state->rsi_channel == 0 && state->rsi_rssi != 100) {

  } else if (state->rsi_channel != 0 && state->rsi_rssi == 100) {

  } else {
  }
  return SL_STATUS_OK;
}

void rsi_wlan_ble_app_init(void *argument)
{
  UNUSED_PARAMETER(argument);
  int32_t status                   = RSI_SUCCESS;
  sl_wifi_version_string_t version = { 0 };

  //! Wi-Fi initialization
  status = sl_wifi_init(&config, default_wifi_event_handler);
  if (status != SL_STATUS_OK) {
    printf("\r\nWi-Fi Initialization Failed, Error Code : 0x%lX\r\n", status);
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

  sl_wifi_set_stats_callback(sl_wifi_module_state_stats_callback, NULL);
  printf("\r\n Registered Wi-Fi module state stats callback\n");
  osThreadNew((osThreadFunc_t)rsi_ble_configurator_task, NULL, &ble_thread_attributes);

  status = rsi_wlan_mqtt_certs_init();
  if (status != RSI_SUCCESS) {
    printf("\r\nset certificate issue, Error Code : 0x%lX\r\n", status);
    return;
  } else {
    printf("\r\nset certificate Success\r\n");
  }

  // BLE initialization
  rsi_ble_configurator_init();

  sl_wifi_app_task();

  return;
}

void app_init(void)
{
  wlan_thread_sem = osSemaphoreNew(1, 0, NULL);
  ble_thread_sem  = osSemaphoreNew(1, 0, NULL);

  osThreadNew((osThreadFunc_t)rsi_wlan_ble_app_init, NULL, &thread_attributes);
}
