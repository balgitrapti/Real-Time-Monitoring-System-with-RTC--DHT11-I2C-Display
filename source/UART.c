
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
* @file UART.c
* @brief
*
* File for the UART functions
*
* @author Trapti Damodar Balgi
* @date 13th December 2023
* @version 1.1
* @references:
* 1) Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers by Alexander G. Dean
* 2) ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code)
*/

#include <MKL25Z4.H>
#include "UART.h"
#include <stdio.h>
#include "cbfifo.h"

// UART macros
#define UART_OVERSAMPLE_RATE (16)
#define BUS_CLOCK (24e6)
#define SYS_CLOCK (24e6)
#define UART_BAUD_RATE (38400)
#define NINE_DATA_BIT_MODE (1)
#define PARITY_ENABLE (1)
#define ODD_PARITY (1)
#define TWO_STOP_BITS (1)
#define RX_ENABLE (1)
#define TX_ENABLE (1)
#define RX_INT_ENABLE (1)
#define TX_INT_ENABLE (1)
#define MCGFLLCLK_SELECT (0)
#define MCGFLLCLK_MCGPLLCLK_SELECT (1)

#define ONE_BYTE (1)
#define ERROR (-1)
#define NO_ERROR (0)


extern CircularBuffer_t* txfifo;
extern CircularBuffer_t* rxfifo;

/*
 * Intialization of UART0
 *
 * Parameters: none
 *
 * Returns: none
 *
 * Reference: Taken from ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code) and modified per requirement
 *
 */
void init_UART0()
{
	uint32_t baud_rate = UART_BAUD_RATE;
	uint16_t sbr;
	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 24MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK_MCGPLLCLK_SELECT);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(MCGFLLCLK_SELECT);

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

	// Select two stop bits
	UART0->BDH |= UART0_BDH_SBNS(TWO_STOP_BITS);

	// Use 9 data bit mode, use odd parity
	UART0->C1 = UART0_C1_M(NINE_DATA_BIT_MODE) | UART0_C1_PE(PARITY_ENABLE) | UART0_C1_PT(ODD_PARITY);

	// Enable interrupt for Rx
	UART0->C2 = UART0_C2_RIE(RX_INT_ENABLE);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(RX_ENABLE) | UART0_C2_TE(TX_ENABLE);

	// Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

	// Enable NVIC for UART0
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
}

/*
 * UART0 interrupt handler
 *
 * Parameters: none
 *
 * Returns: none
 *
 * Reference: Taken from ESF/NXP/Misc at master (https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code) and modified per requirement
 *
 */
void UART0_IRQHandler(void)
{
	uint8_t ch;
	// If character has arrived at the serial port
	if (UART0->S1 & UART0_S1_RDRF_MASK)
	{
		// If rxfifo not full
		if(cbfifo_length(rxfifo) != MAX_BUFFER_SIZE)
		{
			ch = UART0->D;
			// Enqueue to rxfifo
			cbfifo_enqueue(&ch, ONE_BYTE, rxfifo);
		}
	}

	// If character is to be sent from the serial port & data register is empty
	if ((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK))
	{
		// If txfifo is not empty
		if(cbfifo_length(txfifo) != 0)
		{
			uint8_t ch = 0;
			cbfifo_dequeue(&ch, ONE_BYTE, txfifo);
			UART0->D = ch;
		}
		else
		{
			// FIFO was empty, so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

/*
 * sys_write to redirect output. Write the specified bytes to stdout (handle = 1) or stderr (handle = 2).
 * Returns -1 on error, or 0 on success.
 *
 * Parameters: int iFileHandle, char *pcBuffer, int iLength
 *
 * Returns: Returns -1 on error, or 0 on success.
 *
 */
int __sys_write(int iFileHandle, char *pcBuffer, int iLength)
{
	unsigned int i;
	for (i = 0; i < iLength; i++)
	{
		// If txfifo is not empty
		if(cbfifo_length(txfifo) != MAX_BUFFER_SIZE)
		{
			// Add to txfifo
			cbfifo_enqueue(&pcBuffer[i], ONE_BYTE, txfifo);
		}
		else
			return ERROR; 				// Return -1 on error
	}

	// Enable Tx interrupt
	UART0->C2 |= UART0_C2_TIE(TX_INT_ENABLE);

	return NO_ERROR;
}

/*
 * sys_read to redirect input. Return one character from stdin. Return -1 on error or if no data is available to be read.
 *
 * Parameters: none
 *
 * Returns: one charcter from stdin
 *
 */
int __sys_readc (void)
{
	uint8_t ch = 0;
	// If available, dequeue character from rxfifo
	if (cbfifo_length(rxfifo) > 0)
	{
		cbfifo_dequeue(&ch, ONE_BYTE, rxfifo);
		return (int)ch;
	}
	// Return -1 if no data to read
	return ERROR;
}
