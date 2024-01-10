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
* @file timers.h
* @brief
*
* This header file provides macros and function descriptions for the systick timer
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#ifndef _TIMER_H_
#define _TIMER_H_

/* Taking 62.5ms as the resolution for the systick. In order to achieve a delay of 500ms, 1s, etc.,
 * the systick interrupt needs to overflow (x/62.5ms)with x being the delay needed in seconds
 *
 * Added macros for common delays with the factor
 *
 */

typedef uint32_t ticktime_t;  // time since boot, in sixteenths of a second

#define SYSTICK_FOURTEEN_US (42)	// Systick load value to get an interrupt every 14us (3MHz*14us)

/*
 * This function initializes the SysTick
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_systick(void);

/*
 * The function returns the counts of SysTick overflow since startup
 *
 * Parameters: none
 *
 * Returns: Time since startup as a 32 bit value
 *
 */
ticktime_t now(void);

/*
 * The function resets the time_since_reset counter & reload value
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void reset_timer(void);

/*
 * The function returns the counts of SysTick overflow since reset
 *
 * Parameters: none
 *
 * Returns: Time since reset as a 32 bit value
 *
 */
ticktime_t get_timer(void);

/*
 * The function is the handler for SysTick. With every overflow, the handler increments
 * the counts of time since startup and time since reset
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void SysTick_Handler();

/*
 * The function is for a delay of 62.5 ms.
 * It waits for time since startup to increment by 1 which takes 62.5ms.
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void delay (void);

#endif
