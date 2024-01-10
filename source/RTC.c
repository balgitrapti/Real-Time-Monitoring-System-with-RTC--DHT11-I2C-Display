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
* @file RTC.c
* @brief
*
* Functions related to the RTC
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.0
* @references:
* 1) Using RTC module on FRDM-KL25Z: https://community.nxp.com/t5/Kinetis-Microcontrollers/Using-RTC-module-on-FRDM-KL25Z/ta-p/1127476
* 2) µTasker – Time-Keeping: https://www.utasker.com/docs/uTasker/uTasker_Time.pdf
* 2) µTasker KL RTC Support - https://www.utasker.com/kinetis/KL_RTC.html
* 3) KL25 - RTC and system oscillator - https://community.nxp.com/t5/Kinetis-Microcontrollers/KL25-RTC-and-system-oscillator/td-p/279645
*/

#include <I2C.h>
#include "RTC.h"
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "timers.h"
#include "DHT11.h"
#include "LCD.h"

#define UM (1 << 2)
#define SUP (1 << 3)

#define TIME_BUFFER (8)
#define SIXTY_S (60)
#define SIXTY_M (60)
#define HOURS (0)
#define MIN_1 (2)
#define MIN_2 (3)
#define S_1 (5)
#define S_2 (6)

#define TIME_POSITION (0xE1)
#define TIME_CHARACTERS (7)

#define ONE_S_UPDATE (0x00007C00)

volatile bool tim_flag = 0;
volatile uint32_t seconds = 0, minutes = 0, hours = 0;

/*
 * This function is to initialize the RTC
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void init_RTC(void)
{
    // Enable clock to port C
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Enable the internal reference clock. MCGIRCLK is active.
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;
    // Select the slow internal reference clock source.
    MCG->C2 &= ~(MCG_C2_IRCS_MASK);
    // Set PTC1 as RTC_CLKIN and select 32 KHz clock source for the RTC module.
    PORTC->PCR[1] |= (PORT_PCR_MUX(0x1));
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0);

    // Set PTC3 as CLKOUT pin and selects the MCGIRCLK clock to output on the CLKOUT pin.
    SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
    PORTC->PCR[3] |= (PORT_PCR_MUX(0x5));

    // Enable software access and interrupts to the RTC module.
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;

    // Clear all RTC registers.
    RTC->CR = RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;

    // Set update node and supervisor access
    RTC->CR = UM | SUP;
    RTC->TPR = ONE_S_UPDATE;

    if (RTC->SR & RTC_SR_TIF_MASK)
    {
        RTC->TSR = 0x00000000;
    }

    // Set time compensation parameters. (These parameters can be different for each application)
    RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    // Enable time seconds interrupt for the module and enable its IRQ.
    NVIC_SetPriority(UART0_IRQn, 2);
    NVIC_EnableIRQ(RTC_Seconds_IRQn);
    NVIC_ClearPendingIRQ(RTC_Seconds_IRQn);

    // Set time seconds interrupt
    RTC->IER |= RTC_IER_TSIE_MASK;

    // Enable time counter.
    RTC->SR |= RTC_SR_TCE_MASK;
}

/*
 * This function is to the RTC seconds handler
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void RTC_Seconds_IRQHandler(void)
{
	// Reset the pre-scaler
	RTC->SR = 0x00000000;
	RTC->TPR = ONE_S_UPDATE;
	RTC->SR = 0x00000010;

	// Set flag, update seconds and update the clock
	tim_flag = 1;
	seconds++;
	clock_update();
}

/*
 * This function is to update the clock
 *
 * Parameters: none
 *
 * Returns: none
 *
 */
void clock_update (void)
{
	char time[TIME_BUFFER];
	time[7] = '\0', time[4] = ':', time[1] = ':';
	if (seconds == SIXTY_S)
	{
		minutes++;
		seconds = 0;
		if (minutes == SIXTY_M)
		{
			hours++;
			minutes = 0;
		}
	}

    // Convert to characters to be printed
    time[S_2] = seconds%10 + '0';
    time[S_1] = seconds/10 + '0';
    time[MIN_2] = minutes%10 + '0';
    time[MIN_1] = minutes/10 + '0';
    time[HOURS] = hours + '0';

    // Flag for DDRAM address not to be updated
    lcd_flag = 1;
    // Set cursor position
    send_command_lcd(TIME_POSITION);
    // Print time
    put_str_lcd(time);
//    // Subtract number of characters by 7 - number of characters needed to display time
//    num_chars = num_chars - TIME_CHARACTERS;
    // Reset flag
    lcd_flag = 0;
}
