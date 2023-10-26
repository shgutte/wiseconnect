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
#include "rsi_bt_common_apis.h"

//! Common include file
#include <rsi_common_apis.h>
#include <string.h>

//! BLE attribute service types uuid values
#define RSI_BLE_CHAR_SERV_UUID   0x2803
#define RSI_BLE_CLIENT_CHAR_UUID 0x2902

//! immediate alert service uuid
#define RSI_BLE_NEW_SERVICE_UUID 0x1802
//! Alert level characteristic
#define RSI_BLE_ATTRIBUTE_1_UUID 0x2A06

#include "rsi_ble_common_config.h"

//! rssi threshold value
#define RSI_BLE_RSSI_THRESHOLD_VALUE 40

//! max data length
#define RSI_BLE_MAX_DATA_LEN 20

//! max number of scan list
#define MAX_NUMBER_OF_SCAN_LIST 5

//! local device name
#define RSI_BLE_APP_NAME "Immediate_Alert"

//! attribute properties
#define RSI_BLE_ATT_PROPERTY_READ   0x02
#define RSI_BLE_ATT_PROPERTY_WRITE  0x08
#define RSI_BLE_ATT_PROPERTY_NOTIFY 0x10

//! application event list
#define RSI_APP_EVENT_ADV_REPORT   0x00
#define RSI_BLE_CONN_EVENT         0x02
#define RSI_BLE_DISCONN_EVENT      0x03
#define RSI_BLE_GATT_WRITE_EVENT   0x04
#define RSI_BLE_GATT_PROFILE       0x05
#define RSI_BLE_GATT_CHAR_SERVICES 0x06
#define RSI_BLE_GET_RSSI           0x07

//! Address type of the device to connect
#define RSI_BLE_DEV_ADDR_TYPE LE_RANDOM_ADDRESS

//! Address of the device to connect
#define RSI_BLE_DEV_ADDR "B8:8F:27:74:F8:F0"

//! Remote Device Name to connect
#define RSI_REMOTE_DEVICE_NAME "realme 10 Pro+ 5G"

//! global parameters list
static volatile uint32_t ble_app_event_map;
static volatile uint32_t ble_app_event_mask;
static uint8_t remote_addr_type = 0;
static uint8_t remote_name[31];
static uint8_t remote_dev_addr[18]   = { 0 };
static uint8_t remote_dev_bd_addr[6] = { 0 };
static uint8_t device_found          = 0;
static rsi_ble_event_conn_status_t conn_event_to_app;
static rsi_ble_event_disconnect_t disconn_event_to_app;
static profile_descriptors_t rsi_ble_service;
static rsi_ble_resp_char_services_t char_servs;
static uint16_t rsi_ble_att1_val_hndl;

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
 * @fn         rsi_ble_simple_central_on_adv_report_event
 * @brief      invoked when advertise report event is received
 * @param[in]  adv_report, pointer to the received advertising report
 * @return     none.
 * @section description
 * This callback function updates the scanned remote devices list
 */
void rsi_ble_simple_central_on_adv_report_event(rsi_ble_event_adv_report_t *adv_report)
{

  if (device_found == 1) {
    return;
  }

  memset(remote_name, 0, 31);
  BT_LE_ADPacketExtract(remote_name, adv_report->adv_data, adv_report->adv_data_len);

  remote_addr_type = adv_report->dev_addr_type;
  rsi_6byte_dev_address_to_ascii(remote_dev_addr, (uint8_t *)adv_report->dev_addr);
  memcpy(remote_dev_bd_addr, (uint8_t *)adv_report->dev_addr, 6);
  if (((device_found == 0) && ((strcmp((const char *)remote_name, RSI_REMOTE_DEVICE_NAME)) == 0))
      || ((remote_addr_type == RSI_BLE_DEV_ADDR_TYPE)
          && ((strcmp((const char *)remote_dev_addr, RSI_BLE_DEV_ADDR) == 0)))) {
    device_found = 1;
    rsi_ble_app_set_event(RSI_APP_EVENT_ADV_REPORT);
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
  memcpy((void *)&disconn_event_to_app, (const void *)resp_disconnect, sizeof(rsi_ble_event_disconnect_t));
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
  UNUSED_PARAMETER(event_id);      //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(rsi_ble_write); //This statement is added only to resolve compilation warning, value is unchanged
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_profile
 * @brief      invoked when the specific service details are received for
 *             supported specific services.
 * @param[out] p_ble_resp_profile, specific profile details
 * @return     none
 * @section description
 * This is a callback function
 */
static void rsi_ble_profile(uint16_t resp_status, profile_descriptors_t *rsi_ble_resp_profile)
{
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(
    rsi_ble_resp_profile); //This statement is added only to resolve compilation warning, value is unchanged
  rsi_ble_app_set_event(RSI_BLE_GATT_PROFILE);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_char_services
 * @brief      invoked when response is received for characteristic services details
 * @param[out] p_ble_resp_char_services, list of characteristic services.
 * @return     none
 * @section description
 */
static void rsi_ble_char_services(uint16_t resp_status, rsi_ble_resp_char_services_t *rsi_ble_resp_char_services)
{
  UNUSED_PARAMETER(resp_status); //This statement is added only to resolve compilation warning, value is unchanged
  UNUSED_PARAMETER(
    rsi_ble_resp_char_services); //This statement is added only to resolve compilation warning, value is unchanged
  rsi_ble_app_set_event(RSI_BLE_GATT_CHAR_SERVICES);
  return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_immediate_alert_client
 * @brief      this is the application of GATT client for immediate alert service.
 * @param[in]  none.
 * @return     none.
 * @section description
 * This function is used to test the immediate alert service client role.
 */
void rsi_ble_immediate_alert_client(void)
{
  int32_t status = 0;
  int32_t event_id;
  int8_t rssi;
  uint8_t ix, data;
  uuid_t service_uuid;
  uint32_t last_time = 0, present_time = 0;
  sl_wifi_version_string_t version = { 0 };

  status = sl_wifi_init(&config, default_wifi_event_handler);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\nWi-Fi Initialization Failed, Error Code : 0x%lX\r\n", status);
    return;
  } else {
    LOG_PRINT("\r\nWi-Fi Initialization Success\n");
  }

  //! Firmware version Prints
  status = sl_wifi_get_firmware_version(&version);
  if (status != SL_STATUS_OK) {
    LOG_PRINT("\r\nFirmware version Failed, Error Code : 0x%lX\r\n", status);
  } else {
    LOG_PRINT("\r\nfirmware_version = %s\r\n", version.version);
  }

  //! registering the GAP callback functions
  rsi_ble_gap_register_callbacks(rsi_ble_simple_central_on_adv_report_event,
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
                                  rsi_ble_profile,
                                  rsi_ble_char_services,
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

  //! Set local name
  rsi_bt_set_local_name((uint8_t *)RSI_BLE_APP_NAME);

  //! start scanning
  status = rsi_ble_start_scanning();
  if (status != RSI_SUCCESS) {
    return;
  }
  LOG_PRINT("\r\nScanning started \r\n");

  //! waiting for events from controller.
  while (1) {

    //! Application main loop

    //! checking for events list
    event_id = rsi_ble_app_get_event();
    if (event_id == -1) {
      //! calculate the time difference with last_time
      present_time = osKernelGetTickCount();

      if ((rsi_ble_att1_val_hndl != 0) && ((present_time - last_time) > 1000)) {
        rsi_ble_app_set_event(RSI_BLE_GET_RSSI);
      }
      continue;
    }

    switch (event_id) {
      case RSI_APP_EVENT_ADV_REPORT: {
        //! advertise report event.
        //! clear the advertise report event.
        rsi_ble_app_clear_event(RSI_APP_EVENT_ADV_REPORT);
        status = rsi_ble_connect(remote_addr_type, (int8_t *)remote_dev_bd_addr);
        if (status != RSI_SUCCESS) {
          LOG_PRINT("connect status: 0x%lX\r\n", status);
        }
      } break;

      case RSI_BLE_CONN_EVENT: {
        //! event invokes when connection was completed

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_CONN_EVENT);
        rsi_6byte_dev_address_to_ascii(remote_dev_addr, conn_event_to_app.dev_addr);
        LOG_PRINT("\r\nModule connected to address : %s \r\n", remote_dev_addr);

        //! initiating the alert data and handle
        rsi_ble_att1_val_hndl = 0;
        data                  = 0;

        //! search the immediate alert service
        service_uuid.size      = 2;
        service_uuid.val.val16 = RSI_BLE_NEW_SERVICE_UUID;
        rsi_ble_get_profile((uint8_t *)conn_event_to_app.dev_addr, service_uuid, &rsi_ble_service);
      } break;

      case RSI_BLE_DISCONN_EVENT: {
        //! event invokes when disconnection was completed

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_DISCONN_EVENT);
        device_found = 0;
        LOG_PRINT("\r\nModule got Disconnected\r\n");
        //! start scanning
        status = rsi_ble_start_scanning();
        if (status != RSI_SUCCESS) {
          LOG_PRINT("start_scanning status: 0x%lX\r\n", status);
        }
        LOG_PRINT("\r\nScanning started \r\n");
        //! reset the alert data and handle
        rsi_ble_att1_val_hndl = 0;
        data                  = 0;

      } break;

      case RSI_BLE_GATT_WRITE_EVENT: {
        //! event invokes when write/notification events received

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_WRITE_EVENT);
      } break;

      case RSI_BLE_GATT_PROFILE: {
        //! event invokes when get profile response received

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_PROFILE);

        //! get characteristics of the immediate alert servcie
        rsi_ble_get_char_services(conn_event_to_app.dev_addr,
                                  *(uint16_t *)rsi_ble_service.start_handle,
                                  *(uint16_t *)rsi_ble_service.end_handle,
                                  &char_servs);
      } break;

      case RSI_BLE_GATT_CHAR_SERVICES: {
        //! event invokes when get characteristics of the service response received

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GATT_CHAR_SERVICES);

        //! verifying the immediate alert characteristic
        for (ix = 0; ix < char_servs.num_of_services; ix++) {
          if (char_servs.char_services[ix].char_data.char_uuid.val.val16 == RSI_BLE_ATTRIBUTE_1_UUID) {
            rsi_ble_att1_val_hndl = char_servs.char_services[ix].char_data.char_handle;

            //! set the event to calculate RSSI value
            rsi_ble_app_set_event(RSI_BLE_GET_RSSI);

            last_time = osKernelGetTickCount();
            break;
          }
        }
      } break;

      case RSI_BLE_GET_RSSI: {
        //! event invokes when time is expired

        //! clear the served event
        rsi_ble_app_clear_event(RSI_BLE_GET_RSSI);

        if (rsi_ble_att1_val_hndl != 0) {

          //! calculate the RSSI value
          rsi_bt_get_rssi((uint8_t *)conn_event_to_app.dev_addr, (int8_t *)&rssi);

          if (rssi >= RSI_BLE_RSSI_THRESHOLD_VALUE) {
            if (data == 0) {
              data = 1;
              //! set the middle alert at GATT server
              rsi_ble_set_att_cmd(conn_event_to_app.dev_addr, rsi_ble_att1_val_hndl, 1, &data);
            }
          } else {
            if (data == 1) {
              data = 0;
              //! set the low alert in GATT server
              rsi_ble_set_att_cmd(conn_event_to_app.dev_addr, rsi_ble_att1_val_hndl, 1, &data);
            }
          }
        }

        //! taking tick count
        last_time = osKernelGetTickCount();
      } break;
      default: {
      }
    }
  }
}

void app_init(void)
{
  osThreadNew((osThreadFunc_t)rsi_ble_immediate_alert_client, NULL, &thread_attributes);
}
