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
* @file processor.h
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

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

/*
 * Checks if the inputs received for the LED command are valid - either integer or hex
 *
 * Parameters: Each argument, one by one
 *
 * Returns: Status of validity - 1 if invalid, 0 if valid
 *
 */
int check_valid (char* str);

/*
 * Function to process the LED command and turn on respective LEDs
 *
 * Parameters: Each argument, one by one
 *
 * Returns: none
 *
 */
void LED_input_process(char* str);
/*
 * Function to create a delay of 1s
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void timer_delay (void);

/*
 * Handler fucntion for the LED command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void led_handler(int argc, char *argv[]);


/*
 * Handler function for the ECHO command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void echo_handler(int argc, char *argv[]);

/*
 * Handler function for the HELP command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void help_handler(int argc, char *argv[]);


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
void process_command(char *input);

/*
 * Handler function for the TEMP command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void temp_handler(int argc, char *argv[]);

/*
 * Handler function for the HUMIDITY command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void humidity_handler(int argc, char *argv[]);

/*
 * Handler function for the RESET command
 *
 * Parameters: The token pointers and number of tokens
 *
 * Returns: none
 *
 */
void reset_handler(int argc, char *argv[]);


#endif /* PROCESSOR_H_ */
