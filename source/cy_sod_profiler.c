/******************************************************************************
* File Name: cy_sod.c
*
* Description: This file contains functions for Speech onset detection.
*              
*
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
* Include header file
******************************************************************************/

#ifdef COMPONENT_PROFILER
#include "cy_sod_private.h"
#include "cy_sod_profiler.h"
#include "cy_profiler.h"

/******************************************************************************
* Defines
*****************************************************************************/

/******************************************************************************
* Constants
*****************************************************************************/

/******************************************************************************
* Variables
*****************************************************************************/

/******************************************************************************
* Functions
*****************************************************************************/

bool sod_profile_on = false;
sod_profile_data_t sod_profile = {0};

cy_rslt_t cy_sod_profile(sod_profile_command cmd,
		sod_profile_data_t *data)
{
	switch(cmd)
	{
		case SOD_PROFILE_CMD_ENABLE:
		{
			sod_profile.cycles_taken = 0;
			sod_profile.profile_frame_counter = 0;
			sod_profile_on = true;
			break;
		}
		case SOD_PROFILE_CMD_DISABLE:
		{
			sod_profile_on = false;
			break;
		}

		case SOD_PROFILE_CMD_START:
		{
			if(true == sod_profile_on)
			{
				sod_profile.profile_frame_counter++;
				cy_profiler_start();
			}
			break;
		}
		case SOD_PROFILE_CMD_STOP:
		{
			if(true == sod_profile_on)
			{
				cy_profiler_stop();
				sod_profile.cycles_taken += cy_profiler_get_cycles();
			}
			break;
		}
		case SOD_PROFILE_CMD_GET_DATA:
		{
			if(true == sod_profile_on)
			{
				if(NULL != data)
				{
					data->cycles_taken = sod_profile.cycles_taken;
					data->profile_frame_counter = sod_profile.profile_frame_counter;
				}
			}
			break;
		}
		case SOD_PROFILE_CMD_RESET:
		{
			if(true == sod_profile_on)
			{
				sod_profile.cycles_taken = 0;
				sod_profile.profile_frame_counter = 0;
			}
			break;
		}
		case SOD_PROFILE_CMD_PRINT_STATS:
		{
			 cy_sod_app_log_info("SODProfile:Cntr:%u, Cycles:%u",
					 sod_profile.profile_frame_counter,
					 sod_profile.cycles_taken);
			 printf("\r\nSOD-Profile:Cntr:%u, Cycles:%u\r\n",
					 sod_profile.profile_frame_counter,
					 sod_profile.cycles_taken);
			 break;
		}
		default:
		{
			break;
		}
	}

	return CY_RSLT_SUCCESS;
}

#endif
