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
* @file I2C.h
* @brief
*
* Functions related to the I2C protocol
*
* @author Alexander G. Dean. Edited by Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.0
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#include <stdint.h>

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN		I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK
#define I2C_WAIT 		wait_I2C();

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           	I2C0->C1 &= ~I2C_C1_TXAK_MASK

void init_I2C(void);

/*
 * This function waits for transmission to complete
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void wait_I2C(void);

/*
 * This function sends the I2C start sequence
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void start_I2C();

/*
 * This function sends is to read a byte from the I2C device
 *
 * Parameters: The device address
 *
 * Returns: The byte read
 *
 */
uint8_t read_byte_I2C(uint8_t dev);


/*
 * This function sends is to write a byte to the I2C device
 *
 * Parameters: The device address & data to be written
 *
 * Returns: none
 *
 */
void write_byte_I2C(uint8_t dev, uint8_t data);
