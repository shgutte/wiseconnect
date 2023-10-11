/***************************************************************************/ /**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_status.h"
#include "sl_wifi_types.h"
#include "sl_net.h"
#include "stddef.h"

// Convert a string IP address to a 32-bit integer
sl_status_t sl_net_inet_addr(const char *addr, uint32_t *value)
{
  uint8_t ip_bytes[4] = { 0 };
  int i, j, digits;

  if ((NULL == addr) || (NULL == value)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  i      = 0;
  j      = 0;
  digits = 0;

  // Iterate through the characters in the IP address string
  for (i = 0, j = 0; 0 != addr[i]; i++) {
    if ('.' == addr[i]) {
      ++j;
      digits = 0;
      continue;
    }

    // Check if the character is a digit (0-9)
    if ((addr[i] < '0') || (addr[i] > '9')) {
      return SL_STATUS_INVALID_PARAMETER;
    }

    // Convert character to numeric value and update IP bytes
    ip_bytes[j] = (ip_bytes[j] * 10) + (uint8_t)(addr[i] - '0');

    digits++;
    if (digits > 3) {
      return SL_STATUS_INVALID_PARAMETER;
    }
  }

  // Ensure that there are exactly three '.' separators in the IP address
  if (j != 3) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Calculate the 32-bit integer value of the IP address
  *value = (uint32_t)ip_bytes[0];
  *value |= (uint32_t)(ip_bytes[1] << 8);
  *value |= (uint32_t)(ip_bytes[2] << 16);
  *value |= (uint32_t)(ip_bytes[3] << 24);

  return SL_STATUS_OK;
}

sl_status_t sl_si91x_host_get_credentials(sl_wifi_credential_id_t id, uint8_t type, sl_wifi_credential_t *cred)
{
  UNUSED_PARAMETER(type);
  sl_net_credential_type_t actual_type;
  uint32_t credential_length = sizeof(sl_wifi_credential_t) - offsetof(sl_wifi_credential_t, pmk);
  sl_status_t status         = sl_net_get_credential(id, &actual_type, &cred->pmk, &credential_length);
  VERIFY_STATUS_AND_RETURN(status);

  // Map the network credential type to a simplified type
  switch (actual_type) {
    case SL_NET_WIFI_PSK:
      // Set the credential type to Pre-Shared Key (PSK)
      cred->type = SL_WIFI_PSK_CREDENTIAL;
      break;
    case SL_NET_WIFI_PMK:
      // Set the credential type to Pairwise Master Key (PMK)
      cred->type = SL_WIFI_PMK_CREDENTIAL;
      break;
    case SL_NET_WIFI_WEP:
      // Set the credential type to Wired Equivalent Privacy (WEP)
      cred->type = SL_WIFI_WEP_CREDENTIAL;
      break;
    case SL_NET_EAP_CLIENT_CREDENTIAL:
      // Set the credential type to Extensible Authentication Protocol (EAP)
      cred->type = SL_WIFI_EAP_CREDENTIAL;
      break;
    default:
      return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}
