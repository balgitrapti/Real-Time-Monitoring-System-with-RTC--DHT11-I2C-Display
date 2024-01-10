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
* @file UART_terminal.h
* @brief
*
* Function for the initial UART terminal & character handling
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#ifndef UART_TERMINAL_H_
#define UART_TERMINAL_H_

/*
 * Function for the serial terminal - how characters are handled and added to the command buffer
 *
 * Parameters: baud rate
 *
 * Returns: none
 *
 */
void UART_terminal (void);

#endif /* UART_TERMINAL_H_ */
