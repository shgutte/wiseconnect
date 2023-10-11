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

#include <string.h>
#include "cmsis_os2.h"
#include "sl_status.h"
#include "sl_net.h"
#include "sl_wifi.h"
#include "sl_wifi_device.h"
#include "sl_net_wifi_types.h"
#include "sl_utility.h"
#include "sl_si91x_driver.h"
#include "wifi_config.h"
#include "sl_wifi_callback_framework.h"

//! Certificates to be loaded
#include "aws_client_certificate.pem.crt.h"
#include "aws_client_private_key.pem.key.h"
#include "aws_starfield_ca.pem.h"

//! AWS files
#include "aws_iot_error.h"
#include "aws_iot_config.h"
#include "aws_iot_shadow_interface.h"

/******************************************************
*                    Constants
******************************************************/
#define JSON_DOC_BUFFER_LENGTH       300
#define ROOM_TEMPERATURE_UPPER_LIMIT 32
#define ROOM_TEMPERATURE_LOWER_LIMIT 25
#define STARTING_ROOM_TEMPERATURE    ROOM_TEMPERATURE_LOWER_LIMIT
#define ENABLE_POWER_SAVE            0

/******************************************************
 *               Function Declarations
 ******************************************************/
static void application_start(void *argument);
sl_status_t load_certificates_in_flash();
sl_status_t start_aws_device_shadow();
static void simulate_room_temperature(float *p_room_temperature, bool *p_window_open);
static void window_actuate_callback(const char *p_json_string, uint32_t json_string_data_len, jsonStruct_t *p_context);
static void shadow_update_status_callback(const char *p_thing_name,
                                          ShadowActions_t action,
                                          Shadow_Ack_Status_t status,
                                          const char *p_received_json_document,
                                          void *p_context_data);
uint8_t *sl_si91x_6byte_dev_address_to_ascii(uint8_t *ascii_mac_address, uint8_t *hex_addr);
int8_t hex_to_ascii(uint8_t hex_num);
/******************************************************
 *               Variable Definitions
 ******************************************************/
const osThreadAttr_t thread_attributes = {
  .name       = "app",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 3072,
  .priority   = osPriorityLow,
  .tz_module  = 0,
  .reserved   = 0,
};

uint32_t wifi_connections, wifi_disconnections, wifi_disconnections_flag;

static const sl_wifi_device_configuration_t client_init_configuration = {
  .boot_option = LOAD_NWP_FW,
  .mac_address = NULL,
  .band        = SL_SI91X_WIFI_BAND_2_4GHZ,
  .boot_config = { .oper_mode       = SL_SI91X_CLIENT_MODE,
                   .coex_mode       = SL_SI91X_WLAN_MODE,
                   .feature_bit_map = (SL_SI91X_FEAT_SECURITY_PSK
#if ENABLE_POWER_SAVE
                                       | SL_SI91X_FEAT_ULP_GPIO_BASED_HANDSHAKE
#endif
                                       ),
                   .tcp_ip_feature_bit_map = (SL_SI91X_TCP_IP_FEAT_DHCPV4_CLIENT | SL_SI91X_TCP_IP_FEAT_DNS_CLIENT
                                              | SL_SI91X_TCP_IP_FEAT_SSL | SL_SI91X_TCP_IP_FEAT_EXTENSION_VALID),
                   .custom_feature_bit_map =
                     (SL_SI91X_FEAT_CUSTOM_FEAT_EXTENTION_VALID | SL_SI91X_CUSTOM_FEAT_ASYNC_CONNECTION_STATUS),
                   .ext_custom_feature_bit_map = (SL_SI91X_EXT_FEAT_XTAL_CLK |
#if ENABLE_POWER_SAVE
                                                  SL_SI91X_EXT_FEAT_LOW_POWER_MODE |
#endif
#ifndef RSI_M4_INTERFACE
                                                  RAM_LEVEL_NWP_ALL_MCU_ZERO
#else
                                                  RAM_LEVEL_NWP_ADV_MCU_BASIC
#endif
#ifdef CHIP_917
                                                  | SL_SI91X_EXT_FEAT_FRONT_END_SWITCH_PINS_ULP_GPIO_4_5_0
#endif
                                                  ),
                   .bt_feature_bit_map         = 0,
                   .ext_tcp_ip_feature_bit_map = (SL_SI91X_CONFIG_FEAT_EXTENTION_VALID),
                   .ble_feature_bit_map        = 0,
                   .ble_ext_feature_bit_map    = 0,
                   .config_feature_bit_map     = (
#if ENABLE_POWER_SAVE
                     SL_SI91X_FEAT_SLEEP_GPIO_SEL_BITMAP
#else
                     0
#endif
                     ) }
};

char json_document_buffer[JSON_DOC_BUFFER_LENGTH];

/******************************************************
 *               Function Definitions
 ******************************************************/
void app_init(void)
{
  osThreadNew((osThreadFunc_t)application_start, NULL, &thread_attributes);
}

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

  if (payload_length != sizeof(sl_si91x_state_notification_t))
    return SL_STATUS_FAIL;
  sl_si91x_state_notification_t *state = (sl_si91x_state_notification_t *)payload;
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
  sl_si91x_6byte_dev_address_to_ascii((uint8_t *)bssid_string, state->sl_si91x_bssid);

  if (*higher_nibble == 'A') {
    wifi_connections++;
    printf("Wi-Fi connections %ld\n", wifi_connections);
  }
  if (*higher_nibble == 'U') {
    wifi_disconnections++;
    wifi_disconnections_flag = 1;
    printf("Wi-Fi disconnections %ld\n", wifi_disconnections);
  }
  if (state->sl_si91x_channel == 0 && state->sl_si91x_rssi == 100) {

  } else if (state->sl_si91x_channel == 0 && state->sl_si91x_rssi != 100) {

  } else if (state->sl_si91x_channel != 0 && state->sl_si91x_rssi == 100) {

  } else {
  }
  return SL_STATUS_OK;
}

static void application_start(void *argument)
{
  UNUSED_PARAMETER(argument);
  sl_net_wifi_client_profile_t profile = { 0 };
  sl_ip_address_t ip_address           = { 0 };

  sl_status_t status = sl_net_init(SL_NET_WIFI_CLIENT_INTERFACE, &client_init_configuration, NULL, NULL);
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while doing init: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nWiFi Init Success\r\n");

  sl_wifi_set_stats_callback(sl_wifi_module_state_stats_callback, NULL);
  printf("\r\n Registered Wi-Fi module state stats callback\n");

#ifdef RSI_M4_INTERFACE
  uint8_t xtal_enable = 1;
  status              = sl_si91x_m4_ta_secure_handshake(SI91X_ENABLE_XTAL, 1, &xtal_enable, 0, NULL);
  if (status != SL_STATUS_OK) {
    printf("Failed to bring m4_ta_secure_handshake: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nm4_ta_secure_handshake Success\r\n");
#endif

  status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
  if (status != SL_STATUS_OK) {
    printf("\r\nError while connecting to Access point: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nConnected to Access point\r\n");

  status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID, &profile);
  if (status != SL_STATUS_OK) {
    printf("\r\nFailed to get client profile: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nClient profile fetched successfully\r\n");

  ip_address.type = SL_IPV4;
  memcpy(&ip_address.ip.v4.bytes, &profile.ip.ip.v4.ip_address.bytes, sizeof(sl_ipv4_address_t));
  print_sl_ip_address(&ip_address);

  status = load_certificates_in_flash();
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading certificates: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nCertificate loading success\r\n");

#if ENABLE_POWER_SAVE
  sl_wifi_performance_profile_t performance_profile = { .profile = ASSOCIATED_POWER_SAVE };

  status = sl_wifi_set_performance_profile(&performance_profile);
  if (status != SL_STATUS_OK) {
    printf("\r\nPower save configuration Failed, Error Code : 0x%lX\r\n", status);
    return;
  }
  printf("\r\nAssociated Power Save Enabled\n");
#endif

  status = start_aws_device_shadow();
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error occurred in AWS Device shadow: 0x%lx\r\n", status);
    return;
  }
  printf("\r\nAWS Device shadow Success\r\n");
}

sl_status_t load_certificates_in_flash()
{
  sl_status_t status = SL_STATUS_FAIL;

  status = sl_net_set_credential(SL_NET_TLS_SERVER_CREDENTIAL_ID(0),
                                 SL_NET_SIGNING_CERTIFICATE,
                                 aws_starfield_ca,
                                 sizeof(aws_starfield_ca));
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading CA certificate: 0x%lx\r\n", status);
    return status;
  }

  status = sl_net_set_credential(SL_NET_TLS_CLIENT_CREDENTIAL_ID(0),
                                 SL_NET_CERTIFICATE,
                                 aws_client_certificate,
                                 sizeof(aws_client_certificate));
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading Client certificate: 0x%lx\r\n", status);
    return status;
  }

  status = sl_net_set_credential(SL_NET_TLS_CLIENT_CREDENTIAL_ID(0),
                                 SL_NET_PRIVATE_KEY,
                                 aws_client_private_key,
                                 sizeof(aws_client_private_key));
  if (status != SL_STATUS_OK) {
    printf("\r\nUnexpected error while loading Private Key: 0x%lx\r\n", status);
  } else {
    printf("\r\nCertificate loading success\r\n");
  }

  return status;
}

sl_status_t start_aws_device_shadow()
{
  IoT_Error_t rc                                      = FAILURE;
  AWS_IoT_Client mqtt_client                          = { 0 };
  ShadowInitParameters_t shadow_init_parameters       = ShadowInitParametersDefault;
  ShadowConnectParameters_t shadow_connect_parameters = ShadowConnectParametersDefault;
  bool window_open_state                              = false;
  jsonStruct_t window_actuator                        = { 0 };
  float temperature                                   = 0.0;
  sl_status_t status                                  = { 0 };

  jsonStruct_t temperature_handler    = { 0 };
  size_t size_of_json_document_buffer = sizeof(json_document_buffer) / sizeof(json_document_buffer[0]);

  shadow_init_parameters.pRootCA             = (char *)aws_starfield_ca;
  shadow_init_parameters.pClientCRT          = (char *)aws_client_certificate;
  shadow_init_parameters.pClientKey          = (char *)aws_client_private_key;
  shadow_init_parameters.enableAutoReconnect = true;

  rc = aws_iot_shadow_init(&mqtt_client, &shadow_init_parameters);
  if (rc < 0) {
    printf("\r\nShadow Initialization failed with aws error: %d\r\n", rc);
    return rc;
  }
  printf("\r\nShadow Initialization Success\r\n");

  shadow_connect_parameters.pMyThingName    = AWS_IOT_MY_THING_NAME;
  shadow_connect_parameters.pMqttClientId   = AWS_IOT_MQTT_CLIENT_ID;
  shadow_connect_parameters.mqttClientIdLen = strlen(AWS_IOT_MQTT_CLIENT_ID);

  rc = aws_iot_shadow_connect(&mqtt_client, &shadow_connect_parameters);
  if (rc < 0) {
    printf("\r\nShadow Connection failed with aws error: %d\r\n", rc);
    return rc;
  }
  printf("\r\nShadow Connection Success\r\n");

  window_actuator.pKey       = "Window Open";
  window_actuator.pData      = &window_open_state;
  window_actuator.dataLength = sizeof(bool);
  window_actuator.type       = SHADOW_JSON_BOOL;
  window_actuator.cb         = window_actuate_callback;

  temperature_handler.pKey       = "Temperature";
  temperature_handler.pData      = &temperature;
  temperature_handler.dataLength = sizeof(float);
  temperature_handler.type       = SHADOW_JSON_FLOAT;
  temperature_handler.cb         = NULL;

  rc = aws_iot_shadow_register_delta(&mqtt_client, &window_actuator);
  if (rc != SUCCESS) {
    printf("\r\nShadow Register Delta failed with aws error: %d\r\n", rc);
    return rc;
  }
  printf("\r\nShadow Register Delta\r\n");

  temperature = STARTING_ROOM_TEMPERATURE;

  while (1) {
    if (wifi_disconnections_flag == 1) {
      status = sl_net_down(SL_NET_WIFI_CLIENT_INTERFACE);
      if (status != SL_STATUS_OK) {
        printf("Failed to down Wi-Fi client interface up: 0x%x\r\n", status);
        continue;
      }
      do {
        status = sl_net_up(SL_NET_WIFI_CLIENT_INTERFACE, SL_NET_DEFAULT_WIFI_CLIENT_PROFILE_ID);
        if (status != SL_STATUS_OK) {
          printf("\r\nError while connecting to Access point: 0x%lx\r\n", status);
          delay(1000);
          continue;
        } else {
          break;
        }
      } while (1);
      printf("\r\nConnected to Access point\r\n");

      rc = aws_iot_shadow_disconnect(&mqtt_client);
      if (rc < 0) {
        printf("\r\nShadow Disconnection failed with aws error: %d\r\n", rc);
        continue;
      }

      rc = aws_iot_shadow_connect(&mqtt_client, &shadow_connect_parameters);
      if (rc < 0) {
        printf("\r\nShadow Connection failed with aws error: %d\r\n", rc);
        continue;
      }
      printf("\r\nShadow Connection Success\r\n");

      wifi_disconnections_flag = 0;
    }

    rc = aws_iot_shadow_yield(&mqtt_client, 2000);
    if (rc == NETWORK_ATTEMPTING_RECONNECT) {
      continue;
    }
    simulate_room_temperature(&temperature, &window_open_state);
    rc = aws_iot_shadow_init_json_document(json_document_buffer, size_of_json_document_buffer);
    if (rc != SUCCESS) {
      printf("\r\nFailed to initialize JSON buffer with error:0x%x\r\n", rc);
      continue;
    }

    rc = aws_iot_shadow_add_reported(json_document_buffer,
                                     size_of_json_document_buffer,
                                     2,
                                     &temperature_handler,
                                     &window_actuator);
    if (rc != SUCCESS) {
      printf("\r\nFailed to add reported value in JSON buffer with error:0x%x\r\n", rc);
      continue;
    }
    printf("\r\nAdding reported value in JSON buffer success\r\n");

    rc = aws_iot_finalize_json_document(json_document_buffer, size_of_json_document_buffer);
    if (rc != SUCCESS) {
      printf("\r\nFailed to finalize JSON buffer with error:0x%x\r\n", rc);
      continue;
    }
    printf("\r\nJSON finalization buffer Success\r\n");

    printf("\r\nUpdate Shadow: %s\r\n", json_document_buffer);

    rc = aws_iot_shadow_update(&mqtt_client,
                               AWS_IOT_MY_THING_NAME,
                               json_document_buffer,
                               shadow_update_status_callback,
                               NULL,
                               40,
                               true);
    if (rc != SUCCESS) {
      printf("\r\nFailed to update JSON buffer with error:0x%x\r\n", rc);
      continue;
    }
  }
  printf("\r\nSuccess to update JSON buffer\r\n");

  return rc;
}
static void simulate_room_temperature(float *p_room_temperature, bool *p_window_open)
{
  static float delta_change;

  if (*p_room_temperature >= ROOM_TEMPERATURE_UPPER_LIMIT) {
    delta_change = -0.5f;
  } else if (*p_room_temperature <= ROOM_TEMPERATURE_LOWER_LIMIT) {
    delta_change = +0.5f;
  }

  *p_room_temperature += delta_change;
  *p_window_open = false;

  if (*p_room_temperature >= (ROOM_TEMPERATURE_UPPER_LIMIT + ROOM_TEMPERATURE_LOWER_LIMIT) / 2) {
    *p_window_open = true;
  }
}

static void shadow_update_status_callback(const char *p_thing_name,
                                          ShadowActions_t action,
                                          Shadow_Ack_Status_t status,
                                          const char *p_received_json_document,
                                          void *p_context_data)
{
  UNUSED_PARAMETER(p_thing_name);
  UNUSED_PARAMETER(action);
  UNUSED_PARAMETER(p_received_json_document);
  UNUSED_PARAMETER(p_context_data);

  if (SHADOW_ACK_TIMEOUT == status) {
    printf("\r\nUpdate Timed out!!\r\n");
  } else if (SHADOW_ACK_REJECTED == status) {
    printf("\r\nUpdate Rejected!!\r\n");
  } else if (SHADOW_ACK_ACCEPTED == status) {
    printf("\r\nUpdate Accepted!!\r\n");
  }
}

static void window_actuate_callback(const char *p_json_string, uint32_t json_string_data_len, jsonStruct_t *p_context)
{
  UNUSED_PARAMETER(p_json_string);
  UNUSED_PARAMETER(json_string_data_len);

  if (p_context != NULL) {
    printf("Delta - Window state changed to %d", *(bool *)(p_context->pData));
  }
}

/*=============================================================================*/
/**
 * @fn              int8_t *sl_si91x_6byte_dev_address_to_ascii(uint8_t *ascii_mac_address, uint8_t *hex_addr)
 * @brief           Convert given 6-byte hex address to ASCII Mac address.
 * @param[in]       hex_addr              - Hex address input.  
 * @param[out]      asciiMacFormatAddress - Converted ASCII mac address is returned here. 
 * @return          Converted ASCII mac address 
 */

uint8_t *sl_si91x_6byte_dev_address_to_ascii(uint8_t *ascii_mac_address, uint8_t *hex_addr)
{
  int8_t i;        // loop counter
  uint8_t cBufPos; // which char in the ASCII representation

  //byteNum = 5;
  cBufPos = 0;
  for (i = 5; i >= 0; i--) {
    ascii_mac_address[cBufPos++] = hex_to_ascii(hex_addr[i] >> 4);
    ascii_mac_address[cBufPos++] = hex_to_ascii(hex_addr[i]);
    if (i != 0) {
      ascii_mac_address[cBufPos++] = ':';
    }
  }
  return ascii_mac_address;
}

/*=============================================================================*/
/**
 * @fn          int8_t hex_to_ascii(uint8_t hex_num)
 * @brief       Hex to ascii conversion.
 * @param[in]   hex_num - hex number
 * @return      Ascii value for given hex value	
 */

int8_t hex_to_ascii(uint8_t hex_num)
{
  uint8_t ascii = 0;

  switch (hex_num & 0x0F) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      ascii = (hex_num & 0x0F) + '0';
      return ascii;

    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      ascii = (hex_num & 0x0F) - 10 + 'A';
      return ascii;
      //	break;
    default:
      break;
  }

  return ascii;
}
