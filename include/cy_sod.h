/*
 * Copyright 2025, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/**
 * @file cy_sod.h
 *
 * @brief
 * This library provides set of APIs that can be used to detect the onset of the speech in the audio data.
 */
/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef __CY_SOD_H__
#define __CY_SOD_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "cy_sod_errors.h"
#include <stdbool.h>

/**
 * \defgroup group_sod_macros Macros
 * \defgroup group_sod_enums Enumerated types
 * \defgroup group_sod_typedefs Typedefs
 * \defgroup group_sod_structures Structures
 * \defgroup group_sod_functions Functions
 */

/*******************************************************************************
*                      Type Definitions
******************************************************************************/

/**
 * \addtogroup group_sod_typedefs
 * \{
 */

/**
 *  SOD MW handle
 */
typedef void* cy_sod_t;

/** \} group_sod_typedefs */

/*******************************************************************************
 *                      Macros
 ******************************************************************************/
/**
 * \addtogroup group_sod_macros
 * \{
 */

#define CY_MAX_SOD_SENSITIVITY (32767)        /**< maximum SOD sensitivity value */
#define CY_NOMINAL_SOD_SENSITIVITY (16384)    /**< nominal SOD sensitivity value */

/**
 * Supported SOD onset gap sensitivity. This parameter needs to be passed
 * as part of SOD init under cy_sod_config_params::onset_gap_setting_ms
 */
#define CY_SOD_ONSET_GAP_SETTING_1000_MS (1000)     /**< Speech onset gap of 1000ms */
#define CY_SOD_ONSET_GAP_SETTING_500_MS (500)       /**< Speech onset gap of 500ms */
#define CY_SOD_ONSET_GAP_SETTING_400_MS (400)       /**< Speech onset gap of 400ms */
#define CY_SOD_ONSET_GAP_SETTING_300_MS (300)       /**< Speech onset gap of 300ms */
#define CY_SOD_ONSET_GAP_SETTING_200_MS (200)       /**< Speech onset gap of 200ms */
#define CY_SOD_ONSET_GAP_SETTING_100_MS (100)       /**< Speech onset gap of 100ms */
#define CY_SOD_ONSET_GAP_SETTING_0_MS (0)           /**< Speech onset gap of 0ms */

/**
 * SOD algorithm detects speech onset in worse case with this delay. The
 * application needs to look-back the buffer of maximum this delay to get the
 * actual start of the speech.
 */
#define CY_MAX_SOD_HIT_LATE_DELAY_MS (500)

/**
 * SOD algorithm detects speech onset with this time in advance.
 * This may vary depends on the SNR of the signal. Lower the SNR results in
 * early detection due the presence of noise.
 */
#define CY_MAX_SOD_HIT_EARLY_DELAY_MS (350)

/** \} group_sod_macros */
/*******************************************************************************
 *                      Constants
 ******************************************************************************/
/**
 * \addtogroup group_sod_enums
 * \{
 */

/*******************************************************************************
 *                      Enumerations
 ******************************************************************************/
/**
 * SOD detection status
 */
typedef enum
{
    /**
     * Speech detection status is invalid.
     */
    CY_SOD_STATUS_INVALID,

    /**
     * Speech onset is detected.
     * This status will be returned only when the "sod_check_trigger" param is
     * passed as TRUE in cy_sod_process(),
     */
    CY_SOD_STATUS_DETECTED,

    /**
     * In cy_sod_process(), the param sod_check_trigger is set to TRUE, then
     * after processing the feed and if the speech on-set is not detected,
     * then cy_sod_process will return status as  "CY_SOD_STATUS_INPUT_DATA_PROCESSED"
     * to acknowledge that data is consumed by the SOD MW.
     *
     * In cy_sod_process(), the param sod_check_trigger is set to FALSE, then
     * cy_sod_process will always return "CY_SOD_STATUS_INPUT_DATA_PROCESSED".
     * It helps the SOD to maintain the status in the buffer without any
     * discontinuity in the input feed.
     */
    CY_SOD_STATUS_INPUT_DATA_PROCESSED,

    /**
     * Speech detection status is maximum (invalid).
     */
    CY_SOD_STATUS_MAX

} cy_sod_status_t;

/** \} group_sod_enums */

/**
 * \addtogroup group_sod_structures
 * \{
 */

/*******************************************************************************
 *                      Structures
 ******************************************************************************/

/**
 * SOD configuration parameters.
 */
typedef struct
{
    /**
     * Sensitivity, The detection sensitivity (0- 32767)
     * 0 = least sensitive
     * 32767 (MAX_SOD_SENSITIVITY) = most sensitive
     * 16384 = nominal sensitive and suitable (recommended) for Wakeword detection.
     */
    int sensitivity;

    /**
     * Onset gap settings. Generally, a talker will pause momentarily before
     * addressing a person, or in this case, a device.  The pause is
     * approximately in the range of 200-500ms in conversational speech.
     *
     * Allowed gap settings are:
     * CY_SOD_ONSET_GAP_SETTING_1000_MS,
     * CY_SOD_ONSET_GAP_SETTING_500_MS,
     * CY_SOD_ONSET_GAP_SETTING_400_MS,
     * CY_SOD_ONSET_GAP_SETTING_300_MS
     * CY_SOD_ONSET_GAP_SETTING_200_MS
     * CY_SOD_ONSET_GAP_SETTING_100_MS
     * CY_SOD_ONSET_GAP_SETTING_0_MS
     *
     * For wake-word detection, better behavior is seen with a
     * CY_SOD_ONSET_GAP_SETTING_400_MS gap setting.
     */
    int onset_gap_setting_ms;

} cy_sod_config_params;

/** \} group_sod_structures */

/**
 * \addtogroup group_sod_functions
 * \{
 */

/*******************************************************************************
 *                      Function Declarations
 ******************************************************************************/
/**
 * Initializes the SOD MW.
 *
 * Supported only one instance of SOD. (Multi-instance is not supported)
 *
 * @param[in]  config_params        Configuration parameters
 *
 * @param[out]  handle              SOD handle
 *
 * @return    CY_RSLT_SUCCESS on success; an error code on failure.
 */
cy_rslt_t cy_sod_init(cy_sod_config_params *config_params, cy_sod_t *handle);

/**
 * Process the audio data and detect the speech onset on the data.
 *
 * @param[in]  handle               SOD handle
 *
 * @param[in]  sod_check_trigger    If set to true then SOD middleware will process the audio data and return the
 *                                  appropriate status (cy_sod_status_t). If set to false then SOD middleware will use the audio data for internal
 *                                  processing and return the status cy_sod_status_t as "CY_SOD_STATUS_NOT_REQUESTED_DATA_PROCESSED"
 *
 * @param[in] data                  Pointer to audio data. Audio data must be
 *                                  mono channel format (160 samples and each
 *                                  sample of 2 bytes, totally 320bytes).
 *                                  - Application has to provide complete audio
 *                                  frame data frame worth of 320 bytes
 *                                  - SOD MW will completely process data in
 *                                  the API itself. Application can reuse the
 *                                  buffer once the API returns.
 *                                  - Data is always assumed at the sample
 *                                  rate of 16KHz.
 *
 * @param[in] sod_status            status of the SOD detection.
 *
 * @return    CY_RSLT_SUCCESS on success; an error code on failure.
 */
cy_rslt_t cy_sod_process(
        cy_sod_t handle,
        bool sod_check_trigger,
        int16_t *data,
        cy_sod_status_t *sod_status);

/**
 * Reset the SOD MW. This will reset the SOD MW context and make it ready as
 * fresh SOD start detection. This API will be useful when there is
 * discontinuity in the data feed and the application wants
 * to restart of SOD.
 *
 * @param[in]  handle                  Handle to SOD MW
 *
 * @return    CY_RSLT_SUCCESS on success; an error code on failure.
 */
cy_rslt_t cy_sod_reset(cy_sod_t handle);

/**
 * De-Initializes the SOD MW.
 *
 * @param[in,out]  handle              SOD handle.
 *                                     On successful deinit the handle memory
 *                                     would be set to NULL.
 *
 * @return    CY_RSLT_SUCCESS on success; an error code on failure.
 */
cy_rslt_t cy_sod_deinit(cy_sod_t *handle);

/** \} group_sod_functions */

#ifdef __cplusplus
}
#endif

#endif /*__CY_SOD_H__ */
