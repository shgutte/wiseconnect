# POWER MANAGER M4 WIRELESS

## Introduction
- This application demonstrates the power manager service APIs, state transitions, sleep-wakeup (with RAM retention) and sleep-wakeup (without RAM retention).
- According to the macros configured in power_manager_example.h file, it executes the state transition and sleep-wakeup with RAM retention on button press, sleep-wakeup without RAM retention using second trigger as wakeup source.
- State transitions demonstrated are as follows: PS4 -> PS2, PS2 -> PS4, PS4 -> PS4 Sleep -> PS4, PS4 -> PS3, PS3 -> PS3 Sleep -> PS3, PS3 -> PS2, PS2 -> PS2 Sleep -> PS2, PS2 -> PS1 -> PS2, PS2 -> PS3, PS3 -> PS2. It switches the state at the time of button press.
- Sleep - wakeup without RAM retention is demonstrated as follows: PS4 -> PS0 -> wakeup -> restart the controller.

## About Example Code
- At the time of initialization, a thread is created and the application_start() function is called along the thread.
- All the activities are handled in the application_start() function.
- Firstly wifi is initialized, M4-TA secure handshake is established to send commands to TA, TA is switched to STANDBY_WITH_RAM_RETENTION mode.
- Power Manager service is initialized, the processor is switched to PS4 state and the clock is 100 MHz (Power Save) using \ref sl_si91x_power_manager_init.
- All the possible events are ored and passed to the \ref sl_si91x_power_manager_subscribe_ps_transition_event along with the callback function address.
- RAM retention is enabled and configured using \ref sl_si91x_power_manager_configure_ram_retention.

- If SWITCH_TO_PS0 is enabled, m4 switches the state and goes to PS0, and upon wakeup restarts the controller. 
  - The TA is switched to STANDBY_POWER_SAVE which means, sleep without retention.
  - Wakeup Source is selected as the calendar second trigger. The calendar peripheral is initialized before setting it as a wakeup source, the RC clock is selected using \ref sl_si91x_calendar_set_configuration, the calendar is initialized using \ref sl_si91x_calendar_init, the second trigger is selected as wakeup source using \ref sl_si91x_power_manager_set_wakeup_sources, Now callback is registered for second trigger (it enables the trigger also) using \ref sl_si91x_calendar_register_sec_trigger_callback.
  - RAM retention is enabled and configured using \ref sl_si91x_power_manager_configure_ram_retention.
  - It goes to PS0 state using \ref sl_si91x_power_manager_add_ps_requirement. After waking up using the calendar one-second trigger, it restarts the controller.

- If SWITCH_TO_PS0 is disabled, upon button press it changes the state and performs sleep-wakeup operations.
  - PS4 -> PS2: Unwanted peripherals are powered off using \ref sl_si91x_power_manager_remove_peripheral_requirement, PS2 state requirement is added using \ref sl_si91x_power_manager_add_ps_requirement.
  - PS2 -> PS4: To transmit to PS2, remove the requirement for the PS2 state using \ref sl_si91x_power_manager_remove_ps_requirement and add a requirement for the PS4 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS4.
  - PS4 -> PS4 Sleep -> PS4: 
    - Wakeup Source is selected as the calendar second trigger. The calendar peripheral is initialized before setting it as a wakeup source, the RC clock is selected using \ref sl_si91x_calendar_set_configuration, the calendar is initialized using \ref sl_si91x_calendar_init, the second trigger is selected as wakeup source using \ref sl_si91x_power_manager_set_wakeup_sources, Now callback is registered for second trigger (it enables the trigger also) using \ref sl_si91x_calendar_register_sec_trigger_callback.
    - Now soc goes to sleep using \ref sl_si91x_power_manager_sleep. Upon wake-up, the calendar is stopped using \ref sl_si91x_calendar_rtc_stop and callback is unregistered using \ref sl_si91x_calendar_unregister_sec_trigger_callback.

  - PS4 -> PS3: To transmit to PS3, remove the requirement for PS4 state using \ref sl_si91x_power_manager_remove_ps_requirement and add the requirement for PS3 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS3.
  - PS3 -> PS3 Sleep -> PS3: 
    - Wakeup Source is selected as the calendar second trigger. The calendar peripheral is initialized before setting it as a wakeup source, the RC clock is selected using \ref sl_si91x_calendar_set_configuration, the calendar is initialized using \ref sl_si91x_calendar_init, the second trigger is selected as wakeup source using \ref sl_si91x_power_manager_set_wakeup_sources, Now callback is registered for second trigger (it enables the trigger also) using \ref sl_si91x_calendar_register_sec_trigger_callback.
    - Now soc goes to sleep using \ref sl_si91x_power_manager_sleep. Upon wake-up, the calendar is stopped using \ref sl_si91x_calendar_rtc_stop and callback is unregistered using \ref sl_si91x_calendar_unregister_sec_trigger_callback.

  - PS3 -> PS2: Unwanted peripherals are powered off using \ref sl_si91x_power_manager_remove_peripheral_requirement. To transmit to PS2, remove the requirement for PS3 state using \ref sl_si91x_power_manager_remove_ps_requirement and add the requirement for PS3 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS3.
  - PS3 -> PS2: Unwanted peripherals are powered off using \ref sl_si91x_power_manager_remove_peripheral_requirement. To transmit to PS2, remove the requirement for PS3 state using \ref sl_si91x_power_manager_remove_ps_requirement and add the requirement for PS3 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS3.
  - PS2 -> PS2 Sleep -> PS2: 
    - Wakeup Source is selected as the calendar second trigger. The calendar peripheral is initialized before setting it as a wakeup source, the RC clock is selected using \ref sl_si91x_calendar_set_configuration, the calendar is initialized using \ref sl_si91x_calendar_init, the second trigger is selected as wakeup source using \ref sl_si91x_power_manager_set_wakeup_sources, Now callback is registered for second trigger (it enables the trigger also) using \ref sl_si91x_calendar_register_sec_trigger_callback.
    - Now soc goes to sleep using \ref sl_si91x_power_manager_sleep.
    - Upon wakeup, the calendar is stopped using \ref sl_si91x_calendar_rtc_stop and the callback is unregistered using \ref sl_si91x_calendar_unregister_sec_trigger_callback.
  - PS2 -> PS1 -> PS2:
    - Wakeup Source is selected as ULP Timer. ULP Timer peripheral is initialized before setting it as a wakeup source. It is initialized using \ref sl_si91x_ulp_timer_init, set the match value for 2 seconds and configured the ULP Timer using \ref sl_si91x_ulp_timer_set_configuration. Now callback is registered for the second trigger (it enables the trigger also) using \ref sl_si91x_ulp_timer_register_timeout_callback. ULPSS-based wakeup source is selected using \ref sl_si91x_power_manager_set_wakeup_sources.
    - Now the timer is started using \ref sl_si91x_ulp_timer_start.The requirement is added for PS1 state using \ref sl_si91x_power_manager_add_ps_requirement.
    - Upon wakeup timer is stopped using \ref sl_si91x_ulp_timer_stop and callback is unregistered using \ref sl_si91x_ulp_timer_unregister_timeout_callback and the wakeup source is cleared using \ref sl_si91x_power_manager_set_wakeup_sources.

  - PS2 -> PS3: To transmit to PS3, remove the requirement for the PS2 state using \ref sl_si91x_power_manager_remove_ps_requirement and add the requirement for the PS3 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS3.
  - PS3 -> PS4: To transmit to PS3, remove the requirement for PS3 state using \ref sl_si91x_power_manager_remove_ps_requirement and add the requirement for PS4 state using \ref sl_si91x_power_manager_add_ps_requirement switches the power state to PS4.

## Running Example Code

- To use this application following Hardware, Software and Project Setup is required.

### Hardware Requirements

- Windows PC
- Silicon Labs Si917 Evaluation Kit [WPK/WSTK + BRD4338A]

![Figure: Introduction](resources/readme/image501a.png)

### Software Requirements

- Si91x SDK
- Embedded Development Environment
  - For Silicon Labs Si91x, use the latest version of Simplicity Studio (refer **"Download and Install Simplicity Studio"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html**)

## Project Setup

- **Silicon Labs Si91x** refer **"Download SDK"** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio.

## Loading Application on Simplicity Studio

1. With the product Si917 selected, navigate to the example projects by clicking on Example Projects & Demos in Simplicity Studio and click on to SL_POWER_MANAGER Example application as shown below.

![Figure: Selecting Example project](resources/readme/image501b.png)

- Configure the following macros in power_manager_example.h file and update/modify the following macros if required.

```C
#define SWITCH_TO_PS0 DISABLE // Enable this macro to configure soc state as PS0
```

## Build

1. Compile the application in Simplicity Studio using the build icon.

![Figure: Build run and Debug](resources/readme/image501c.png)

## Device Programming

- To program the device, refer **Burn** M4 Binary** section in **getting-started-with-siwx917-soc** guide at **release_package/docs/index.html** to work with Si91x and Simplicity Studio.

## Executing the Application

1. Enable any of the macros whose functionality needs to be tested.
2. Compile and run the application.

## Expected Results

- By default it initializes the wifi and switches TA to standby with RAM retention mode, power manager service is initialized and callback is subscribed.
- If SWITCH_TO_PS0 is enabled, it goes to PS0 state i.e., sleep without retention and upon wakeup restarts the controller. It can be analyzed using serial console prints as well as monitor current using Energy Profiler in Simplicity Studio.
- If SWITCH_TO_PS0 is disabled, with the button press, it switches the state and performs sleep-wakeup. It can be analyzed using serial console prints as well as monitor current using Energy Profiler in Simplicity Studio.
