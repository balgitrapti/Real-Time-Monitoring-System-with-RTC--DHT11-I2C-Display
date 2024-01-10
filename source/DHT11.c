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
* @file DHT11.c
* @brief
*
* Functions related to the DHT11 sensor
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.0
* @references:
* 1) DHT11 Humidity & Temperature Sensor datasheet
*/

#include <stdio.h>
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "timers.h"
#include "DHT11.h"

#define DHT_11 (3)
#define OUTPUT (1)
#define INPUT (0)

#define ONE_FORTY_US (10)
#define EIGHTEEN_MS (1285)
#define FORTY_TWO_US (3)

#define BUFFER_SIZE (40)
#define BITS_PER_VALUE (8)

#define HUM_I_START (0)
#define HUM_I_END (HUM_I_START + BITS_PER_VALUE)

#define HUM_D_START (8)
#define HUM_D_END (HUM_D_START + BITS_PER_VALUE)

#define TEMP_I_START (16)
#define TEMP_I_END (TEMP_I_START + BITS_PER_VALUE)

#define TEMP_D_START (24)
#define TEMP_D_END (TEMP_D_START + BITS_PER_VALUE)

#define CHECKSUM_START (32)
#define CHECKSUM_END (CHECKSUM_START + BITS_PER_VALUE)

uint8_t hum_i_buffer = 0, hum_d_buffer = 0, temp_i_buffer = 0, temp_d_buffer = 0;

/*
 * This function sets the direction of the DHT11 pin
 *
 * Parameters: direction - either input or output
 *
 * Returns: none
 *
 */
void set_pin_direction (bool direction)
{
	if (direction) 							// output
		GPIOD->PDDR |= (1 << DHT_11);
	else									// input
		GPIOD->PDDR &= ~(1 << DHT_11);
}

/*
 * This function initializes the DHT11 sensor GPIO port
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_DHT11(void)
{
	// Enable clock to port D
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[DHT_11] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[DHT_11] =PORT_PCR_MUX(1);						// Configured as GPIO
}

/*
 * This function sends a start signal for the DHT11
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void send_start_DHT11 (void)
{
	set_pin_direction(OUTPUT);
	reset_timer();								// Reset the counter for time since reset
	GPIOD->PCOR |= (1 << DHT_11);
	while(get_timer() <= EIGHTEEN_MS);			// Wait for 18ms
	GPIOD->PCOR &= ~(1 << DHT_11);
}

/*
 * This function acquires data from the DHT11
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void get_data_DHT11 (void)
{
	uint8_t buffer[BUFFER_SIZE], checksum = 0;
	set_pin_direction(INPUT);

	// Wait for 140us
	reset_timer();
	while(get_timer() < ONE_FORTY_US);
	while((GPIOD->PDIR & (1 << DHT_11)));				// Wait for bit to become low

	// Data transmission starts
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		while(!(GPIOD->PDIR & (1 << DHT_11)));			// Wait for bit to become high
		// Wait for 42us
		reset_timer();
		while(get_timer() < FORTY_TWO_US);
		// If still high, bit is 1, else 0
		if(GPIOD->PDIR & (1 << DHT_11))
		{
			buffer[i] = 1;
		}
		else
		{
			buffer[i] = 0;
		}
		while((GPIOD->PDIR & (1 << DHT_11)));			// Wait for bit to become low
	}

	// Extract the bits
	for (int i = HUM_I_START; i < HUM_I_END; i++)
	{
	    hum_i_buffer = (hum_i_buffer << 1) | buffer[i];
	}
	for (int i = HUM_D_START; i < HUM_D_END; i++)
	{
	    hum_d_buffer = (hum_d_buffer << 1) | buffer[i];
	}
	for (int i = TEMP_I_START; i < TEMP_I_END; i++)
	{
	    temp_i_buffer = (temp_i_buffer << 1) | buffer[i];
	}
	for (int i = TEMP_D_START; i < TEMP_D_END; i++)
	{
	    temp_d_buffer = (temp_d_buffer << 1) | buffer[i];
	}
	for (int i = CHECKSUM_START; i < CHECKSUM_END; i++)
	{
	    checksum = (checksum << 1) | buffer[i];
	}

	// Error control
	if (!(checksum == (hum_i_buffer + hum_d_buffer + temp_i_buffer + temp_d_buffer)))
	{
	    printf("\n\rError in sensor readings");
	}
}


