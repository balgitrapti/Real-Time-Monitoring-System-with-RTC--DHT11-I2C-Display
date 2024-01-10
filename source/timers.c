/*****************************************************************************
* Copyright (C) 2023 by Trapti Damodar Balgi
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Trapti Damodar Balgi and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/

/**
* @file timers.c
* @brief
*
* This source file contains functions related to the systick timer
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include <stdio.h>
#include <stdint.h>
#include "timers.h"

ticktime_t time_since_startup = 0 ;	// Time since startup, where one unit represents 1/16th of a second
ticktime_t time_since_reset = 0;	// Time elapsed since reset was called

/*
 * This function initializes the SysTick
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_systick(void)
{

	SysTick -> LOAD = SYSTICK_FOURTEEN_US;		// Set load to get interrupts every 62.5ms
	NVIC_SetPriority(SysTick_IRQn, 3);							// Set interrupt priority
	SysTick -> VAL = 0;											// Force load of reload value
	SysTick -> CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;		// Enable interrupt, alt. clock source & enable the systick timer
}

/*
 * The function returns the counts of SysTick overflow since startup
 *
 * Parameters: none
 *
 * Returns: Time since startup as a 32 bit value
 *
 */
ticktime_t now(void)
{
	return time_since_startup;
}

/*
 * The function resets the time_since_reset counter & reload value
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void reset_timer(void)
{
	time_since_reset = 0;
	SysTick -> VAL = 0;
}

/*
 * The function returns the counts of SysTick overflow since reset
 *
 * Parameters: none
 *
 * Returns: Time since reset as a 32 bit value
 *
 */
ticktime_t get_timer(void)
{
	return time_since_reset;
}

/*
 * The function is the handler for SysTick. With every overflow, the handler increments
 * the counts of time since startup and time since reset
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void SysTick_Handler()
{
	time_since_startup++;
	time_since_reset++;
}

/*
 * The function is for a delay of 62.5 ms.
 * It waits for time since startup to increment by 1 which takes 62.5ms.
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void delay (void)
{
	int val = time_since_startup + 1;
	while ( time_since_startup != val );
}
