/*******************************************************************************
* @file  wifi_config.h
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
 * @file         wifi_config.h
 * @version      0.1
 *
 *  @brief : This file contains user configurable details to configure the device
 *
 *  @section Description  This file contains user configurable details to configure the device
 *
 *
 */
#ifndef RSI_CONFIG_H
#define RSI_CONFIG_H

#define RSI_APP_BUF_SIZE 1600

//! Enumeration for states in application
typedef enum sl_wifi_app_state_e {
  SL_WIFI_INITIAL_STATE          = 0,
  SL_WIFI_UNCONNECTED_STATE      = 1,
  SL_WIFI_CONNECTED_STATE        = 2,
  SL_WIFI_IPCONFIG_DONE_STATE    = 3,
  SL_WIFI_SOCKET_CONNECTED_STATE = 4,
  SL_WIFI_SCAN_STATE             = 5,
  SL_WIFI_JOIN_STATE             = 6,
  SL_WIFI_SOCKET_RECEIVE_STATE   = 7,

  SL_WIFI_MQTT_INIT_STATE               = 8,
  SL_WIFI_MQTT_CONNECT_STATE            = 9,
  SL_WIFI_MQTT_AUTO_RECONNECT_SET_STATE = 18,
  SL_WIFI_MQTT_SUBSCRIBE_STATE          = 19,
  SL_WIFI_MQTT_PUBLISH_STATE            = 20,
  /*
  SL_WIFI_MQTT_INIT_DONE_STATE      = 8,
  SL_WIFI_MQTT_SUBSCRIBE_DONE_STATE = 9,
  */
  SL_BLE_GATT_WRITE_EVENT      = 10,
  SL_WIFI_DISCONNECTED_STATE   = 11,
  SL_WIFI_DISCONN_NOTIFY_STATE = 12,
  SL_WIFI_ERROR_STATE          = 13,
  SL_WIFI_FLASH_STATE          = 14,
  SL_WIFI_DATA_RECEIVE_STATE   = 15,
  SL_SD_WRITE_STATE            = 16,
  SL_WIFI_DEMO_COMPLETE_STATE  = 17
} sl_wifi_app_state_t;

typedef enum rsi_app_cmd_e {
  SL_DATA                      = 0,
  SL_WIFI_SCAN_RESP            = 1,
  SL_WIFI_CONNECTION_STATUS    = 2,
  SL_WIFI_DISCONNECTION_STATUS = 3,
  SL_WIFI_DISCONNECTION_NOTIFY = 4,
  SL_WIFI_TIMEOUT_NOTIFY       = 5
} rsi_app_cmd_t;

/*==================================================*/
// Asynchronous message for connection state notification
typedef struct rsi_state_notification_s {
  uint8_t TimeStamp[4];
  uint8_t StateCode;
  uint8_t reason_code;
  uint8_t rsi_channel;
  uint8_t rsi_rssi;
  uint8_t rsi_bssid[6];
} rsi_state_notification_t;

/*==================================================*/
#define WLAN_MODULE_STATES 11
#define WLAN_REASON_CODES  50
struct rsi_bit_2_string {
  uint8_t bit;
  char *string;
};
static const struct rsi_bit_2_string STATE[WLAN_MODULE_STATES] = {
  { 0x10, "Beacon Loss (Failover Roam)" },
  { 0x20, "De-authentication (AP induced Roam / Disconnect from supplicant" },
  { 0x50, "Current AP is best" },
  { 0x60, "Better AP found" },
  { 0x70, "No AP found" },
  { 0x80, "Associated" },
  { 0x90, "Unassociated" },
  { 0x01, "Authentication denial" },
  { 0x02, "Association denial" },
  { 0x03, "AP not present" },
  { 0x05, "WPA2 key exchange failed" }

};

static const struct rsi_bit_2_string REASONCODE[WLAN_REASON_CODES] = {
  { 0x01, "Authentication denial" },
  { 0x02, "Association denial" },
  { 0x10, "Beacon Loss (Failover Roam)" },
  { 0x20, "De-authentication (AP induced Roam/Deauth from supplicant)" },
  { 0x07, "PSK not configured" },
  { 0x05, "Roaming not enabled" },
  { 0x28, "TLS CA Cert not present" },
  { 0x29, "TLS PRIVATE key not present " },
  { 0x2A, "TLS Client Cert not present" },
  { 0x2B, "TLS no Cert present" },
  { 0x2C, "PEAP CA Cert not present" },
  { 0x2D, "Server Cert Invalid Key Type" },
  { 0x2E, "Server Intermediate CA Invalid Key Type" },
  { 0x2F, "Server Root CA Invalid Key Type" },
  { 0x30, "Client Cert Invalid Key Type" },
  { 0x31, "Client Root CA Invalid Key Type" },
  { 0x32, "FIPS Server Cert Invalid Length" },
  { 0x33, "FIPS Server Intermediate CA Invalid Length" },
  { 0x34, "FIPS Server Root CA Invalid Length" },
  { 0x35, "FIPS Client Cert Invlaid Length" },
  { 0x36, "FIPS Client Root CA Invalid Length" },
  { 0x37, "Server Cert Invalid Length" },
  { 0x38, "Server Intermediate CA Invalid Length" },
  { 0x39, "Server Root CA Invalid Length" },
  { 0x3A, "Client Cert Invalid Lenght" },
  { 0x3B, "Client Root CA Invalid Length" },
  { 0x3C, "Server Cert Invalid Sign Alg" },
  { 0x3D, "Server Intermediate CA Invalid Sign Alg" },
  { 0x3E, "Server Root CA Invalid Sign Length" },
  { 0x3F, "Client Cert Invalid Sign Alg" },
  { 0x40, "Client Root CA Invalid Sign Length" },
  { 0x41, "Server Intermediate CA not Present" },
  { 0x42, "Server Root CA Parse Error" },
  { 0x43, "Server Intermediate Root CA Parse Error" },
  { 0x44, "Sever Cert Parse Error" },
  { 0x45, "Client Cert Parse Error" },
  { 0x46, "Incorrect Private Key Password" },
  { 0x47, "EAP Failure Received" },
  { 0x48, "Client Cert Bad Date Error" },
  { 0x49, "Server Cert Bad Date Error" },
  { 0x4A, "Server Root CA Bad Date Error" },
  { 0x4B, "Client Root CA Bad Date Error" },
  { 0x4C, "Server Intermediate Root CA Bad Date Error" },
  { 0x4D, "Pem Header Error" },
  { 0x4E, "Pem Footer Error" },
  { 0x4F, "Client Intermediate CA Invalid Sign Length" },
  { 0x50, "Client Intermediate CA Invalid Length" },
  { 0x51, "FIPS Client Intermediate CA Invalid Length" },
  { 0x52, "Client Intermediate CA invalid Key Type" },
  { 0x53, "Pem Error" }
};

#endif
