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
 * Include files
 * */
//! SL Wi-Fi SDK includes
#include "sl_board_configuration.h"
#include "sl_constants.h"
#include "sl_wifi.h"
#include "sl_wifi_callback_framework.h"
#include "cmsis_os2.h"

//! BLE include file to refer BLE APIs
#include "rsi_ble_apis.h"
#include "ble_config.h"
#include "rsi_ble_common_config.h"
#include "rsi_bt_common_apis.h"
#include "rsi_bt_common.h"
#include "rsi_ble.h"

//! Common include file
#include "rsi_common_apis.h"
#include <stdio.h>
#include <string.h>

//! local device name
#define RSI_BLE_APP_GATT_TEST (void *)"BLE_GATT_TEST"

//! Service ID to query
#define SERVICE_UUID 0x1234

//! application events list
#define RSI_BLE_ADV_REPORT_EVENT        0x01
#define RSI_BLE_CONN_EVENT              0x02
#define RSI_BLE_DISCONN_EVENT           0x03
#define RSI_BLE_GATT_WRITE_EVENT        0x04
#define RSI_BLE_GATT_PROFILES           0x05
#define RSI_BLE_GATT_PROFILE            0x06
#define RSI_BLE_GATT_CHAR_SERVICES      0x07
#define RSI_BLE_GATT_INC_SERVICES       0x08
#define RSI_BLE_GATT_DESC_SERVICES      0x09
#define RSI_BLE_GATT_READ               0x0A
#define RSI_BLE_GATT_WRITE              0x0B
#define RSI_BLE_GATT_ERROR              0x0C
#define RSI_BLE_GATT_DESC_VAL           0x0D
#define RSI_BLE_PREPARE_WRITE_RSP_EVENT 0x0E

//! Address type of the device to connect
#define RSI_BLE_DEV_ADDR_TYPE LE_PUBLIC_ADDRESS

//! Address of the device to connect
#define RSI_BLE_DEV_ADDR "00:23:A7:80:70:B9"

//! Remote Device Name to connect
#define RSI_REMOTE_DEVICE_NAME "SILABS_DEV"

//! application global variables list
static volatile uint32_t ble_app_event_map;
static volatile uint32_t ble_app_event_mask;
static uint8_t remote_addr_type = 0;
static uint8_t remote_name[31];
static uint8_t remote_dev_addr[18]   = { 0 };
static uint8_t remote_dev_bd_addr[6] = { 0 };
static uint8_t device_found          = 0;
static rsi_ble_event_conn_status_t conn_event_to_app;
static rsi_ble_event_disconnect_t disconn_event_to_app;
static rsi_ble_event_write_t app_ble_write_event;
static rsi_ble_prepare_write_resp_t app_ble_write_rsp_event;
rsi_ble_event_profile_by_uuid_t p_profile;
rsi_ble_event_read_by_type1_t char_serv;
rsi_ble_event_read_by_type3_t p_att_desc;
uint8_t remote_dev_addr_conn[18]                   = { 0 };
uint16_t offset                                    = 0;
uint8_t prepare_write_cnt                          = 0;
static const sl_wifi_device_configuration_t config = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = NULL,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .region_code = US,
  .boot_config = { .oper_mode       = SL_SI91X_CLIENT_MODE,
                   .coex_mode       = SL_SI91X_WLAN_BLE_MODE,
                   .feature_bit_map = (SL_SI91X_FEAT_WPS_DISABLE | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
                                       | SL_SI91X_FEAT_DEV_TO_HOST_ULP_GPIO_1),
                   .tcp_ip_feature_bit_map =
                     (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map = (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID),
                   .ext_custom_feature_bit_map =
                     (SL_SI91X_EXT_FEAT_LOW_POWER_MODE | SL_SI91X_EXT_FEAT_XTAL_CLK | MEMORY_CONFIG
#ifdef CHIP_917
                      | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#endif
                      | SL_SI91X_EXT_FEAT_BT_CUSTOM_FEAT_ENABLE),
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
  .stack_size = 3072,
  .priority   = osPriorityNormal,
  .tz_module  = 0,
  .reserved   = 0,
};

/*==============================================*/
/**
 * @fn         rsi_ble_app_init_events
 * @brief      initializes the event parameter.
 * @param[in]  none.
 * @return     none.
 * @section description
 * This function is used during BLE initialization.
 */
static void rsi_ble_app_init_events(void)
{
  ble_app_event_map  = 0;
  ble_app_event_mask = 0xFFFFFFFF;
  ble_app_event_mask = ble_app_event_mask; //To suppress warning while compiling
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_set_event
 * @brief      set the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to set/raise the specific event.
 */
static void rsi_ble_app_set_event(uint32_t event_num)
{
  ble_app_event_map |= BIT(event_num);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_clear_event
 * @brief      clear the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to clear the specific event.
 */
static void rsi_ble_app_clear_event(uint32_t event_num)
{
  ble_app_event_map &= ~BIT(event_num);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_get_event
 * @brief      returns the first set event based on priority
 * @param[in]  none.
 * @return     int32_t
 *             > 0  = event number
 *             -1   = not received any event
 * @section description
 * This function returns the highest priority event among all the set events
 */
static int32_t rsi_ble_app_get_event()
{
  uint32_t ix;

  for (ix = 0; ix < 32; ix++) {
    if (ble_app_event_map & (1 << ix)) {
      return ix;
    }
  }

  return (-1);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_adv_reports
 * @brief      invoked when advertise report event is received
 * @param[in]  adv_report, pointer to the received advertising report
 * @return     none.
 * @section description
 * This callback function updates the scanned remote devices list
 */
static void rsi_ble_on_adv_reports(rsi_ble_event_adv_report_t *adv_report)
{
  if (device_found == 1) {
    return;
  }

  memset(remote_name, 0, 31);

  BT_LE_ADPacketExtract(remote_name, adv_report->adv_data, adv_report->adv_data_len);

  remote_addr_type = adv_report->dev_addr_type;
  rsi_6byte_dev_address_to_ascii(remote_dev_addr, (uint8_t *)adv_report->dev_addr);
  memcpy(remote_dev_bd_addr, (uint8_t *)adv_report->dev_addr, 6);
  if (((device_found == 0) && ((strcmp((const char *)remote_name, (const char *)RSI_REMOTE_DEVICE_NAME)) == 0))
      || (((remote_addr_type == RSI_BLE_DEV_ADDR_TYPE)
           && ((strcmp((const char *)remote_dev_addr, (const char *)RSI_BLE_DEV_ADDR) == 0))))) {
    device_found = 1;
    rsi_ble_app_set_event(RSI_BLE_ADV_REPORT_EVENT);
  }
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_enhance_conn_status_event
 * @brief      invoked when enhanced connection complete event is received
 * @param[out] resp_conn, connected remote device information
 * @return     none.
 * @section description
 * This callback function indicates the status of the connection
 */
void rsi_ble_on_enhance_conn_status_event(rsi_ble_event_enhance_conn_status_t *resp_enh_conn)
{
  conn_event_to_app.dev_addr_type = resp_enh_conn->dev_addr_type;
  memcpy(conn_event_to_app.dev_addr, resp_enh_conn->dev_addr, RSI_DEV_ADDR_LEN);
  conn_event_to_app.status = resp_enh_conn->status;
  rsi_ble_app_set_event(RSI_BLE_CONN_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_connect_event
 * @brief      invoked when connection complete event is received
 * @param[out] resp_conn, connected remote device information
 * @return     none.
 * @section description
 * This callback function indicates the status of the connection
 */
static void rsi_ble_on_connect_event(rsi_ble_event_conn_status_t *resp_conn)
{
  memcpy(&conn_event_to_app, resp_conn, sizeof(rsi_ble_event_conn_status_t));
  rsi_ble_app_set_event(RSI_BLE_CONN_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_disconnect_event
 * @brief      invoked when disconnection event is received
 * @param[in]  resp_disconnect, disconnected remote device information
 * @param[in]  reason, reason for disconnection.
 * @return     none.
 * @section description
 * This callback function indicates disconnected device information and status
 */
static void rsi_ble_on_disconnect_event(rsi_ble_event_disconnect_t *resp_disconnect, uint16_t reason)
{
  UNUSED_PARAMETER(reason); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(&disconn_event_to_app, resp_disconnect, sizeof(rsi_ble_event_disconnect_t));
  rsi_ble_app_set_event(RSI_BLE_DISCONN_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_gatt_write_event
 * @brief      this is call back function, it invokes when write/notify events received.
 * @param[in]  event_id, it indicates write/notification event id.
 * @param[in]  rsi_ble_write, write event parameters.
 * @return     none.
 * @section description
 * This is a callback function
 */
static void rsi_ble_on_gatt_write_event(uint16_t event_id, rsi_ble_event_write_t *rsi_ble_write)
{
  UNUSED_PARAMETER(event_id); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(&app_ble_write_event, rsi_ble_write, sizeof(rsi_ble_event_write_t));
  rsi_ble_app_set_event(RSI_BLE_GATT_WRITE_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_gatt_prepare_write_resp
 * @brief      this is call back function, it is invoked when prepare write response event is received.
 * @param[in]  event_status, it indicates the status of the event
 * @param[in]  rsi_ble_prepare_write_resp, prepare write response parameters.
 * @return     none.
 * @section description
 * This is a callback function
 */

static void rsi_ble_on_gatt_prepare_write_resp(uint16_t event_status,
                                               rsi_ble_prepare_write_resp_t *rsi_ble_prepare_write_resp)
{
  memcpy(&app_ble_write_rsp_event, rsi_ble_prepare_write_resp, sizeof(rsi_ble_prepare_write_resp_t));
  offset += rsi_ble_prepare_write_resp->length;
  prepare_write_cnt++;
  rsi_ble_app_set_event(RSI_BLE_PREPARE_WRITE_RSP_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_profiles_list_event
 * @brief      invoked when response is received for get list of services.
 * @param[out] p_ble_resp_profiles, profiles list details
 * @return     none
 * @section description
 */
static void rsi_ble_profiles_list_event(uint16_t resp_status, rsi_ble_event_profiles_list_t *rsi_ble_event_profiles)
{
  UNUSED_PARAMETER(
    rsi_ble_event_profiles);     //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  rsi_ble_app_set_event(RSI_BLE_GATT_PROFILES);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_profile_event
 * @brief      invoked when the specific service details are received for
 *             supported specific services.
 * @param[out] rsi_ble_event_profile, specific profile details
 * @return     none
 * @section description
 * This is a callback function
 */
static void rsi_ble_profile_event(uint16_t resp_status, rsi_ble_event_profile_by_uuid_t *rsi_ble_event_profile)
{
  UNUSED_PARAMETER(
    rsi_ble_event_profile);      //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  LOG_PRINT("\n in rsi_ble_profile_event\n");

  memcpy(&p_profile, rsi_ble_event_profile, sizeof(rsi_ble_event_profile_by_uuid_t));

  rsi_ble_app_set_event(RSI_BLE_GATT_PROFILE);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_char_services_event
 * @brief      invoked when response is received for characteristic services details
 * @param[out] rsi_ble_event_char_services, list of characteristic services.
 * @return     none
 * @section description
 */
static void rsi_ble_char_services_event(uint16_t resp_status,
                                        rsi_ble_event_read_by_type1_t *rsi_ble_event_char_services)
{
  UNUSED_PARAMETER(
    rsi_ble_event_char_services); //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status);  //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(&char_serv, rsi_ble_event_char_services, sizeof(rsi_ble_event_read_by_type1_t));
  rsi_ble_app_set_event(RSI_BLE_GATT_CHAR_SERVICES);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_inc_services_event
 * @brief      invoked when response is received for the include services details
 * @param[out] rsi_ble_event_inc_services, list of include  services.
 * @return     none
 * @section description
 */
static void rsi_ble_inc_services_event(uint16_t resp_status, rsi_ble_event_read_by_type2_t *rsi_ble_event_inc_services)
{
  UNUSED_PARAMETER(
    rsi_ble_event_inc_services); //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  rsi_ble_app_set_event(RSI_BLE_GATT_INC_SERVICES);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_att_desc_event
 * @brief      invoked when response is received for the characteristic descriptors details
 * @param[out] rsi_ble_event_att_desc, list of descriptors.
 * @return     none
 * @section description
 */
static void rsi_ble_on_att_desc_event(uint16_t resp_status, rsi_ble_event_read_by_type3_t *rsi_ble_event_att_desc)
{
  UNUSED_PARAMETER(
    rsi_ble_event_att_desc);     //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(&p_att_desc, rsi_ble_event_att_desc, sizeof(rsi_ble_event_read_by_type3_t));
  rsi_ble_app_set_event(RSI_BLE_GATT_DESC_SERVICES);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_read_event
 * @brief      invoked when response is received for get attribute value
 * @param[out] resp_id, received response id.
 * @param[out] rsi_ble_event_att_val, attribute value details
 * @return     none
 * @section description
 */
static void rsi_ble_on_read_event(uint16_t resp_status,
                                  uint16_t resp_id,
                                  rsi_ble_event_att_value_t *rsi_ble_event_att_val)
{
  UNUSED_PARAMETER(
    rsi_ble_event_att_val);      //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_id);     //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  rsi_ble_app_set_event(RSI_BLE_GATT_READ);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_write_event
 * @brief      this function will invoke when set the attribute value complete
 * @param[out] resp_id, response id
 * @param[out] status, status of the response
 * @return     none
 * @section description
 */
static void rsi_ble_write_event(uint16_t resp_status, rsi_ble_set_att_resp_t *rsi_ble_event_set_att_rsp)
{
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(remote_dev_bd_addr, rsi_ble_event_set_att_rsp->dev_addr, 6);
  rsi_ble_app_set_event(RSI_BLE_GATT_WRITE);
}
/*==============================================*/
/**
 * @fn         rsi_ble_gatt_error_event
 * @brief      this function will invoke when set the attribute value complete
 * @param[out] rsi_ble_gatt_error, event structure
 * @param[out] status, status of the response
 * @return     none
 * @section description
 */
static void rsi_ble_gatt_error_event(uint16_t resp_status, rsi_ble_event_error_resp_t *rsi_ble_gatt_error)
{
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(remote_dev_bd_addr, rsi_ble_gatt_error->dev_addr, 6);
  rsi_ble_app_set_event(RSI_BLE_GATT_ERROR);
}
/*==============================================*/
/**
 * @fn         rsi_ble_gatt_error_event
 * @brief      this function will invoke when set the attribute value complete
 * @param[out] rsi_ble_gatt_desc_val, event structure
 * @param[out] status, status of the response
 * @return     none
 * @section description
 */
static void rsi_ble_gatt_desc_val_event(uint16_t resp_status, rsi_ble_event_gatt_desc_t *rsi_ble_gatt_desc_val)
{
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  memcpy(remote_dev_bd_addr, rsi_ble_gatt_desc_val->dev_addr, 6);
  rsi_ble_app_set_event(RSI_BLE_GATT_DESC_VAL);
}

/*==============================================*/
/**
 * @fn         rsi_ble_simple_gatt_test
 * @brief      this is the application of ble GATT client api's test cases.
 * @param[in]  none.
 * @return     none.
 * @section description
 * This function is used at application.
 */
void rsi_ble_simple_gatt_test(void)
{
  int32_t status = 0;
  int32_t event_id;
  uuid_t search_serv;
  uint8_t loop          = 0;
  uint8_t adv[31]       = { 2, 1, 6 };
  uint8_t i             = 0;
  uint16_t write_handle = 0;
  uint8_t inc_query;
  uint8_t data[DATA_LENGTH] = { 01, 02, 03, 04, 05, 06, 07, 10, 01, 02, 03, 04, 05, 06, 07 };

  sl_wifi_version_string_t fw_version = { 0 };

  //! Wi-Fi initialization
  status = sl_wifi_init(&config, default_wifi_event_handler);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\n Wi-Fi Initialization Failed, Error Code : 0x%lX\r\n", status);
  }
  printf("\r\n Wi-Fi initialization is successful\n");

  //! Firmware version Prints
  status = sl_wifi_get_firmware_version(&fw_version);
  if (status == SL_STATUS_OK) {
    LOG_PRINT("\r\nFirmware version response: %s\r\n", fw_version.version);
  } else {
    LOG_PRINT("\r\nFailed to get Firmware version \r\n");
  }
  //! registering the GAP call back functions
  rsi_ble_gap_register_callbacks(rsi_ble_on_adv_reports,
                                 rsi_ble_on_connect_event,
                                 rsi_ble_on_disconnect_event,
                                 NULL,
                                 NULL,
                                 NULL,
                                 rsi_ble_on_enhance_conn_status_event,
                                 NULL,
                                 NULL,
                                 NULL);

  //! registering the GATT call back functions
  rsi_ble_gatt_register_callbacks(NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  rsi_ble_on_gatt_write_event,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  rsi_ble_gatt_error_event,
                                  rsi_ble_gatt_desc_val_event,
                                  rsi_ble_profiles_list_event,
                                  rsi_ble_profile_event,
                                  rsi_ble_char_services_event,
                                  rsi_ble_inc_services_event,
                                  rsi_ble_on_att_desc_event,
                                  (rsi_ble_on_event_read_resp_t)rsi_ble_on_read_event,
                                  rsi_ble_write_event,
                                  NULL,
                                  rsi_ble_on_gatt_prepare_write_resp);

  //!  initializing the application events map
  rsi_ble_app_init_events();

  //! Set local name
  rsi_bt_set_local_name(RSI_BLE_APP_GATT_TEST);
  LOG_PRINT("\n Local name set to: %s\n", (char *)RSI_BLE_APP_GATT_TEST);

  //! prepare advertise data //local/device name
  adv[3] = strlen(RSI_BLE_APP_GATT_TEST) + 1;
  adv[4] = 9;
  strcpy((char *)&adv[5], RSI_BLE_APP_GATT_TEST);

  //! set advertise data
  rsi_ble_set_advertise_data(adv, strlen(RSI_BLE_APP_GATT_TEST) + 5);

  //! set device in advertising mode.
  status = rsi_ble_start_advertising();
  if (status != RSI_SUCCESS) {
    LOG_PRINT("\r\n Start advertising failed, Error Code : 0x%lx\r\n", status);
    //return;
  }
  LOG_PRINT("\r\n Advertising started \r\n ");

  //! waiting for events from controller.
  while (1) {
    //! checking for events list
    event_id = rsi_ble_app_get_event();

    if (event_id == -1) {
      continue;
    }

    switch (event_id) {
      case RSI_BLE_ADV_REPORT_EVENT: {
        //! advertise report event.
        //! clear the advertise report event.
        rsi_ble_app_clear_event(RSI_BLE_ADV_REPORT_EVENT);
        status = rsi_ble_connect(remote_addr_type, (int8_t *)remote_dev_bd_addr);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("connect status: 0x%lX\r\n", status);
        }

      } break;
      case RSI_BLE_CONN_EVENT: {
        //! event invokes when connection was completed

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_CONN_EVENT);
        rsi_6byte_dev_address_to_ascii(remote_dev_addr, (uint8_t *)conn_event_to_app.dev_addr);
        LOG_PRINT("\r\n Module connected to address : %s \r\n", remote_dev_addr);
        rsi_ble_app_set_event(RSI_BLE_GATT_PROFILES);

      } break;
      case RSI_BLE_DISCONN_EVENT: {
        //! event invokes when disconnection was completed

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_DISCONN_EVENT);
        LOG_PRINT("\r\nModule got Disconnected\r\n");

        //! set device in advertising mode.
adv:
        status = rsi_ble_start_advertising();
        if (status != RSI_SUCCESS) {
          goto adv;
        }
        LOG_PRINT("\r\n Advertising started \r\n ");
      } break;

      case RSI_BLE_GATT_WRITE_EVENT: {
        //! event invokes when write/notification events received

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_WRITE_EVENT);
#if 1
        status = rsi_ble_indicate_confirm(conn_event_to_app.dev_addr);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("\n indication confirm failed \t reason = %lx \n", status);
        }
#endif
      } break;

      case RSI_BLE_GATT_PROFILES: {
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_PROFILES);
        LOG_PRINT("\nin gatt test:rsi_ble_gatt_profiles\n");
        memset(&search_serv, 0, sizeof(search_serv));
        search_serv.size      = 0x02;
        search_serv.val.val32 = SERVICE_UUID;
        rsi_6byte_dev_address_to_ascii(remote_dev_addr_conn, conn_event_to_app.dev_addr);
        LOG_PRINT("\n triggering profile asyn for %s", remote_dev_addr_conn);
        status = rsi_ble_get_profile_async(conn_event_to_app.dev_addr, search_serv, NULL);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("\n rsi_ble_get_profile_async failed with %lx", status);
        } else {
          LOG_PRINT("\n rsi_ble_get_profile_async success \n");
        }
      } break;

      case RSI_BLE_GATT_PROFILE: {
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_PROFILE);
        LOG_PRINT("\n rsi_ble_get_profile_async success start handle = %x , end handle = %x",
                  *(uint16_t *)p_profile.start_handle,
                  *(uint16_t *)p_profile.end_handle);
        status = rsi_ble_get_char_services_async(conn_event_to_app.dev_addr,
                                                 *(uint16_t *)p_profile.start_handle,
                                                 *(uint16_t *)p_profile.end_handle,
                                                 NULL);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("\n rsi_ble_get_char_services_async failed with %lx", status);
        } else {
          LOG_PRINT("\n rsi_ble_get_char_services_async success \n");
        }
      } break;

      case RSI_BLE_GATT_CHAR_SERVICES: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_CHAR_SERVICES);
        inc_query = 1;
        status    = rsi_ble_get_inc_services_async(conn_event_to_app.dev_addr,
                                                *(uint16_t *)p_profile.start_handle,
                                                *(uint16_t *)p_profile.end_handle,
                                                NULL);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("\n rsi_ble_get_inc_services_async failed with %lx", status);
        }

      } break;

      case RSI_BLE_GATT_INC_SERVICES: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_INC_SERVICES);
        if (inc_query) {
          inc_query = 0;
          rsi_ble_app_set_event(RSI_BLE_GATT_DESC_VAL);
        }

      } break;

      case RSI_BLE_GATT_DESC_SERVICES: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_DESC_SERVICES);

        rsi_ble_get_att_value_async(conn_event_to_app.dev_addr, *(uint16_t *)p_att_desc.handle, NULL);
        loop = 0;
      } break;

      case RSI_BLE_GATT_READ: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_READ);
        if (loop == 0) {
          search_serv.size      = 2;
          search_serv.val.val16 = 0x2A00;
          rsi_ble_get_char_value_by_uuid_async(conn_event_to_app.dev_addr, 0x01, 0x05, search_serv, NULL);
        } else if (loop == 1) {
          uint16_t handles[2];

          handles[0] = 0x03;
          handles[1] = 0x05;
          rsi_ble_get_multiple_att_values_async(conn_event_to_app.dev_addr, 2, handles, NULL);
        } else if (loop == 2) {
          rsi_ble_get_long_att_value_async(conn_event_to_app.dev_addr, 3, 0, NULL);
        } else {
          rsi_ble_set_att_value_async(conn_event_to_app.dev_addr, 3, 12, (uint8_t *)"gatttestdata");
        }
        loop++;
      } break;

      case RSI_BLE_GATT_WRITE: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_WRITE);
        rsi_ble_set_att_cmd(remote_dev_bd_addr, 3, 12, (uint8_t *)"gatttestdata");
      } break;
      case RSI_BLE_GATT_ERROR: {
        rsi_ble_app_clear_event(RSI_BLE_GATT_ERROR);
        LOG_PRINT("get att descriptor value");
        if (inc_query) {
          inc_query = 0;
          rsi_ble_app_set_event(RSI_BLE_GATT_DESC_VAL);
        }
        break;

        case RSI_BLE_GATT_DESC_VAL: {
          for (i = 0; i < char_serv.num_of_services; i++) {
            if (char_serv.char_services[i].char_data.char_property & RSI_BLE_ATT_PROPERTY_WRITE) {
              write_handle = char_serv.char_services[i].char_data.char_handle;
              LOG_PRINT("\n write handle = %x", write_handle);
              break;
            }
          }
          rsi_ble_app_clear_event(RSI_BLE_GATT_DESC_VAL);
          LOG_PRINT("\n get att value \n");
          status = rsi_ble_prepare_write_async(conn_event_to_app.dev_addr, write_handle, 0, DATA_LENGTH, data);
          if (status != RSI_SUCCESS) {
            LOG_PRINT("\n rsi_ble_prepare_write_async failed with %lX ", status);
          } else {
            LOG_PRINT("\n rsi_ble_prepare_write_async success");
          }
          loop = 0;
        } break;
        case RSI_BLE_PREPARE_WRITE_RSP_EVENT: {
          rsi_ble_app_clear_event(RSI_BLE_PREPARE_WRITE_RSP_EVENT);
          if ((!memcmp(app_ble_write_rsp_event.att_value, data, app_ble_write_rsp_event.length))
              && (prepare_write_cnt < 3)) {
            status = rsi_ble_prepare_write_async(conn_event_to_app.dev_addr, write_handle, offset, DATA_LENGTH, data);
            if (status != RSI_SUCCESS) {
              LOG_PRINT("\n rsi_ble_prepare_write_async failed with %lX ", status);
            } else {
              LOG_PRINT("\n rsi_ble_prepare_write_async success");
            }
          } else {
            status = rsi_ble_execute_write_async(conn_event_to_app.dev_addr, EXECUTE_WRITE);
            if (status != RSI_SUCCESS) {
              LOG_PRINT("\n rsi_ble_execute_write_async failed with %lX ", status);
            }
          }
        } break;
        default: {
        }
      }
    }
  }
}
void app_init(void)
{
  osThreadNew((osThreadFunc_t)rsi_ble_simple_gatt_test, NULL, &thread_attributes);
}
