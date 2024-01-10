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
* @file DHT11.h
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

#ifndef DHT11_H_
#define DHT11_H_

#include <stdbool.h>

extern uint8_t hum_i_buffer, hum_d_buffer, temp_i_buffer, temp_d_buffer;

/*
 * This function sets the direction of the DHT11 pin
 *
 * Parameters: direction - either input or output
 *
 * Returns: none
 *
 */
void set_pin_direction (bool);

/*
 * This function initializes the DHT11 sensor GPIO port
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_DHT11(void);

/*
 * This function sends a start signal for the DHT11
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void send_start_DHT11 (void);

/*
 * This function acquires data from the DHT11
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void get_data_DHT11 (void);

#endif /* DHT11_H_ */
