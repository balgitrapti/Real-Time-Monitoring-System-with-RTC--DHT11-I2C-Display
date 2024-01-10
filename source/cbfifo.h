/*******************************************************************************
 * Copyright (C) 2023 by Trapti Damodar Balgi
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Trapti Damodar Balgi and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/*
 * cbfifo.h - a fixed-size FIFO implemented via a circular buffer
 * 
 * Author: Howdy Pierce/Lalit Pandit
 * 
 * DO NOT EDIT THIS FILE: You should check this file into your repo
 * exactly as it was delivered to you.
 */

// Re-used from assignment 2 (Modified)

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>  // for size_t
#include <stdint.h>

#define MAX_BUFFER_SIZE (255)

/*Structure for circular buffer
*   buffer is the circular buffer where bytes will be enqueued and dequeued
*   size is the number of bytes of data currently in the CBFIFO
*   front is the position of the read pointer
*   rear is the position of the write pointer
*/
typedef struct CircularBuffer_s{
    int buffer[MAX_BUFFER_SIZE];
    uint8_t size;
    uint8_t front;
    uint8_t rear;
} CircularBuffer_t;

extern CircularBuffer_t* txfifo;
extern CircularBuffer_t* rxfifo;

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 *   of an error, returns (size_t) -1. For example, if the capacity is 30,
 *   and current lenght of FIFO is 0. A call to enqueue 35 bytes, will
 *   only enqueue 30 to the capacity and return 30 from this call. Application
 *   needs to retry enqueuing the remaining 5 bytes subsequently.
 * 
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte, CircularBuffer_t* cbfifo);


/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 * 
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 *   nbyte(inclusive of both). 
 * 
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte, CircularBuffer_t* cbfifo);


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(CircularBuffer_t* cbfifo);


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity(CircularBuffer_t* cbfifo);

/*
 * Resets the FIFO clearing all elements resulting in a 0 length. Basically,
 * the length of the FIFO goes to 0 after reset but capacity and max_capacity
 * stay intact.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Nothing
 */
void  cbfifo_reset(CircularBuffer_t* cbfifo);

#ifdef DEBUG
/*
 * Print function: Prints all the data in the FIFO
 *
 * Parameters: none
 * 
 * Returns: none
 */
void cbfifo_print(CircularBuffer_t* cbfifo);
#endif

// IGNORE FOLLOWING FUNCTIONS FOR ASSIGNMENT 2.
/*
 * Freezes the FIFO. Once FIFO is frozen, enqueue/dequeue operations will not
 * succeed. Instead, they will always return 0.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Nothing
 */
//void   cbfifo_freeze();

/*
 * Unfreezes the FIFO. Once FIFO is unfrozen, normal enqueue/dequeue operations can
 * be resumed.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   Nothing
 */
//void   cbfifo_unfreeze();

/*
 * Check the freeze status of the FIFO.
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   1 if FIFO is frozen, 0 otherwise.
 */
//int   cbfifo_frozen();


#endif // _CBFIFO_H_