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
* @file main.c
* @brief
*
* Main function for the serialIO
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#include <stdio.h>
#include <stdint.h>
#include "UART.h"
#include "processor.h"
#include "UART_terminal.h"

#define MAX_BUFFER_SIZE (255)
#define ASCII_BACKSPACE (8)
#define ASCII_SPACE (32)
#define ASCII_CARRIAGE_RETURN (13)
#define ASCII_DELETE (127)
#define ASCII_NO_CHAR (-1)
#define ASCII_NULL (0)

/*
 * Function for the serial terminal - how characters are handled and added to the command buffer
 *
 * Parameters: baud rate
 *
 * Returns: none
 *
 */
void UART_terminal(void)
{
    uint8_t ch = 0;
    char command_buffer[MAX_BUFFER_SIZE];
    printf("\n\r\t\tReal-Time Environment Monitor with RTC and DHT11\t\t\n\r");

    while (1)
    {
        printf("\n\n\r$$ ");

        uint8_t i = 0;
        while (i < MAX_BUFFER_SIZE)
        {
            while ((ch = getchar()) == (char)(ASCII_NO_CHAR));

            if (ch == ASCII_CARRIAGE_RETURN)
            {
                printf("\n\r");
                command_buffer[i] = ASCII_NULL;
                break;  // Exit loop when carriage return is encountered
            }
            else if ((ch == ASCII_BACKSPACE) || (ch == ASCII_DELETE))
            {
                if (i > 0)
                {
                    putchar(ASCII_BACKSPACE);
                    putchar(ASCII_SPACE);
                    putchar(ASCII_BACKSPACE);
                    command_buffer[--i] = ASCII_NULL;
                }
            }
            else
            {
                putchar(ch);
                if (i == (MAX_BUFFER_SIZE -1))
                {
                    printf("\n\rMaximum limit of buffer reached. Cannot add more commands, sending for processing.");
                    command_buffer[i] = ch;
                    break;  // Exit loop when buffer limit reached
                }
                else
                {
                    command_buffer[i++] = ch;
                }
            }
        }
        command_buffer[MAX_BUFFER_SIZE - 1] = ASCII_NULL;  // Ensure null termination

        process_command(command_buffer);
    }
}
