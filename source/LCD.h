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

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>

#define LCD_ROW_0 (0x80)
#define LCD_CLEAR_DISPLAY (0x01)

extern volatile int num_chars;
extern volatile bool lcd_flag;

/*
 * This function is to initialize the LCD
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_LCD(void);

/*
 * This function is to send an instruction to the LCD
 *
 * Parameters: instruction to be sent
 *
 * Returns: none
 *
 */
void send_command_lcd (uint8_t);

/*
 * This function is to print a string on the LCD
 *
 * Parameters: string to be printed
 *
 * Returns: none
 *
 */
void put_str_lcd (char *);

/*
 * This function is for a delay
 *
 * Parameters: delay
 *
 * Returns: none
 *
 */
void delay_ms(uint16_t);

/*
 * This function is to print a character on the LCD
 *
 * Parameters: character to be printed
 *
 * Returns: none
 *
 */
void put_char_lcd(char);

/*
 * This function is to print the DHT11 data on the LCD
 *
 * Parameters: the integral and the decimal
 *
 * Returns: none
 *
 */
void print_data_lcd(uint8_t, uint8_t);

#endif /* LCD_H_ */
