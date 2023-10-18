/*******************************************************************************
* @file  doxygen_template.h
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

/*!@defgroup BLUETOOTH APIs
 *
 *  This section provides a reference to the Bluetooth Low Energy (BLE) API including functions, data types, and events.
 *
 */

/** @defgroup BT-FUNCTIONS Functions
 *  @ingroup BLUETOOTH
 *
 *  This section provides a reference to Bluetooth Low Energy (BLE) API functions:
 *
 *  - @ref BT-BLE
 *    functions to initialize and configure BLE features.
 *
 *  - @ref BT-LOW-ENERGY
 *    functions providing BLE connectivity and protocol functions.
 *
 */

/** @defgroup BT-BLE Common
 *  @ingroup BT-FUNCTIONS
 *
 */

/** @defgroup BT-LOW-ENERGY BLE
 *  @ingroup BT-FUNCTIONS
 *
 *  BLE functions provide all the connectivity and protocol features of BLE:
 *  - @ref BT-LOW-ENERGY1
 *  functions to implement the Generic Access Profile (GAP) protocol.
 *  - @ref BT-LOW-ENERGY2
 *  functions to implement the Generic Attribute Profile (GATT) protocol.
 *  - @ref BT-LOW-ENERGY6
 *  functions to access Bluetooth Low Energy (BLE) test mode features.
 *  - @ref BT-LOW-ENERGY7
 *  section to refer to functions to register Bluetooth Low Energy (BLE) API callbacks.
 *  - @ref BT-LOW-ENERGY8
 *  for handling Bluetooth Low Energy (BLE) API callbacks.
 *
 */

/** @defgroup BT-LOW-ENERGY1 GAP
 *  @ingroup BT-LOW-ENERGY
 *
 */

/** @defgroup BT-LOW-ENERGY2 GATT
 *  @ingroup BT-LOW-ENERGY
 *
 *  Generic Attribute Profile (GATT) functions provide access to the BLE GATT protocol. The response payload for all the aysnchronous APIs will be indicated
 *  to the application through the corresponding callback functions as described in the following sections.
 *  The response payload structure is described in the _Callback Declarations_ section. This section provides a reference to GATT functions:
 *
 *  - @ref BT-LOW-ENERGY3
 *  functions to implement a synchronous Generic Attribute Profile (GATT) client.
 *  - @ref BT-LOW-ENERGY4
 *  functions to implement an asynchronous Generic Attribute Profile (GATT) client.
 *  - @ref BT-LOW-ENERGY5
 *  functions to implement a Generic Attribute Profile (GATT) server.
 *
 */

/** @defgroup BT-LOW-ENERGY3 Synchronous Client
 *  @ingroup BT-LOW-ENERGY2
 *
 */

/** @defgroup BT-LOW-ENERGY4 Asynchronous Client
 *  @ingroup BT-LOW-ENERGY2
 *
 */

/** @defgroup BT-LOW-ENERGY5 Server
 *  @ingroup BT-LOW-ENERGY2
 *
 */

/** @defgroup BT-LOW-ENERGY6  Test Mode
 *  @ingroup BT-LOW-ENERGY
 *
 */

/** @defgroup BT-LOW-ENERGY7  Register Callbacks
 *  @ingroup BT-LOW-ENERGY
 *
 */

/** @defgroup BT-LOW-ENERGY8  Callbacks Declarations
 *  @ingroup BT-LOW-ENERGY
 *
 */

/*! @defgroup BT_BLE_TYPES Data Structures
 *  @ingroup BLUETOOTH
 *
 *   This section provides a reference to Bluetooth Low Energy (BLE) API data types.
 *
 */

/*! @defgroup BT_BLE_EVENT_TYPES Event Types
 *  @ingroup BLUETOOTH
 *
 *   This section provides a reference to Bluetooth Low Energy (BLE) API events.
 *
 */
