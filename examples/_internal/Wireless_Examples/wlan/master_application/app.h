/***************************************************************************/ /**
 * @file app.h
 * @brief Top level application functions
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

#ifndef APP_H
#define APP_H

#include "sl_slist.h"
#include "sl_status.h"
/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init();

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);
typedef enum {
  IDLE,                 //<  Initial state of application.
  MODULE_INIT,          //<< After successful sl_net init.
  WLAN_CONNECTING,      //<< When connect has been called, but still waiting for the reply
  WLAN_CONNECTED,       //<< When module is successfully connected to an AP.
  WLAN_DICONNECTED,     //<< App arrives to this state when we receive join fail callback from TA
  SOCKET_DATA_TRANSFER, //<< When app is doing socket data transfer.
  TERMINATED,           //<< When application reached terminal state.
  UNDEFINED,            //<  Application is in corrupt/undefined state.
} master_application_state_t;

typedef enum {
  INIT,
  CONNECT,                //< When we call sl_connect
  DISCONNECT,             //< Event of join failure
  INITIATE_DATA_TRANSFER, //< This event is handled when we initiated socket data transfer.
  MQTT,                   //< This event is handled when we initiated MQTT operations.
  MAX,
} master_application_event_t;

typedef struct {
  master_application_state_t state;
} master_app_state_machine_t;

typedef sl_status_t (*state_transition_callback)(master_application_state_t last_state,
                                                 master_application_state_t new_state,
                                                 master_application_event_t event_occurred);

typedef struct {
  master_application_state_t current_state; //<< State on which event occurred
  master_application_state_t next_state;    //<< State to which the state machine would to move to

  master_application_event_t event_occured; //< Event which occurred.

  state_transition_callback state_change_callback;
} master_application_trasition;

#endif // APP_H
