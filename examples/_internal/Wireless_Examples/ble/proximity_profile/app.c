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
#include "ble_config.h"
#include "rsi_ble_apis.h"
#include "rsi_ble_common_config.h"
#include "rsi_bt_common_apis.h"

//! Common include file
#include "rsi_common_apis.h"
#include <string.h>
#include <stdio.h>

//! BLE attribute service types uuid values
#define RSI_BLE_CHAR_SERV_UUID   0x2803
#define RSI_BLE_CLIENT_CHAR_UUID 0x2902

//! BLE characteristic service uuid
#define RSI_BLE_IMMEDIATE_ALERT_SERVICE_UUID 0x1802
#define RSI_BLE_LINK_LOSS_SERVICE_UUID       0x1803
#define RSI_BLE_TX_POWER_SERVIEC_UUID        0x1804

#define RSI_BLE_ATT_ALERT_LEVEL_UUID 0x2A06
#define RSI_BLE_ATT_TX_POWER_UUID    0x2A07

//! local device name
#define RSI_BLE_APP_PROXIMITY_REPORTER (void *)"BLE_PROXIMITY"

//! attribute properties
#define RSI_BLE_ATT_PROPERTY_READ      0x02
#define RSI_BLE_ATT_WRITE_WITHOUT_RESP 0x04
#define RSI_BLE_ATT_PROPERTY_WRITE     0x08
#define RSI_BLE_ATT_PROPERTY_NOTIFY    0x10

//! application event list
#define RSI_BLE_CONN_EVENT            0x01
#define RSI_BLE_DISCONN_EVENT         0x02
#define RSI_BLE_LINK_LOSS_WRITE_EVENT 0x03
#define RSI_BLE_IMME_ALT_WRITE_EVENT  0x04

//TX power limits
#define TX_MIN_VALUE 0x5
#define TX_MAX_VALUE 0x12

//alert types
#define NO_ALERT   0
#define MILD_ALERT 1
#define HIGH_ALERT 2

//! global parameters list
static volatile uint32_t ble_app_event_map;
static volatile uint32_t ble_app_event_mask;
static rsi_ble_event_conn_status_t conn_event_to_app;
static rsi_ble_event_disconnect_t disconn_event_to_app;
static rsi_ble_event_write_t linkloss_event;
static rsi_ble_event_write_t imm_alt_event;
static uint16_t rsi_ble_link_loss_hndl;
static uint16_t rsi_ble_imme_alt_hndl;
static uint16_t rsi_ble_tx_power_hndl;
static uint8_t remote_dev_addr[18] = { 0 };

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
 * @fn         rsi_ble_add_char_serv_att
 * @brief      this function is used to add characteristic service attribute..
 * @param[in]  serv_handler, service handler.
 * @param[in]  handle, characteristic service attribute handle.
 * @param[in]  val_prop, characteristic value property.
 * @param[in]  att_val_handle, characteristic value handle
 * @param[in]  att_val_uuid, characteristic value uuid
 * @return     none.
 * @section description
 * This function is used at application to add characteristic attribute
 */
static void rsi_ble_add_char_serv_att(void *serv_handler,
                                      uint16_t handle,
                                      uint8_t val_prop,
                                      uint16_t att_val_handle,
                                      uuid_t att_val_uuid)
{
  rsi_ble_req_add_att_t new_att = { 0 };

  //! preparing the attribute service structure
  new_att.serv_handler       = serv_handler;
  new_att.handle             = handle;
  new_att.att_uuid.size      = 2;
  new_att.att_uuid.val.val16 = RSI_BLE_CHAR_SERV_UUID;
  new_att.property           = RSI_BLE_ATT_PROPERTY_READ;

  //! preparing the characteristic attribute value
  new_att.data_len = 6;
  new_att.data[0]  = val_prop;
  rsi_uint16_to_2bytes(&new_att.data[2], att_val_handle);
  rsi_uint16_to_2bytes(&new_att.data[4], att_val_uuid.val.val16);

  //! Add attribute to the service
  rsi_ble_add_attribute(&new_att);

  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_add_char_val_att
 * @brief      this function is used to add characteristic value attribute.
 * @param[in]  serv_handler, new service handler.
 * @param[in]  handle, characteristic value attribute handle.
 * @param[in]  att_type_uuid, attribute uuid value.
 * @param[in]  val_prop, characteristic value property.
 * @param[in]  data, characteristic value data pointer.
 * @param[in]  data_len, characteristic value length.
 * @return     none.
 * @section description
 * This function is used at application to create new service.
 */
static void rsi_ble_add_char_val_att(void *serv_handler,
                                     uint16_t handle,
                                     uuid_t att_type_uuid,
                                     uint8_t val_prop,
                                     uint8_t *data,
                                     uint8_t data_len)
{
  rsi_ble_req_add_att_t new_att = { 0 };

  //! preparing the attributes
  new_att.serv_handler = serv_handler;
  new_att.handle       = handle;
  memcpy((void *)&new_att.att_uuid, (void *)&att_type_uuid, sizeof(uuid_t));
  new_att.property = val_prop;

  //! preparing the attribute value
  new_att.data_len = RSI_MIN(sizeof(new_att.data), data_len);
  memcpy(new_att.data, data, new_att.data_len);

  //! add attribute to the service
  rsi_ble_add_attribute(&new_att);

  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_add_proximity_serv
 * @brief      this function is used to add new service i.e.., proximity service.
 * @param[in]  none.
 * @return     int32_t
 *             0  =  success
 *             !0 = failure
 * @section description
 * This function is used at application to create new service.
 */
static uint32_t rsi_ble_add_proximity_serv(void)
{
  uuid_t new_uuid                       = { 0 };
  rsi_ble_resp_add_serv_t new_serv_resp = { 0 };
  uint8_t maxvalue                      = TX_MAX_VALUE;
  uint8_t level                         = 0;

  //! adding new service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_LINK_LOSS_SERVICE_UUID;
  rsi_ble_add_service(new_uuid, &new_serv_resp);

  //! adding characteristic service attribute to the service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_ATT_ALERT_LEVEL_UUID;
  rsi_ble_add_char_serv_att(new_serv_resp.serv_handler,
                            new_serv_resp.start_handle + 1,
                            RSI_BLE_ATT_PROPERTY_READ | RSI_BLE_ATT_PROPERTY_WRITE,
                            new_serv_resp.start_handle + 2,
                            new_uuid);

  //! adding characteristic value attribute to the service
  rsi_ble_link_loss_hndl = new_serv_resp.start_handle + 2;
  new_uuid.size          = 2;
  new_uuid.val.val16     = RSI_BLE_ATT_ALERT_LEVEL_UUID;
  rsi_ble_add_char_val_att(new_serv_resp.serv_handler,
                           new_serv_resp.start_handle + 2,
                           new_uuid,
                           RSI_BLE_ATT_PROPERTY_READ | RSI_BLE_ATT_PROPERTY_WRITE,
                           &level,
                           sizeof(level));

  //! adding new service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_IMMEDIATE_ALERT_SERVICE_UUID;
  rsi_ble_add_service(new_uuid, &new_serv_resp);

  //! adding characteristic service attribute to the service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_ATT_ALERT_LEVEL_UUID;
  rsi_ble_add_char_serv_att(new_serv_resp.serv_handler,
                            new_serv_resp.start_handle + 3,
                            RSI_BLE_ATT_WRITE_WITHOUT_RESP,
                            new_serv_resp.start_handle + 4,
                            new_uuid);

  //! adding characteristic value attribute to the service
  rsi_ble_imme_alt_hndl = new_serv_resp.start_handle + 4;
  new_uuid.size         = 2;
  new_uuid.val.val16    = RSI_BLE_ATT_ALERT_LEVEL_UUID;
  rsi_ble_add_char_val_att(new_serv_resp.serv_handler,
                           new_serv_resp.start_handle + 4,
                           new_uuid,
                           RSI_BLE_ATT_WRITE_WITHOUT_RESP,
                           &level,
                           sizeof(level));

  //! adding new service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_TX_POWER_SERVIEC_UUID;
  rsi_ble_add_service(new_uuid, &new_serv_resp);
  //! adding characteristic service attribute to the service
  new_uuid.size      = 2;
  new_uuid.val.val16 = RSI_BLE_ATT_TX_POWER_UUID;
  rsi_ble_add_char_serv_att(new_serv_resp.serv_handler,
                            new_serv_resp.start_handle + 5,
                            RSI_BLE_ATT_PROPERTY_READ,
                            new_serv_resp.start_handle + 6,
                            new_uuid);

  //! adding characteristic value attribute to the service
  rsi_ble_tx_power_hndl = new_serv_resp.start_handle + 6;
  new_uuid.size         = 2;
  new_uuid.val.val16    = RSI_BLE_ATT_TX_POWER_UUID;
  rsi_ble_add_char_val_att(new_serv_resp.serv_handler,
                           new_serv_resp.start_handle + 6,
                           new_uuid,
                           RSI_BLE_ATT_PROPERTY_READ,
                           &maxvalue,
                           sizeof(maxvalue));
  return 0;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_init_events
 * @brief      initializes the event parameter.
 * @param[in]  none.
 * @return     none.
 * @section description
 * This function is used during BLE initialization.
 */
static void rsi_ble_app_init_events()
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
 * @brief      clears the specific event.
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
static int32_t rsi_ble_app_get_event(void)
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
 * @brief      its invoked when write/notify/indication events are received.
 * @param[in]  event_id, it indicates write/notification event id.
 * @param[in]  rsi_ble_write, write event parameters.
 * @return     none.
 * @section description
 * This callback function is invoked when write/notify/indication events are received
 */
static void rsi_ble_on_gatt_write_event(uint16_t event_id, rsi_ble_event_write_t *rsi_ble_write)
{
  UNUSED_PARAMETER(event_id); //This statement is added only to resolve compilation warning, value is unchanged

  if (rsi_ble_link_loss_hndl == *((uint16_t *)rsi_ble_write->handle)) {
    memcpy(&linkloss_event, rsi_ble_write, sizeof(rsi_ble_event_write_t));
    rsi_ble_app_set_event(RSI_BLE_LINK_LOSS_WRITE_EVENT);
  } else if (rsi_ble_imme_alt_hndl == *((uint16_t *)rsi_ble_write->handle)) {
    memcpy(&imm_alt_event, rsi_ble_write, sizeof(rsi_ble_event_write_t));
    rsi_ble_app_set_event(RSI_BLE_IMME_ALT_WRITE_EVENT);
  }
}

/*==============================================*/
/**
 * @fn         rsi_ble_proximity_gatt_server
 * @brief      this is the application of proximity profile application.
 * @param[in]  event_id, it indicates write/notification event id.
 * @param[in]  rsi_ble_write, write event parameters.
 * @return     none.
 * @section description
 * This function is used to test the simple chat application.
 */
void rsi_ble_proximity_gatt_server(void)
{
  int32_t status = 0;
  uint8_t ix     = 0;
  int32_t event_id;
  uint8_t adv[31]                                            = { 2, 1, 6 };
  static uint8_t rsi_app_resp_get_dev_addr[RSI_DEV_ADDR_LEN] = { 0 };
  uint8_t local_dev_addr[18]                                 = { 0 };
  sl_wifi_version_string_t version                           = { 0 };

  //! WC initialization
  status = sl_wifi_init(&config, default_wifi_event_handler);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\nWi-Fi Initialization Failed, Error Code : 0x%lX\r\n", status);
    return;
  } else {
    LOG_PRINT("\r\nWi-Fi Initialization Success\n\n");
  }

  //! Firmware version Prints
  status = sl_wifi_get_firmware_version(&version);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("Firmware version Failed, Error Code : 0x%lX\r\n", status);
  } else {
    LOG_PRINT("firmware_version = %s\r\n", version.version);
  }

  //! adding  BLE Proximity service
  rsi_ble_add_proximity_serv();

  //! registering the GAP callback functions
  rsi_ble_gap_register_callbacks(NULL,
                                 rsi_ble_on_connect_event,
                                 rsi_ble_on_disconnect_event,
                                 NULL,
                                 NULL,
                                 NULL,
                                 rsi_ble_on_enhance_conn_status_event,
                                 NULL,
                                 NULL,
                                 NULL);

  //! registering the GATT callback functions
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
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL);

  //!  initializing the application events map
  rsi_ble_app_init_events();

  //! get the local device address(MAC address).
  status = rsi_bt_get_local_device_address(rsi_app_resp_get_dev_addr);
  if (status != RSI_SUCCESS) {
    return;
  }

  rsi_6byte_dev_address_to_ascii(local_dev_addr, rsi_app_resp_get_dev_addr);
  LOG_PRINT("Local device addr: %s \n", local_dev_addr);

  //! Set local name
  rsi_bt_set_local_name(RSI_BLE_APP_PROXIMITY_REPORTER);

  //! prepare advertise data //local/device name
  adv[3] = strlen(RSI_BLE_APP_PROXIMITY_REPORTER) + 1;
  adv[4] = 9;
  strcpy((char *)&adv[5], RSI_BLE_APP_PROXIMITY_REPORTER);

  //! set advertise data
  rsi_ble_set_advertise_data(adv, strlen(RSI_BLE_APP_PROXIMITY_REPORTER) + 5);

  //! set device in advertising mode.
  status = rsi_ble_start_advertising();
  if (status != RSI_SUCCESS) {
    return;
  }
  LOG_PRINT("Advertising started, local name : %s\r\n", (char *)RSI_BLE_APP_PROXIMITY_REPORTER);

  //! waiting for events from controller.
  while (1) {
    //! Application main loop

    //! checking for events list
    event_id = rsi_ble_app_get_event();
    if (event_id == -1) {
      continue;
    }
    switch (event_id) {
      case RSI_BLE_CONN_EVENT: {
        //! event invokes when connection was completed
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_CONN_EVENT);
        rsi_6byte_dev_address_to_ascii(remote_dev_addr, conn_event_to_app.dev_addr);
        LOG_PRINT("\r\n Module connected to address : %s \r\n", remote_dev_addr);
      } break;
      case RSI_BLE_DISCONN_EVENT: {
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_DISCONN_EVENT);
        LOG_PRINT("\r\nModule got Disconnected\r\n");

        //! set device in advertising mode.
adv:
        status = rsi_ble_start_advertising();
        if (status != RSI_SUCCESS) {
          goto adv;
        }
        LOG_PRINT("Advertising  started \r\n");
      } break;
      case RSI_BLE_LINK_LOSS_WRITE_EVENT: {
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_LINK_LOSS_WRITE_EVENT);

        LOG_PRINT("\r\nHandle: 0x%x, length: %d, data: ", *((uint16_t *)linkloss_event.handle), linkloss_event.length);
        for (ix = 0; ix < linkloss_event.length; ix++) {
          LOG_PRINT("%x, ", linkloss_event.att_value[ix]);
        }
        LOG_PRINT("\r\n");
      } break;
      case RSI_BLE_IMME_ALT_WRITE_EVENT: {
        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_IMME_ALT_WRITE_EVENT);

        LOG_PRINT("\r\nHandle: 0x%x, length: %d, data: ", *((uint16_t *)imm_alt_event.handle), imm_alt_event.length);
        for (ix = 0; ix < imm_alt_event.length; ix++) {
          LOG_PRINT("%x, ", imm_alt_event.att_value[ix]);
        }
        LOG_PRINT("\r\n");
      } break;
      default: {
      }
    }
  }
}

void app_init(void)
{
  osThreadNew((osThreadFunc_t)rsi_ble_proximity_gatt_server, NULL, &thread_attributes);
}
