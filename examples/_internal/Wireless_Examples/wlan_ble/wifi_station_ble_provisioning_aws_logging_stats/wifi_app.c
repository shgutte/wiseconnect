/*******************************************************************************
* @file  wifi_app.c
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
 * */

//! SL Wi-Fi SDK includes
#include "sl_constants.h"
#include "sl_wifi.h"
#include "sl_wifi_callback_framework.h"
#include "sl_net.h"
#include "sl_net_si91x.h"
#include "sl_utility.h"

#include "cmsis_os2.h"
#include <string.h>

#include "rsi_common_apis.h"
#include "rsi_bt_common_apis.h"

#include "aws_client_certificate.pem.crt.h"
#include "aws_client_private_key.pem.key.h"
#include "aws_starfield_ca.pem.h"

//! AWS Includes
#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_error.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "ble_config.h"
#include "wifi_config.h"
#include "wifi_config.h"

/******************************************************
*                    Constants
******************************************************/
#define DHCP_HOST_NAME    NULL
#define TIMEOUT_MS        5000
#define WIFI_SCAN_TIMEOUT 10000

#define MQTT_TOPIC    "$aws/things/silicon_labs_thing/shadow/update"
#define MQTT_USERNAME "username"
#define MQTT_PASSWORD "password"

#define GPIO_PIN          0
#define CERTIFICATE_INDEX 0

//! Message to publish
uint8_t publish_message_mq[] = "{\"state\":{\"desired\":{\"toggle\":1}}}";

/*
 *********************************************************************************************************
 *                                         LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

sl_wifi_scan_result_t *scan_result          = NULL;
static volatile bool scan_complete          = false;
static volatile sl_status_t callback_status = SL_STATUS_OK;
uint16_t scanbuf_size = (sizeof(sl_wifi_scan_result_t) + (SL_MAX_SCANNED_AP * sizeof(scan_result->scan_info[0])));

sl_wifi_performance_profile_t wifi_profile = { ASSOCIATED_POWER_SAVE, 0, 0, 1000, { 0 } };

uint8_t connected = 0, timeout = 0;
uint8_t disconnected = 0, disassosiated = 0;
uint8_t a = 0;

sl_wifi_client_configuration_t access_point = { 0 };
sl_net_ip_configuration_t ip_address        = { 0 };

static uint32_t wlan_app_event_map;

uint8_t retry = 1;

uint8_t yield;
AWS_IoT_Client client   = { 0 };
uint8_t disconnect_flag = 0;
uint8_t power_save_given;

/*
 *********************************************************************************************************
 *                                               DATA TYPES
 *********************************************************************************************************
 */
extern void sl_wifi_app_send_to_ble(uint16_t msg_type, uint8_t *data, uint16_t data_len);
extern uint8_t coex_ssid[50], pwd[34], sec_type;
void sl_wifi_mqtt_task(void);

uint8_t conn_status;
extern uint8_t magic_word;

// WLAN include file for configuration
osSemaphoreId_t rsi_mqtt_sem;
extern osSemaphoreId_t wlan_thread_sem;

/*==============================================*/
/**
 * @fn         sl_wifi_app_set_event
 * @brief      sets the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to set/raise the specific event.
 */
void sl_wifi_app_set_event(uint32_t event_num)
{
  wlan_app_event_map |= BIT(event_num);

  osSemaphoreRelease(wlan_thread_sem);

  return;
}

/*==============================================*/
/**
 * @fn         sl_wifi_app_clear_event
 * @brief      clears the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to clear the specific event.
 */
void sl_wifi_app_clear_event(uint32_t event_num)
{
  wlan_app_event_map &= ~BIT(event_num);
  return;
}

/*==============================================*/
/**
 * @fn         sl_wifi_app_get_event
 * @brief      returns the first set event based on priority
 * @param[in]  none.
 * @return     int32_t
 *             > 0  = event number
 *             -1   = not received any event
 * @section description
 * This function returns the highest priority event among all the set events
 */
int32_t sl_wifi_app_get_event(void)
{
  uint32_t ix;

  for (ix = 0; ix < 32; ix++) {
    if (wlan_app_event_map & (1 << ix)) {
      return ix;
    }
  }

  return (-1);
}

// rejoin failure call back handler in station mode
sl_status_t join_callback_handler(sl_wifi_event_t event, char *result, uint32_t result_length, void *arg)
{
  UNUSED_PARAMETER(event);
  UNUSED_PARAMETER(result);
  UNUSED_PARAMETER(result_length);
  UNUSED_PARAMETER(arg);

  // update wlan application state
  disconnected = 1;
  connected    = 0;

  sl_wifi_app_set_event(SL_WIFI_DISCONNECTED_STATE);

  return SL_STATUS_OK;
}

void rsi_wlan_app_call_backs_init(void)
{
  //! Initialize join fail call back
  sl_wifi_set_join_callback(join_callback_handler, NULL);
}

/**
 * @brief This parameter will avoid infinite loop of publish and exit the program after certain number of publishes
 */
static void iot_subscribe_callback_handler(AWS_IoT_Client *pClient,
                                           char *topicName,
                                           uint16_t topicNameLen,
                                           IoT_Publish_Message_Params *params,
                                           void *pData)
{
  UNUSED_PARAMETER(pClient);
  UNUSED_PARAMETER(topicName);
  UNUSED_PARAMETER(topicNameLen);
  UNUSED_PARAMETER(pData);
  char dt[1000] = { 0 };
  uint32_t len;
  len = params->payloadLen;

  strncpy(dt, params->payload, len);
  LOG_PRINT("\r\n data received = %s\r\n", dt);

  sl_wifi_app_set_event(SL_WIFI_MQTT_PUBLISH_STATE);
}

static void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data)
{
  IoT_Error_t rc = FAILURE;
  LOG_PRINT("MQTT Disconnect");
  if (NULL == pClient) {
    return;
  }
  IOT_UNUSED(data);
  if (aws_iot_is_autoreconnect_enabled(pClient)) {
    LOG_PRINT("Auto Reconnect is enabled, Reconnecting attempt will start now\n");
  } else {
    LOG_PRINT("Auto Reconnect not enabled. Starting manual reconnect...\n");
    rc = aws_iot_mqtt_attempt_reconnect(pClient);
    if (NETWORK_RECONNECTED == rc) {
      LOG_PRINT("Manual Reconnect Successful");
    } else {
      LOG_PRINT("Manual Reconnect \n");
    }
  }
}

sl_status_t load_certificates_in_flash(void)
{
  sl_status_t status;

  // Load SSL CA certificate
  status = sl_net_set_credential(SL_NET_TLS_SERVER_CREDENTIAL_ID(CERTIFICATE_INDEX),
                                 SL_NET_SIGNING_CERTIFICATE,
                                 aws_starfield_ca,
                                 sizeof(aws_starfield_ca));
  if (status != SL_STATUS_OK) {
    printf("\r\nLoading TLS CA certificate in to FLASH Failed, Error Code : 0x%lX\r\n", status);
    return status;
  }
  printf("\r\nLoading TLS CA certificate at index %d Successfull\r\n", CERTIFICATE_INDEX);

  // Load SSL Client certificate
  status = sl_net_set_credential(SL_NET_TLS_CLIENT_CREDENTIAL_ID(CERTIFICATE_INDEX),
                                 SL_NET_CERTIFICATE,
                                 aws_client_certificate,
                                 sizeof(aws_client_certificate));
  if (status != SL_STATUS_OK) {
    printf("\r\nLoading TLS Client certificate in to FLASH Failed, Error Code : 0x%lX\r\n", status);
    return status;
  }
  printf("\r\nLoading TLS Client certificate at index %d Successfull\r\n", CERTIFICATE_INDEX);

  // Load SSL Client private key
  status = sl_net_set_credential(SL_NET_TLS_CLIENT_CREDENTIAL_ID(CERTIFICATE_INDEX),
                                 SL_NET_PRIVATE_KEY,
                                 aws_client_private_key,
                                 sizeof(aws_client_private_key));
  if (status != SL_STATUS_OK) {
    printf("\r\nLoading TLS Client private key in to FLASH Failed, Error Code : 0x%lX\r\n", status);
  } else {
    printf("\r\nLoading TLS Client private key at index %d Successfull\r\n", CERTIFICATE_INDEX);
  }

  return status;
}

int32_t rsi_wlan_mqtt_certs_init(void)
{
  sl_status_t status = RSI_SUCCESS;

  status = load_certificates_in_flash();
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading certificates: 0x%lx\r\n", status);
    return status;
  }

  rsi_wlan_app_call_backs_init();

  return status;
}

static sl_status_t show_scan_results()
{
  printf("%lu Scan results:\n", scan_result->scan_count);

  if (scan_result->scan_count) {
    printf("\n   %s %24s %s", "SSID", "SECURITY", "NETWORK");
    printf("%12s %12s %s\n", "BSSID", "CHANNEL", "RSSI");

    for (int a = 0; a < (int)scan_result->scan_count; ++a) {
      uint8_t *bssid = (uint8_t *)&scan_result->scan_info[a].bssid;
      printf("%-24s %4u,  %4u, ",
             scan_result->scan_info[a].ssid,
             scan_result->scan_info[a].security_mode,
             scan_result->scan_info[a].network_type);
      printf("  %02x:%02x:%02x:%02x:%02x:%02x, %4u,  -%u\n",
             bssid[0],
             bssid[1],
             bssid[2],
             bssid[3],
             bssid[4],
             bssid[5],
             scan_result->scan_info[a].rf_channel,
             scan_result->scan_info[a].rssi_val);
    }
  }

  return SL_STATUS_OK;
}

sl_status_t wlan_app_scan_callback_handler(sl_wifi_event_t event,
                                           sl_wifi_scan_result_t *result,
                                           uint32_t result_length,
                                           void *arg)
{
  UNUSED_PARAMETER(result_length);
  UNUSED_PARAMETER(arg);

  scan_complete = true;

  if (CHECK_IF_EVENT_FAILED(event)) {
    callback_status = *(sl_status_t *)result;
    return SL_STATUS_FAIL;
  }

  memset(scan_result, 0, scanbuf_size);
  memcpy(scan_result, result, scanbuf_size);

  callback_status = show_scan_results();

  //  scan_complete = true;
  return SL_STATUS_OK;
}

void sl_wifi_app_task(void)
{
  int32_t status   = RSI_SUCCESS;
  int32_t event_id = 0;

  // Allocate memory for scan buffer
  scan_result = (sl_wifi_scan_result_t *)malloc(scanbuf_size);
  if (scan_result == NULL) {
    LOG_PRINT("Failed to allocate memory for scan result\n");
    return;
  }

  while (1) {
    // checking for events list
    event_id = sl_wifi_app_get_event();
    if (event_id == -1) {
      osSemaphoreAcquire(wlan_thread_sem, osWaitForever);
      // if events are not received loop will be continued.
      continue;
    }

    switch (event_id) {
      case SL_WIFI_INITIAL_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_INITIAL_STATE);
        LOG_PRINT("SL_WIFI_INITIAL_STATE\n");

        // update wlan application state
        if (magic_word) {
          // clear the served event
          sl_wifi_app_set_event(SL_WIFI_FLASH_STATE);
        } else {
          sl_wifi_app_set_event(SL_WIFI_SCAN_STATE);
        }
      } break;

      case SL_WIFI_UNCONNECTED_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_UNCONNECTED_STATE);
        LOG_PRINT("SL_WIFI_UNCONNECTED_STATE\n");

        // Any additional code if required

        osSemaphoreRelease(wlan_thread_sem);
      } break;

      case SL_WIFI_SCAN_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_SCAN_STATE);

        sl_wifi_scan_configuration_t wifi_scan_configuration = { 0 };
        wifi_scan_configuration                              = default_wifi_scan_configuration;

        sl_wifi_set_scan_callback(wlan_app_scan_callback_handler, NULL);

        status = sl_wifi_start_scan(SL_WIFI_CLIENT_2_4GHZ_INTERFACE, NULL, &wifi_scan_configuration);
        if (SL_STATUS_IN_PROGRESS == status) {
          LOG_PRINT("Scanning...\r\n");
          const uint32_t start = osKernelGetTickCount();

          while (!scan_complete && (osKernelGetTickCount() - start) <= WIFI_SCAN_TIMEOUT) {
            osThreadYield();
          }
          status = scan_complete ? callback_status : SL_STATUS_TIMEOUT;
        }
        if (status != SL_STATUS_OK) {
          LOG_PRINT("\r\nWLAN Scan Wait Failed, Error Code : 0x%lX\r\n", status);
          sl_wifi_app_set_event(SL_WIFI_SCAN_STATE);
          osDelay(1000);
        } else {
          // update wlan application state
          sl_wifi_app_send_to_ble(SL_WIFI_SCAN_RESP, (uint8_t *)scan_result, scanbuf_size);
        }
      } break;

      case SL_WIFI_JOIN_STATE: {
        sl_wifi_credential_t cred  = { 0 };
        sl_wifi_credential_id_t id = SL_NET_DEFAULT_WIFI_CLIENT_CREDENTIAL_ID;

        sl_wifi_app_clear_event(SL_WIFI_JOIN_STATE);

        cred.type = SL_WIFI_PSK_CREDENTIAL;
        memcpy(cred.psk.value, pwd, strlen((char *)pwd));

        status = sl_net_set_credential(id, SL_NET_WIFI_PSK, pwd, strlen((char *)pwd));
        if (SL_STATUS_OK == status) {
          printf("Credentials set, id : %lu\n", id);

          access_point.ssid.length = strlen((char *)coex_ssid);
          memcpy(access_point.ssid.value, coex_ssid, access_point.ssid.length);
          access_point.security      = sec_type;
          access_point.encryption    = SL_WIFI_CCMP_ENCRYPTION;
          access_point.credential_id = id;

          LOG_PRINT("SSID %s\n", access_point.ssid.value);
          status = sl_wifi_connect(SL_WIFI_CLIENT_2_4GHZ_INTERFACE, &access_point, TIMEOUT_MS);
        }
        if (status != RSI_SUCCESS) {
          timeout = 1;
          sl_wifi_app_send_to_ble(SL_WIFI_TIMEOUT_NOTIFY, (uint8_t *)&timeout, 1);
          LOG_PRINT("\r\nWLAN Connect Failed, Error Code : 0x%lX\r\n", status);

          // update wlan application state
          disconnected = 1;
          connected    = 0;
        } else {
          LOG_PRINT("\n WLAN connection is successful\n");
          // update wlan application state
          sl_wifi_app_set_event(SL_WIFI_CONNECTED_STATE);
        }
        LOG_PRINT("RSI_WLAN_JOIN_STATE\n");
      } break;

      case SL_WIFI_FLASH_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_FLASH_STATE);

        if (retry) {
          status = sl_wifi_connect(SL_WIFI_CLIENT_2_4GHZ_INTERFACE, &access_point, TIMEOUT_MS);
          if (status != RSI_SUCCESS) {
            LOG_PRINT("\r\nWLAN Connect Failed, Error Code : 0x%lX\r\n", status);
            break;
          } else {
            sl_wifi_app_set_event(SL_WIFI_CONNECTED_STATE);
          }
        }
      } break;

      case SL_WIFI_CONNECTED_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_CONNECTED_STATE);

        ip_address.type      = SL_IPV4;
        ip_address.mode      = SL_IP_MANAGEMENT_DHCP;
        ip_address.host_name = DHCP_HOST_NAME;

        // Configure IP
        status = sl_si91x_configure_ip_address(&ip_address, CLIENT_MODE);
        if (status != RSI_SUCCESS) {
          a++;
          if (a == 3) {
            a       = 0;
            timeout = 1;
            status  = sl_wifi_disconnect(SL_WIFI_CLIENT_INTERFACE);
            if (status == RSI_SUCCESS) {
              connected     = 0;
              disassosiated = 1;
              sl_wifi_app_send_to_ble(SL_WIFI_TIMEOUT_NOTIFY, (uint8_t *)&timeout, 1);
              sl_wifi_app_set_event(SL_WIFI_ERROR_STATE);
            }
          }
          LOG_PRINT("\r\nIP Config Failed, Error Code : 0x%lX\r\n", status);
          break;
        } else {
          a             = 0;
          connected     = 1;
          conn_status   = 1;
          disconnected  = 0;
          disassosiated = 0;

#if defined(RSI_DEBUG_PRINTS)
          sl_ip_address_t ip = { 0 };
          ip.type            = ip_address.type;
          ip.ip.v4.value     = ip_address.ip.v4.ip_address.value;
          print_sl_ip_address(&ip);
#endif

          // update wlan application state
          sl_wifi_app_set_event(SL_WIFI_IPCONFIG_DONE_STATE);
          sl_wifi_app_send_to_ble(SL_WIFI_CONNECTION_STATUS, (uint8_t *)&connected, 1);
        }
        LOG_PRINT("SL_WIFI_CONNECTED_STATE\n");
      } break;

      case SL_WIFI_IPCONFIG_DONE_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_IPCONFIG_DONE_STATE);

        sl_wifi_app_set_event(SL_WIFI_MQTT_INIT_STATE);
        sl_wifi_mqtt_task();

        LOG_PRINT("SL_WIFI_IPCONFIG_DONE_STATE\n");
      } break;

      case SL_WIFI_ERROR_STATE: {

      } break;

      case SL_WIFI_DISCONNECTED_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_DISCONNECTED_STATE);
        retry = 1;
        sl_wifi_app_send_to_ble(SL_WIFI_DISCONNECTION_STATUS, (uint8_t *)&disconnected, 1);
        sl_wifi_app_set_event(SL_WIFI_FLASH_STATE);

        LOG_PRINT("SL_WIFI_DISCONNECTED_STATE\n");
      } break;

      case SL_WIFI_DISCONN_NOTIFY_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_DISCONN_NOTIFY_STATE);

        status = sl_wifi_disconnect(SL_WIFI_CLIENT_INTERFACE);
        if (status == RSI_SUCCESS) {
#if RSI_WISE_MCU_ENABLE
          rsi_flash_erase((uint32_t)FLASH_ADDR_TO_STORE_AP_DETAILS);
#endif
          LOG_PRINT("\r\nWLAN Disconnected\r\n");
          disassosiated   = 1;
          connected       = 0;
          yield           = 0;
          disconnect_flag = 0; // reset flag to allow disconnecting again

          sl_wifi_app_send_to_ble(SL_WIFI_DISCONNECTION_NOTIFY, (uint8_t *)&disassosiated, 1);
          sl_wifi_app_set_event(SL_WIFI_UNCONNECTED_STATE);
        } else {
          LOG_PRINT("\r\nWIFI Disconnect Failed, Error Code : 0x%lX\r\n", status);
        }

        LOG_PRINT("SL_WIFI_DISCONN_NOTIFY_STATE\n");
      } break;
      default:
        break;
    }
  }

  if (scan_result != NULL) {
    free(scan_result);
  }
}

void sl_wifi_mqtt_task(void)
{
  IoT_Error_t rc   = FAILURE;
  int32_t event_id = 0;

  IoT_Client_Init_Params mqttInitParams   = iotClientInitParamsDefault;
  IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

  IoT_Publish_Message_Params paramsQOS0;
  IoT_Publish_Message_Params paramsQOS1;

  mqttInitParams.enableAutoReconnect       = false;
  mqttInitParams.pHostURL                  = AWS_IOT_MQTT_HOST;
  mqttInitParams.port                      = AWS_IOT_MQTT_PORT;
  mqttInitParams.pRootCALocation           = (char *)aws_starfield_ca;
  mqttInitParams.pDeviceCertLocation       = (char *)aws_client_certificate;
  mqttInitParams.pDevicePrivateKeyLocation = (char *)aws_client_private_key;
  mqttInitParams.mqttCommandTimeout_ms     = 20000;
  mqttInitParams.tlsHandshakeTimeout_ms    = 5000;
  mqttInitParams.isSSLHostnameVerify       = true;
  mqttInitParams.disconnectHandler         = disconnectCallbackHandler;
  mqttInitParams.disconnectHandlerData     = NULL;

  connectParams.keepAliveIntervalInSec = 600;
  connectParams.isCleanSession         = true;
  connectParams.MQTTVersion            = MQTT_3_1_1;
  connectParams.pClientID              = AWS_IOT_MQTT_CLIENT_ID;
  connectParams.clientIDLen            = (uint16_t)strlen(AWS_IOT_MQTT_CLIENT_ID);
  connectParams.isWillMsgPresent       = false;

  connectParams.pUsername   = MQTT_USERNAME;
  connectParams.usernameLen = strlen(MQTT_USERNAME);
  connectParams.pPassword   = MQTT_PASSWORD;
  connectParams.passwordLen = strlen(MQTT_PASSWORD);

  while (1) {
    event_id = sl_wifi_app_get_event();
    if (event_id == -1) {
      osSemaphoreAcquire(wlan_thread_sem, osWaitForever);

      // if events are not received loop will be continued.
      continue;
    }
    switch (event_id) {
      case SL_WIFI_MQTT_INIT_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_MQTT_INIT_STATE);

        printf("In SL_WIFI_MQTT_INIT_STATE\n");
        rc = aws_iot_mqtt_init(&client, &mqttInitParams);
        if (SUCCESS != rc) {
          sl_wifi_app_set_event(SL_WIFI_MQTT_INIT_STATE);
          LOG_PRINT("aws_iot_mqtt_init returned error ");
        } else {
          printf("mqtt init successful");
          sl_wifi_app_set_event(SL_WIFI_MQTT_CONNECT_STATE);
        }
      } break;

      case SL_WIFI_MQTT_CONNECT_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_MQTT_CONNECT_STATE);

        LOG_PRINT("\r\nAWS IOT MQTT Connecting...\r\n");
        rc = aws_iot_mqtt_connect(&client, &connectParams);
        if (SUCCESS != rc) {
          if (rc == NETWORK_ALREADY_CONNECTED_ERROR) {
            LOG_PRINT("Network is already connected\n");
            sl_wifi_app_set_event(SL_WIFI_MQTT_SUBSCRIBE_STATE);
          } else {
            LOG_PRINT("\r\nError in connection %d\r\n", rc);
            sl_wifi_app_set_event(SL_WIFI_MQTT_CONNECT_STATE);
          }
        } else {
          sl_wifi_app_set_event(SL_WIFI_MQTT_AUTO_RECONNECT_SET_STATE);
        }
      } break;

      case SL_WIFI_MQTT_AUTO_RECONNECT_SET_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_MQTT_AUTO_RECONNECT_SET_STATE);

        rc = aws_iot_mqtt_autoreconnect_set_status(&client, false);
        if (SUCCESS != rc) {
          sl_wifi_app_set_event(SL_WIFI_MQTT_AUTO_RECONNECT_SET_STATE);
          LOG_PRINT("Unable to set Auto Reconnect to true\n ");
        } else {
          sl_wifi_app_set_event(SL_WIFI_MQTT_SUBSCRIBE_STATE);
        }
      } break;

      case SL_WIFI_MQTT_SUBSCRIBE_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_MQTT_SUBSCRIBE_STATE);
        LOG_PRINT("\r\nAWS IOT MQTT Subscribe...\r\n");

        rc = aws_iot_mqtt_subscribe(&client,
                                    MQTT_TOPIC,
                                    strlen(MQTT_TOPIC) /*11*/,
                                    QOS0,
                                    iot_subscribe_callback_handler,
                                    /*paramsQOS0.payload */ client.clientData.readBuf);
        if (SUCCESS != rc) {
          LOG_PRINT("\r\nError subscribing %d\r\n ", rc);
          sl_wifi_app_set_event(SL_WIFI_MQTT_SUBSCRIBE_STATE);
        } else {
          sl_wifi_app_set_event(SL_WIFI_MQTT_PUBLISH_STATE);
        }
      } break;

      case SL_WIFI_MQTT_PUBLISH_STATE: {
        sl_wifi_app_clear_event(SL_WIFI_MQTT_PUBLISH_STATE);

        LOG_PRINT("AWS IOT MQTT Publish...\n");
        paramsQOS0.qos        = QOS0;
        paramsQOS0.payload    = (void *)publish_message_mq;
        paramsQOS0.isRetained = 0;

        paramsQOS1.qos        = QOS1;
        paramsQOS1.payload    = (void *)publish_message_mq;
        paramsQOS1.isRetained = 0;
#ifdef MQTT_YIELD_EN
        LOG_PRINT("AWS IOT MQTT Yield ...\n");
        //! Configure LED
        RSI_EGPIO_SetPinMux(EGPIO1, EGPIO_PORT0, GPIO_PIN, EGPIO_PIN_MUX_MODE0);
        RSI_EGPIO_SetDir(EGPIO1, EGPIO_PORT0, GPIO_PIN, EGPIO_CONFIG_DIR_OUTPUT);

        //! Waiting for data from cloud
        LOG_PRINT("Waiting for data from cloud...\n");
        rc = aws_iot_mqtt_yield(&client, 1000);
        if (NETWORK_ATTEMPTING_RECONNECT == rc) {
          // If the client is attempting to reconnect we will skip the rest of the loop.
          continue;
        }
        //! toggle LED based on msg received from cloud
        for (int i = 0; i < AWS_IOT_MQTT_RX_BUF_LEN; i++) {
          if (client.clientData.readBuf[i] == 't' && client.clientData.readBuf[i + 1] == 'o'
              && client.clientData.readBuf[i + 2] == 'g') {
            LOG_PRINT("Toggling LED\n");
            RSI_EGPIO_TogglePort(EGPIO1, EGPIO_PORT0, (0x1 << GPIO_PIN));
            break;
          }
        }
#endif
        paramsQOS0.payloadLen = strlen((char *)publish_message_mq);
        rc                    = aws_iot_mqtt_publish(&client, MQTT_TOPIC, strlen(MQTT_TOPIC), &paramsQOS0);

        paramsQOS1.payloadLen = strlen((char *)publish_message_mq);
        rc                    = aws_iot_mqtt_publish(&client, MQTT_TOPIC, strlen(MQTT_TOPIC), &paramsQOS1);
        if (rc == MQTT_REQUEST_TIMEOUT_ERROR) {
          LOG_PRINT("\r\nQOS1 publish ack not received.\r\n");
        } else if (rc == 0) {
          LOG_PRINT("\r\nData Published successfully to cloud...\r\n");
          yield = 0;
        } else {
          LOG_PRINT("\r\nData Published Fail :%d\r\n", rc);
        }
        if (disconnect_flag == 0) {
          sl_wifi_app_set_event(SL_WIFI_MQTT_PUBLISH_STATE);

        } else {
          sl_wifi_app_set_event(SL_WIFI_DISCONN_NOTIFY_STATE);
        }
      } break;
      case SL_WIFI_INITIAL_STATE:
      case SL_WIFI_UNCONNECTED_STATE:
      case SL_WIFI_CONNECTED_STATE:
      case SL_WIFI_IPCONFIG_DONE_STATE:
      case SL_WIFI_SOCKET_CONNECTED_STATE:
      case SL_WIFI_SCAN_STATE:
      case SL_WIFI_JOIN_STATE:
      case SL_WIFI_SOCKET_RECEIVE_STATE:
        break;
      case SL_WIFI_DISCONNECTED_STATE:
      case SL_WIFI_DISCONN_NOTIFY_STATE:
        return;
      case SL_WIFI_ERROR_STATE:
      case SL_WIFI_FLASH_STATE:
      case SL_SD_WRITE_STATE:
      case SL_BLE_GATT_WRITE_EVENT:
      case SL_WIFI_DEMO_COMPLETE_STATE:
        break;
    }
  }
}
