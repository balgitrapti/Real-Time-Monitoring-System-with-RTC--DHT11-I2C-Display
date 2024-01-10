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
* @file processor.c
* @brief
*
* File for the command processor
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
* 3) PES Lecture Slides - Command Processing
*/

#include <MKL25Z4.H>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <I2C.h>
#include "UART.h"
#include "cbfifo.h"
#include "processor.h"
#include "timers.h"
#include "LCD.h"
#include "DHT11.h"
#include "RTC.h"

#define MAX_TOKEN_SIZE (30)

// Fucntion pointer for command handlers
typedef void (*command_handler_t)(int, char *argv[]);

// Structure for the command handler with name of command, name of command handler, and description
typedef struct {
const char *name;
command_handler_t handler;
const char *help_string;
} command_table_t;

// Table of commands
static const command_table_t commands[] = {
		{"ECHO", echo_handler, "Echoes the same string back in upper case but removes any whitespaces."},
		{"HUMIDITY", humidity_handler, "Displays the humidity."},
		{"TEMP", temp_handler, "Displays the temperature."},
		{"RESET", reset_handler, "Resets the clock."},
		{"HELP", help_handler, "Details of the functions"}
};

static const int num_commands = 5;

/*
 * Handler function for the RESET command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void reset_handler(int argc, char *argv[])
{
	seconds = 0;
	minutes = 0;
	hours = 0;
}

/*
 * Handler function for the ECHO command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void echo_handler(int argc, char *argv[])
{
	// Clear the display
	send_command_lcd(LCD_CLEAR_DISPLAY);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	// Reset number of characters on screen
	num_chars = 0;
	// Move to row 0, position 0
	send_command_lcd(LCD_ROW_0);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait

	// If there are more than one tokens, print the rest
	for (int k = 1; k < argc; k++)
	{
		for (int i = 0; i < strlen(argv[k]); i++)
		{
			*(argv[k] + i) = toupper(*(argv[k] + i));				// Change to upper case
			put_char_lcd(*(argv[k] + i));							// Print on LCD
		}
		put_char_lcd(' ');
	}
}

/*
 * Handler function for the HUMIDITY command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void humidity_handler(int argc, char *argv[])
{
	// Get the data from the DHT11 sensor
	send_start_DHT11();
	get_data_DHT11();

	// Clear the display
	send_command_lcd(LCD_CLEAR_DISPLAY);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	// Reset number of characters on screen
	num_chars = 0;
	// Move to row 0, position 0
	send_command_lcd(LCD_ROW_0);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait

	// Print the humdity data
	put_str_lcd("Humidity: ");
	print_data_lcd(hum_i_buffer, hum_d_buffer);

	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	put_char_lcd('%');
}

/*
 * Handler function for the TEMPERATURE command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void temp_handler(int argc, char *argv[])
{
	// Get the data from the DHT11 sensor
	send_start_DHT11();
	get_data_DHT11();

	// Clear the display
	send_command_lcd(LCD_CLEAR_DISPLAY);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	// Reset number of characters on screen
	num_chars = 0;
	// Move to row 0, position 0
	send_command_lcd(LCD_ROW_0);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait

	// Print the temperature data
	put_str_lcd("Temperature: ");
	print_data_lcd(temp_i_buffer, temp_d_buffer);
	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	put_char_lcd('C');
}

/*
 * Handler function for the HELP command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void help_handler(int argc, char *argv[])
{
	// Print the commands
	for (int i = 0; i < (num_commands - 1); i++)
	{
		printf("\n\r%s:  %s", commands[i].name, commands[i].help_string);		// Print command with help string
	}
}


/*
 * Function to process the command buffer
 *
 * Parameters: The command buffer
 *
 * Returns: none
 *
 * References: Original taken from PES slides - Command Processing, modified per needs
 *
 */
void process_command(char *input)
{
	char *p = input;
	char *end;
	// Find end of string
	for (end = input; *end != '\0'; end++);
	// Tokenize input in place
	bool in_token = false;
	char *argv[MAX_TOKEN_SIZE];
	int argc = 0;
	memset(argv, 0, sizeof(argv));
	for (p = input; p < end; p++)
	{
		if (*p == ' ' || *p == '\t')						// whitespace character found
		{
		    if (in_token)
		    {
		        *p = '\0';									// if in token, terminate
		         in_token = false;
		    }
		}
		else
		{
		    if (!in_token)
		    {
		        argv[argc++] = p;							// new token found
		        in_token = true;
		        if (argc == MAX_TOKEN_SIZE)
		        {
		            break;									// max token size reached
		        }
		    }
		}
	}
	if (in_token)
	{
		*p = '\0';											// terminate last token with null character
	}
	argv[argc] = NULL;
	if (argc == 0) 											// no command
		return;

	// Check for command match and send to handler
	for (int i=0; i < num_commands; i++)
	{
		if (strcasecmp(argv[0], commands[i].name) == 0)
		{
			commands[i].handler(argc, argv);
			break;
		}
		if (i == num_commands - 1)
		{
			printf("\n\rUnknown command\n\r");
		}
	}
}


