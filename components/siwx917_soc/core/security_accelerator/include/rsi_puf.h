/*******************************************************************************
* @file  rsi_puf.h
* @brief 
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
/*************************************************************************
 *
 */
#ifndef RSI_PUF_H
#define RSI_PUF_H

#include "rsi_chip.h"

#define RSI_SUCCESS 0
//! flag bit to set IPV6
#define KEY_CODE_SIZE              11 /*Key code size*/
#define KEY_CODE_SIZE_BYTES        44 /*Key code size*/
#define MAX_KEY_SIZE_BYTES         32 /*Key size*/
#define AES_CMDS_SIZE_WTH_OUT_DATA 67 /* 1 + 32 + 32 + 2*/

#define MAX_DATA_SIZE_BYTES 1400 /*Data size*/

#define AES_ECB_MODE      0
#define AES_CBC_MODE      1
#define PUF_AS_KEY_SOURCE 0
#define AES_AS_KEY_SOURCE 1
#define PUF_KEY_SIZE_128  0
#define PUF_KEY_SIZE_256  1
#define PUF_IV_SIZE_128   0
#define PUF_IV_SIZE_256   1

/******************************************************
 * *                    Constants
 * ******************************************************/
/******************************************************
 * *                   Enumerations
 * ******************************************************/
/******************************************************
 * *                 Type Definitions
 * ******************************************************/

//! PUF Request Frames Structures
typedef struct rsi_req_puf_set_key_s {
  //! 2 bytes, socket that was closed
  uint8_t key_index;

  uint8_t key_size;
  uint8_t key[32];
} rsi_req_puf_set_key_t;

typedef struct rsi_req_puf_get_key_s {
  uint8_t key_code[44];
} rsi_req_puf_get_key_t;

typedef struct rsi_req_puf_load_key_s {
  uint8_t key_code[44];
} rsi_req_puf_load_key_t;

typedef struct rsi_req_aes_encrypt_s {
  uint8_t mode;
  uint8_t key[32];
  uint8_t iv[32];
  uint8_t data_size[2];
  uint8_t data[1400];
} rsi_req_aes_encrypt_t;

typedef struct rsi_req_aes_decrypt_s {
  uint8_t mode;
  uint8_t key[32];
  uint8_t iv[32];
  uint8_t data_size[2];
  uint8_t data[1400];
} rsi_req_aes_decrypt_t;

typedef struct rsi_req_aes_mac_s {
  uint8_t mode;
  uint8_t key[32];
  uint8_t iv[32];
  uint8_t data_size[2];
  uint8_t data[1400];
} rsi_req_aes_mac_t;

typedef struct rsi_req_puf_intr_key_s {
  uint8_t key_index;
  uint8_t key_size;
} rsi_req_puf_intr_key_t;

/******************************************************
 * *                    Structures
 * ******************************************************/
/******************************************************
 * *                 Global Variables
 * ******************************************************/
/******************************************************
 * *               Function Declarations
 * ******************************************************/
int32_t rsi_puf_enroll_req(void);
int32_t rsi_puf_enroll_disable_req(void);
int32_t rsi_puf_start_req(void);
int32_t rsi_puf_set_key_req(uint8_t key_index,
                            uint16_t key_size,
                            uint8_t *key_ptr,
                            uint8_t *set_key_resp,
                            uint16_t length);
int32_t rsi_puf_set_key_disable_req(void);
int32_t rsi_puf_get_key_req(uint8_t *keycode_ptr, uint8_t *get_key_resp, uint16_t length);
int32_t rsi_puf_get_key_disable_req(void);
int32_t rsi_puf_load_key_req(uint8_t *keycode_ptr);
int32_t rsi_puf_aes_encrypt_req(uint8_t mode,
                                uint8_t key_source,
                                uint16_t key_size,
                                uint8_t *key_ptr,
                                uint16_t data_size,
                                uint8_t *data_ptr,
                                uint16_t iv_size,
                                uint8_t *iv_ptr,
                                uint8_t *aes_encry_resp,
                                uint16_t length);
int32_t rsi_puf_aes_decrypt_req(uint8_t mode,
                                uint8_t key_source,
                                uint16_t key_size,
                                uint8_t *key_ptr,
                                uint16_t data_size,
                                uint8_t *data_ptr,
                                uint16_t iv_size,
                                uint8_t *iv_ptr,
                                uint8_t *aes_decry_resp,
                                uint16_t length);
int32_t rsi_puf_aes_mac_req(uint8_t key_source,
                            uint16_t key_size,
                            uint8_t *key_ptr,
                            uint16_t data_size,
                            uint8_t *data_ptr,
                            uint16_t iv_size,
                            uint8_t *iv_ptr,
                            uint8_t *aes_mac_resp,
                            uint16_t length);
int32_t rsi_puf_intr_key_req(uint8_t key_index, uint8_t key_size, uint8_t *set_key_resp, uint16_t length);
#endif
