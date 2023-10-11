/*
FreeRTOS Kernel V10.2.0
Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 http://aws.amazon.com/freertos
 http://www.FreeRTOS.org
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
*
* These definitions should be adjusted for your particular hardware and
* application requirements.
*
* THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
* FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
* http://www.freertos.org/a00110.html
*
* The bottom of this file contains some constants specific to running the UDP
* stack in this demo.  Constants specific to FreeRTOS+TCP itself (rather than
* the demo) are contained in FreeRTOSIPConfig.h.
*----------------------------------------------------------*/

#warning "FreeRTOSConfig.h is not configured. Please configure the defines here.\n"

// #include "si91x_device.h"

// extern uint32_t SystemCoreClock;
// /* FIX ME: Uncomment and set to the specifications for your MCU. */
// #define configCPU_CLOCK_HZ SystemCoreClock

// #define configUSE_DAEMON_TASK_STARTUP_HOOK      0
// #define configENABLE_BACKWARD_COMPATIBILITY     1
// #define configUSE_PREEMPTION                    1
// #define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
// #define configMAX_PRIORITIES                    (56)
// #define configTICK_RATE_HZ                      ((TickType_t)1000)
// #define configMINIMAL_STACK_SIZE                ((unsigned short)256)
// #define configTOTAL_HEAP_SIZE                   ((size_t)(50 * 1024))
// #define configMAX_TASK_NAME_LEN                 (15)
// #define configUSE_TRACE_FACILITY                1
// #define configUSE_16_BIT_TICKS                  0
// #define configIDLE_SHOULD_YIELD                 1
// #define configUSE_CO_ROUTINES                   0
// #define configUSE_MUTEXES                       1
// #define configUSE_RECURSIVE_MUTEXES             1
// #define configQUEUE_REGISTRY_SIZE               8
// #define configUSE_APPLICATION_TASK_TAG          0
// #define configUSE_COUNTING_SEMAPHORES           1
// #define configUSE_ALTERNATIVE_API               0
// #define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5 /* FreeRTOS+FAT requires 2 pointers if a CWD is supported. */
// #define configRECORD_STACK_HIGH_ADDRESS         1

// /* Hook function related definitions. */
// #define configUSE_TICK_HOOK            0
// #define configUSE_IDLE_HOOK            0
// #define configUSE_MALLOC_FAILED_HOOK   0
// #define configCHECK_FOR_STACK_OVERFLOW 0 /* Not applicable to the Win32 port. */

// /* Software timer related definitions. */
// #define configUSE_TIMERS             1
// #define configTIMER_TASK_PRIORITY    (configMAX_PRIORITIES - 1)
// #define configTIMER_QUEUE_LENGTH     5
// #define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE * 2)

// /* Event group related definitions. */
// #define configUSE_EVENT_GROUPS 1

// #define configUSE_TIME_SLICING 1

// /* Run time stats gathering definitions. */
// /* FIX ME: Uncomment if you plan to use Tracealyzer.*/
// unsigned long ulGetRunTimeCounterValue(void);
// void vConfigureTimerForRunTimeStats(void);
// #define configGENERATE_RUN_TIME_STATS 0
// //#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 	vConfigureTimerForRunTimeStats()
// //#define portGET_RUN_TIME_COUNTER_VALUE()         	ulGetRunTimeCounterValue()

// /* Co-routine definitions. */
// #define configUSE_CO_ROUTINES           0
// #define configMAX_CO_ROUTINE_PRIORITIES (2)

// /* Currently the TCP/IP stack is using dynamic allocation, and the MQTT task is
//  * using static allocation. */
// #define configSUPPORT_DYNAMIC_ALLOCATION 1
// #define configSUPPORT_STATIC_ALLOCATION  0

// /* Set the following definitions to 1 to include the API function, or zero
//  * to exclude the API function. */
// #define INCLUDE_vTaskPrioritySet            1
// #define INCLUDE_uxTaskPriorityGet           1
// #define INCLUDE_vTaskDelete                 1
// #define INCLUDE_vTaskCleanUpResources       1
// #define INCLUDE_vTaskSuspend                1
// #define INCLUDE_vTaskDelayUntil             1
// #define INCLUDE_vTaskDelay                  1
// #define INCLUDE_uxTaskGetStackHighWaterMark 1
// #define INCLUDE_xTaskGetSchedulerState      1
// #define INCLUDE_xTimerGetTimerTaskHandle    0
// #define INCLUDE_xTaskGetIdleTaskHandle      0
// #define INCLUDE_xQueueGetMutexHolder        1
// #define INCLUDE_eTaskGetState               1
// #define INCLUDE_xEventGroupSetBitsFromISR   1
// #define INCLUDE_xTimerPendFunctionCall      1
// #define INCLUDE_xTaskGetCurrentTaskHandle   1
// #define INCLUDE_xTaskAbortDelay             1

// /* Cortex-M specific definitions. */
// #ifdef __NVIC_PRIO_BITS
// #undef __NVIC_PRIO_BITS
// #endif
// #define configPRIO_BITS 6 /* 6 priority levels. */

/* This demo makes use of one or more example stats formatting functions.  These
 * format the raw data provided by the uxTaskGetSystemState() function in to human
 * readable ASCII form.  See the notes in the implementation of vTaskList() within
 * FreeRTOS/Source/tasks.c for limitations.  configUSE_STATS_FORMATTING_FUNCTIONS
 * is set to 2 so the formatting functions are included without the stdio.h being
 * included in tasks.c.  That is because this project defines its own sprintf()
 * functions. */
// #define configUSE_STATS_FORMATTING_FUNCTIONS 0

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
// #define vPortSVCHandler    SVC_Handler
// #define xPortPendSVHandler PendSV_Handler
// #define vHardFault_Handler HardFault_Handler

// /* Ensure Cortex-M port compatibility. */
// #define SysTick_Handler xPortSysTickHandler
// //#define xPortSysTickHandler 						SysTick_Handler

// /* Assert call defined for debug builds. */
// void vAssertCalled(const char *pcFile, uint32_t ulLine);

// #define configASSERT(x)       \
//   if ((x) == 0) {             \
//     taskDISABLE_INTERRUPTS(); \
//     for (;;)                  \
//       ;                       \
//   }

// /* The function that implements FreeRTOS printf style output, and the macro
//  * that maps the configPRINTF() macros to that function. */
// extern void vLoggingPrintf(const char *pcFormat, ...);
// #define configPRINTF(X) vLoggingPrintf X

// /* Non-format version thread-safe print */
// extern void vLoggingPrint(const char *pcMessage);
// #define configPRINT(X) vLoggingPrint(X)

// /* Map the logging task's printf to the board specific output function. */
// #include <stdio.h>
// #define configPRINT_STRING(X) printf(X); /* FIX ME: Change to your devices console print acceptance function. */
// /* Sets the length of the buffers into which logging messages are written - so
//  * also defines the maximum length of each log message. */
// #define configLOGGING_MAX_MESSAGE_LENGTH 100

// /* Set to 1 to prepend each log message with a message number, the task name,
//  * and a time stamp. */
// #define configLOGGING_INCLUDE_TIME_AND_TASK_NAME 1

// /* The priority at which the tick interrupt runs.  This should probably be kept at 1. */
// //#define configKERNEL_INTERRUPT_PRIORITY           1

// /* The lowest interrupt priority that can be used in a call to a "set priority"
// function. */
// #define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 0x3f

// /* The highest interrupt priority that can be used by any interrupt service
// routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
// INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
// PRIORITY THAN THIS! (higher priorities are lower numeric values. */
// #define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

// /* Interrupt priorities used by the kernel port layer itself.  These are generic
// to all Cortex-M ports, and do not rely on any particular library functions. */
// #define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
// /* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
// See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */

// #define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

// // <h> Thread Local Storage Settings
// //  <o>Thread local storage pointers
// //  <i> Thread local storage (or TLS) allows the application writer to store
// //  <i> values inside a task's control block, making the value specific to
// //  <i> (local to) the task itself.
// //  <i> Default: 0
// #define configNUM_USER_THREAD_LOCAL_STORAGE_POINTERS 0
// // </h>

// /* The platform FreeRTOS is running on. */
// #define configPLATFORM_NAME "Si917_SoC"

// #endif /* FREERTOS_CONFIG_H */
