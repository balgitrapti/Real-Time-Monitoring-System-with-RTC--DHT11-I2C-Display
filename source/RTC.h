/*******************************************************************************
 * Copyright (C) 2023 by Trapti Damodar Balgi
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Trapti Damodar Balgi and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
* @file RTC.c
* @brief
*
* Functions related to the RTC
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.0
* @references:
* 1) Using RTC module on FRDM-KL25Z: https://community.nxp.com/t5/Kinetis-Microcontrollers/Using-RTC-module-on-FRDM-KL25Z/ta-p/1127476
* 2) µTasker – Time-Keeping: https://www.utasker.com/docs/uTasker/uTasker_Time.pdf
* 2) µTasker KL RTC Support - https://www.utasker.com/kinetis/KL_RTC.html
* 3) KL25 - RTC and system oscillator - https://community.nxp.com/t5/Kinetis-Microcontrollers/KL25-RTC-and-system-oscillator/td-p/279645
*/

#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include <stdbool.h>

extern volatile bool tim_flag;
extern volatile uint32_t seconds, minutes, hours;

/*
 * This function is to initialize the RTC
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_RTC(void);

/*
 * This function is to the RTC seconds handler
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void RTC_Seconds_IRQHandler(void);

/*
 * This function is to update the clock
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void clock_update (void);

#endif /* RTC_H_ */
