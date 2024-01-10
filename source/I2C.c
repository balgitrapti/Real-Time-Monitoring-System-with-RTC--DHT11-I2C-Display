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
* @file I2C.c
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

#include <I2C.h>
#include <MKL25Z4.H>

int lock_detect=0;
int i2c_lock=0;

/*
 * This function initializes the I2C bus
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_I2C(void)
{
	// Clock I2C peripheral and port B
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTB_MASK);

	// Set pins to I2C function
	PORTB->PCR[0] |= PORT_PCR_MUX(2);
	PORTB->PCR[1] |= PORT_PCR_MUX(2);

	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	// Enable I2C and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}

/*
 * This function is for I2C busy check
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void busy_I2C(void)
{
	// Start Signal
	lock_detect = 0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;

	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; 	// Set MASTER mode
	I2C0->C1 |= I2C_C1_TX_MASK; 	// Set transmit (TX) mode
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {
	} // Wait interrupt
	I2C0->S |= I2C_S_IICIF_MASK; // Clear interrupt bit

	I2C0->S |= I2C_S_ARBL_MASK;	// Clear arbitration error flag

	// Send start
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK; // Set transmit (TX) mode
	I2C0->C1 |= I2C_C1_MST_MASK; // START signal generated
	I2C0->C1 |= I2C_C1_IICEN_MASK; // Wait until start is sent

	// Send stop
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; // Set SLAVE mode
	I2C0->C1 &= ~I2C_C1_TX_MASK; // Set Rx
	I2C0->C1 |= I2C_C1_IICEN_MASK; // Wait
	I2C0->S |= I2C_S_IICIF_MASK; // Clear arbitration error & interrupt flag
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect = 0;
	i2c_lock = 1;
}

/*
 * This function waits for transmission to complete
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void wait_I2C(void)
{
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200))
	{
		lock_detect++;
	} 
	if (lock_detect >= 200)
		busy_I2C();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*
 * This function sends the I2C start sequence
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void start_I2C()
{
    I2C_TRAN;  		// Set to transmit mode
    I2C_M_START;  	// Send start
}

/*
 * This function sends is to read a byte from the I2C device
 *
 * Parameters: The device address
 *
 * Returns: The byte read
 *
 */
uint8_t read_byte_I2C(uint8_t dev)
{
    uint8_t data;
	
    I2C_TRAN;        // Set to transmit mode
    I2C_M_START;     // Send start
    I2C0->D = dev;   // Send dev address
    I2C_WAIT         // Wait for completion

    I2C_M_RSTART;    // Repeated start
    I2C0->D = (dev | 0x1);   // Send dev address (read)
    I2C_WAIT         // Wait for completion

    I2C_REC;         // Set to receive mode
    NACK;            // Set NACK after read

    data = I2C0->D;  // Dummy read
    I2C_WAIT         // Wait for completion

    I2C_M_STOP;      // Send stop
    data = I2C0->D;  // Read data

    return data;
}


/*
 * This function sends is to write a byte to the I2C device
 *
 * Parameters: The device address & data to be written
 *
 * Returns: none
 *
 */
void write_byte_I2C(uint8_t dev, uint8_t data)
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */
		
	I2C0->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;
}
