/***************************************************************************/ /**
 * @file model_profiler.h
 * @brief TFLM model profiler header.
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
#ifndef MODEL_PROFILER_H
#define MODEL_PROFILER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Prototypes
/***************************************************************************/ /**
 * Model Profiler initialization function. It fetches the model being profiled,
 * initialize it and allocates the required tensor arena for the run
 * @param none
 * @return bool
 ******************************************************************************/
bool model_profiler_init(void);

/***************************************************************************/ /**
 * Process action runs only once for single run of the model being profiled
 * @param none
 * @return none
 ******************************************************************************/
void model_profiler_process_action(void);

#ifdef __cplusplus
}
#endif

#endif // MODEL_PROFILER_H
