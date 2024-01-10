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
 * @file    cbfifo.c
 * @brief   The cbfifo implementation will allow cbfifo creation, with a size of 127 bytes which is statically allocated. 
 *
 *
 * @author  Trapti Damodar Balgi
 * @date    09/20/2023
 *
 */
#include "cbfifo.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>  //for memset

#define MIN_BUFFER_SIZE 0
#define ERROR (-1)
#define ZERO 0

/*Structure for circular buffer
*   buffer is the circular buffer where bytes will be enqueued and dequeued
*   size is the number of bytes of data currently in the CBFIFO
*   front is the position of the read pointer
*   rear is the position of the write pointer
*/
// Initialize the fifos
CircularBuffer_t txfifo_struct = { .buffer = {0}, .size = 0, .front = 0, .rear = 0};
CircularBuffer_t* txfifo = &txfifo_struct;
CircularBuffer_t rxfifo_struct = { .buffer = {0}, .size = 0, .front = 0, .rear = 0};
CircularBuffer_t* rxfifo = &rxfifo_struct;

size_t cbfifo_enqueue(void *buf, size_t nbyte, CircularBuffer_t* cbfifo)
{
    uint8_t added_bytes = 0;                //Number of bytes added to the buffer

    //Check for invalid values
    if ( (buf == NULL) || (cbfifo->size < ZERO) || (cbfifo->size > MAX_BUFFER_SIZE) || (cbfifo->front < ZERO) || (cbfifo->front > MAX_BUFFER_SIZE) || (cbfifo->rear < ZERO) || (cbfifo->rear > MAX_BUFFER_SIZE) )
    {
        return ( (size_t) ERROR);
    }
    
    //If max size reached or nbyte <= 0
    if ( (cbfifo->size == (MAX_BUFFER_SIZE)) || !(nbyte > ZERO) )
    {
        return (added_bytes);
    }

    uint8_t *int_buf = (uint8_t*)buf;       //typecasted to int pointer
    
    //while the cbfifo can still enqueue and bytes are yet to be added
    while( (cbfifo->size < MAX_BUFFER_SIZE) && (added_bytes < nbyte) && (added_bytes < MAX_BUFFER_SIZE) && (cbfifo->rear < MAX_BUFFER_SIZE) )
    {
            cbfifo->buffer[cbfifo->rear] = int_buf[added_bytes];                    //add data to the cbfifo
            cbfifo->rear = ( ((cbfifo->rear) + 1) == (MAX_BUFFER_SIZE)) ? 0 : ((cbfifo->rear) + 1);           //if rear is not 127, increment by 1, else make zero
            (cbfifo->size)++;   
            added_bytes++;
    }
    
    //If valid
    if( (cbfifo->size >= ZERO) && (cbfifo->size <= MAX_BUFFER_SIZE) && (cbfifo->front >= ZERO) && (cbfifo->front < MAX_BUFFER_SIZE) && (cbfifo->rear >= ZERO) && (cbfifo->rear < MAX_BUFFER_SIZE) )
        return added_bytes;
    else 
        return ZERO;

}

size_t cbfifo_dequeue(void *buf, size_t nbyte, CircularBuffer_t* cbfifo)
{
    uint8_t removed_bytes = 0;      //Number of bytes removed from the counter

    //Check for invalid values
    if ( (buf == NULL) || (cbfifo->size < ZERO) || (cbfifo->size > MAX_BUFFER_SIZE) || (cbfifo->front < ZERO) || (cbfifo->front > MAX_BUFFER_SIZE) || (cbfifo->rear < ZERO) || (cbfifo->rear > MAX_BUFFER_SIZE) )                        
    {
        return ( (size_t) ERROR);
    }
    
    //If min size reached or nbyte <= 0
    if ( ((cbfifo->size) == (MIN_BUFFER_SIZE)) || !(nbyte > ZERO) )
    {
        return 0;
    }
    
    uint8_t *int_buf = (uint8_t*)buf;

    //while the cbfifo can still dequeue and bytes are yet to be taken away
    while( (cbfifo->size > MIN_BUFFER_SIZE) && (removed_bytes < nbyte) && (removed_bytes < MAX_BUFFER_SIZE) && (cbfifo->front < MAX_BUFFER_SIZE) && (cbfifo->front < MAX_BUFFER_SIZE))
    {
        int_buf[removed_bytes] = cbfifo->buffer[cbfifo->front];
        cbfifo->buffer[cbfifo->front] = 0;       //Overwrite to 0
        cbfifo->front = ((cbfifo->front) + 1 == MAX_BUFFER_SIZE) ? 0 : ((cbfifo->front) + 1);           //if front is not 127, increment by 1, else make zero
        (cbfifo->size)--;
        removed_bytes++;
    }

    //If valid
    if( (cbfifo->size >= ZERO) && (cbfifo->size >= MIN_BUFFER_SIZE) && (cbfifo->front >= ZERO) && (cbfifo->front < MAX_BUFFER_SIZE) && (cbfifo->rear >= ZERO) && (cbfifo->rear < MAX_BUFFER_SIZE) )
        return removed_bytes;
    else 
        return ZERO;

}

size_t cbfifo_length (CircularBuffer_t* cbfifo)
{
    if ( cbfifo->size )           
        return cbfifo->size;
    else
        return ZERO;
}

size_t cbfifo_capacity (CircularBuffer_t* cbfifo)
{
    if (MAX_BUFFER_SIZE)
        return MAX_BUFFER_SIZE;
    else
        return ZERO;
}

void   cbfifo_reset (CircularBuffer_t* cbfifo)
{
    //If invalid buffer
    if (!cbfifo)
        return;
    memset(cbfifo->buffer, 0, sizeof(cbfifo->buffer));      //Reset all buffer values to 0
    cbfifo->size=0;                                         //Reset the size to zero
    cbfifo->front = 0;                                      //Reset the read pointer to 0
    cbfifo->rear = 0;                                       //Reset the write pointer to 0
    return;
}

#ifdef DEBUG
void cbfifo_print (CircularBuffer_t* cbfifo)
{
    size_t rear=0;
    printf("\nPrinting CBFIFO\n\n");
    for (size_t i=0; i<MAX_BUFFER_SIZE; i++)
    {
        printf("%lld -> || %d ||           ", i, cbfifo->buffer[rear]);
        rear++;
    }
    printf("\nFRONT INDEX %d\n",cbfifo->front);
    printf("\nREAR INDEX %d\n",cbfifo->rear);
    printf("\nPrinting Completed\n\n");
    return;
}
#endif
