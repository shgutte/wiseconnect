/*******************************************************************************
 * @file  sl_si91x_psa_ecdh.h
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

#ifndef SL_SI91X_PSA_ECDH_H
#define SL_SI91X_PSA_ECDH_H

#include "psa/crypto.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define ECC_P256_LEN 32
#define ECC_P192_LEN 24

/// ECC Curve
/// By default cure P 256 is selected
#define ECC_SEPR1_256
//#define ECC_SEPR1_192         /* Enable to select curve P 192 */
//#define ECC_OTHER_CURVE       /* This will enable software fallback as only p192 and p256 curves point multiplication is supported in hardware */

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

psa_status_t sli_si91x_psa_export_public_key_ecdh(const psa_key_attributes_t *attributes,
                                                  const uint8_t *key_buffer,
                                                  size_t key_buffer_size,
                                                  uint8_t *data,
                                                  size_t data_size,
                                                  size_t *data_length);

psa_status_t sli_si91x_psa_ecdh_key_agreement(psa_algorithm_t alg,
                                              const psa_key_attributes_t *attributes,
                                              uint8_t *private_key,
                                              uint32_t private_key_len,
                                              uint8_t *peer_key,
                                              uint32_t peer_key_length,
                                              uint8_t *shared_secret,
                                              uint32_t shared_secret_size,
                                              uint32_t shared_secret_length);

#endif /* SLI_SI91X_PSA_ECDH_H */
