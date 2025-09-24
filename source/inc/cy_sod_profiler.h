/******************************************************************************
* File Name: cy_sod_profiler.h
*
* Description: Speech onset detection module header file with APIs and data structures.
*
* Related Document: See README.md
*
*******************************************************************************
* (c) 2021, Infineon Technologies Company. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Infineon Technologies Company (Infineon) or one of its
* subsidiaries and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Infineon hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Infineon's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Infineon.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Infineon
* reserves the right to make changes to the Software without notice. Infineon
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Infineon does
* not authorize its products for use in any products where a malfunction or
* failure of the Infineon product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Infineon's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Infineon against all liability.
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef __CY_SOD_PROFILER_H__
#define __CY_SOD_PROFILER_H__

#ifdef COMPONENT_PROFILER
typedef enum
{
	SOD_PROFILE_CMD_INVALID,
	SOD_PROFILE_CMD_ENABLE,
	SOD_PROFILE_CMD_DISABLE,
	SOD_PROFILE_CMD_START, /** To be used internally inside the SOD MW */
	SOD_PROFILE_CMD_STOP,  /** To be used internally inside the SOD MW */
	SOD_PROFILE_CMD_GET_DATA,
	SOD_PROFILE_CMD_RESET,
	SOD_PROFILE_CMD_PRINT_STATS,
	SOD_PROFILE_CMD_MAX
} sod_profile_command;

typedef struct
{
	unsigned int cycles_taken;
    unsigned int profile_frame_counter;
} sod_profile_data_t;

cy_rslt_t cy_sod_profile(sod_profile_command cmd,
		sod_profile_data_t *data);

#endif /* COMPONENT_PROFILER */
#endif  /*__CY_SOD_PROFILER_H__ */

/* [] END OF FILE */
