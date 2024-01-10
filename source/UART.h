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
* @file UART.h
* @brief
*
* Header file for the UART functions
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#ifndef UART_H
#define UART_H

/*
 * Intialization of UART0
 *
 * Parameters: none
 *
 * Returns: none
 *
 * Reference: Taken from ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code) and modified per requirement
 *
 */
void init_UART0 ();

/*
 * UART0 interrupt handler
 *
 * Parameters: none
 *
 * Returns: none
 *
 * Reference: Taken from ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code) and modified per requirement
 *
 */
void UART0_IRQHandler (void);

/*
 * sys_write to redirect output. Write the specified bytes to stdout (handle = 1) or stderr (handle = 2).
 * Returns -1 on error, or 0 on success.
 *
 * Parameters: int iFileHandle, char *pcBuffer, int iLength
 *
 * Returns: Returns -1 on error, or 0 on success.
 *
 */
int __sys_write (int iFileHandle, char *pcBuffer, int iLength);

/*
 * sys_read to redirect input. Return one character from stdin. Return -1 on error or if no data is available to be read.
 *
 * Parameters: none
 *
 * Returns: one charcter from stdin
 *
 */
int __sys_readc (void);

#endif
