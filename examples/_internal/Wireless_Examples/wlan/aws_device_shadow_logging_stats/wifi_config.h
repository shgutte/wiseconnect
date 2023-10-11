/*******************************************************************************
* @file  wifi_config.c
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
#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

/*==================================================*/
// Asynchronous message for connection state notification
typedef struct sl_si91x_state_notification_s {
  uint8_t TimeStamp[4];
  uint8_t StateCode;
  uint8_t reason_code;
  uint8_t sl_si91x_channel;
  uint8_t sl_si91x_rssi;
  uint8_t sl_si91x_bssid[6];
} sl_si91x_state_notification_t;

/*==================================================*/
#define WLAN_MODULE_STATES 11
#define WLAN_REASON_CODES  50
struct sl_si91x_bit_2_string {
  uint8_t bit;
  char *string;
};
static const struct sl_si91x_bit_2_string STATE[WLAN_MODULE_STATES] = {
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

static const struct sl_si91x_bit_2_string REASONCODE[WLAN_REASON_CODES] = {
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
