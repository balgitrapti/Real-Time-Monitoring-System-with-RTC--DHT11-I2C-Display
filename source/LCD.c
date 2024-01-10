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
* @file LCD.c
* @brief
*
* Functions related to the I2C LCD display
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.0
* @references:
* 1) Texas Instruments PCF8574 Remote 8-Bit I/O Expander for I2C Bus
* 2) HD44780U (LCD-II) data sheet
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
* 3) Difference between interfacing character 16×2 lcd in 4-bit and 8-bit mode with microcontroller :
* 		https://www.engineersgarage.com/lcd-in-4-bit-mode-and-8-bit-mode/
* 4) Interfacing 16×2 LCD with KL25Z Series MCU: https://learningmicro.wordpress.com/interfacing-lcd-with-kl25z-freedom-board/
*/

#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "I2C.h"
#include "LCD.h"

#define LCD_ADDRESS (0x4E)

#define LCD_MOVE_CURSOR (0x02)
#define LCD_ENABLE_4BIT (0x28)
#define LCD_DISPLAY_ON (0x0F)

#define LCD_ROW_1 (0xC0)
#define LCD_ROW_2 (0x94)
#define LCD_ROW_3 (0xD4)

#define MAX_CHARACTERS_IN_ROW_0 (20)
#define MAX_CHARACTERS_IN_ROW_1 (40)
#define MAX_CHARACTERS_IN_ROW_2 (60)
#define MAX_CHARACTERS_IN_ROW_3 (73)
#define NO_CHARACTERS (0)

#define DATA_COMMAND (0b1101)
#define INSTRUCTION_COMMAND (0b1100)

#define ENABLE_LOW (data &= ~(0b00000100))

volatile int num_chars = 0;
volatile bool lcd_flag = 0;

/*
 * This function is to initialize the LCD
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_LCD(void)
{
    send_command_lcd(LCD_MOVE_CURSOR);           // Move the cursor to original position
    while (read_byte_I2C(LCD_ADDRESS) & 0x80);   // Busy wait
    send_command_lcd(LCD_ENABLE_4BIT);           // Enable 4-bit
    while (read_byte_I2C(LCD_ADDRESS) & 0x80);   // Busy wait
    send_command_lcd(LCD_DISPLAY_ON);            // Display ON, Cursor ON and blinking
    while (read_byte_I2C(LCD_ADDRESS) & 0x80);   // Busy wait
    send_command_lcd(LCD_CLEAR_DISPLAY);         // Clear Display
    while (read_byte_I2C(LCD_ADDRESS) & 0x80);   // Busy wait
    delay_ms(500);
}

/*
 * This function is a general function to send a data or instruction command to the LCD
 *
 * Parameters: type of command to be sent and the contents of the command
 *
 * Returns: none
 *
 */
void send_lcd (uint8_t type, uint8_t byte)
{
	uint8_t upper_nibble = (byte & 0xF0) >> 4; // Extract upper nibble
	uint8_t lower_nibble = byte & 0x0F;        // Extract lower nibble
	uint8_t data = (upper_nibble << 4) | type;

	I2C_TRAN;      		// Set to transmit mode
	I2C_M_START;   		// Send start
	I2C0->D = LCD_ADDRESS;   	// Send dev address
	I2C_WAIT;       	// Wait for ack

	// Send upper nibble
	// Send E high
	I2C0->D = data; 	 // Send data
	I2C_WAIT;
	delay_ms(500);

	// Send E low
	ENABLE_LOW;
	I2C0->D = data;  	 // Send data
	I2C_WAIT;
	delay_ms(500);

	data = 0;
	// Send lower nibble
	// Send E high
	data = (lower_nibble << 4) | type;
	I2C0->D = data;  	 // Send data
	I2C_WAIT;
	delay_ms(500);

	// Send E low
	ENABLE_LOW;
	I2C0->D = data;  	// Send data
	I2C_WAIT;
	I2C_M_STOP;
	delay_ms(500);
}

/*
 * This function is to send an instruction to the LCD
 *
 * Parameters: instruction to be sent
 *
 * Returns: none
 *
 */
void send_command_lcd (uint8_t byte)
{
	send_lcd (INSTRUCTION_COMMAND, byte);
}

/*
 * This function is to print a string on the LCD
 *
 * Parameters: string to be printed
 *
 * Returns: none
 *
 */
void put_str_lcd (char *str)
{
    for(int i=0; str[i] != '\0' ;i++)
    {
    	put_char_lcd(str[i]);
    	while(read_byte_I2C(LCD_ADDRESS) & 0x80);	// busy wait
    }
}

/*
 * This function is for a delay
 *
 * Parameters: delay
 *
 * Returns: none
 *
 */
void delay_ms(uint16_t cnt)
{
	for (int j = 0; j < 5; j++)
	{
		for(int i = 0;i < cnt; i++);
	}
}

/*
 * This function is to print a character on the LCD
 *
 * Parameters: character to be printed
 *
 * Returns: none
 *
 */
void put_char_lcd(char byte)
{
	// Update the cursor position if not for clock
	if (lcd_flag != 1)
	{
	    if (num_chars == NO_CHARACTERS)
	        send_command_lcd(LCD_ROW_0);
	    else if (num_chars == MAX_CHARACTERS_IN_ROW_0)
	        send_command_lcd(LCD_ROW_1);
	    else if (num_chars == MAX_CHARACTERS_IN_ROW_1)
	        send_command_lcd(LCD_ROW_2);
	    else if (num_chars == MAX_CHARACTERS_IN_ROW_2)
	        send_command_lcd(LCD_ROW_3);
	    else if (num_chars == MAX_CHARACTERS_IN_ROW_3)
	        send_command_lcd(LCD_ROW_0);

	    // Increment the number of characters displayed on the LCD
	    num_chars++;
	}
	// Send the data
	send_lcd (DATA_COMMAND, byte);
}

/*
 * This function is to print the DHT11 data on the LCD
 *
 * Parameters: the integral and the decimal
 *
 * Returns: none
 *
 */
void print_data_lcd(uint8_t integral, uint8_t decimal)
{
	// Print the data - Integral
	int digit = integral / 10; 		// Extract the MSD
	put_char_lcd(digit + '0');
	digit = integral % 10;
	put_char_lcd(digit + '0');

	while(read_byte_I2C(0x4E) & 0x80);	// busy wait
	put_char_lcd('.');

	// Print the data - Decimal
	digit = 0;
	digit = decimal / 10; 		// Extract the MSD
	put_char_lcd(digit + '0');
	digit = decimal % 10;
	put_char_lcd(digit + '0');
}
