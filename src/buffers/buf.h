/**
 * A type and implementation independent buffer interface.
 * 
 * Author: J. L. Hay
 */

#ifndef BUFFERS_BUF_H_INCLUDED
#define BUFFERS_BUF_H_INCLUDED

#include "../conf.h"


typedef uword_t buf_len_t;
typedef uword_t buf_item_size_t;


/**
 * Buffer interface type. (struct)
 * All buffers must implement this interface to be used with the buffer abstraction layer.
 * 
 * See the corresponding buffer functions to see the behaviour the function pointers should 
 * implement.
 */
typedef struct buf_s {
    void (*write)(struct buf_s *buf, const void *data);
    void (*read)(struct buf_s *buf, void *data);
    void (*free)(struct buf_s *buf);
} buf_t;


/**
 * Writes a specified piece of data to the buffer. All buffers must implement this with memory copy
 * rather than using the passed pointer. This policy is implemented to avoid memory leaks.
 * 
 * Parameters
 * ----------
 * 
 * buf_t *buf: Pointer to the buffer to manipulate.
 * const void *data: Pointer to the data to be added to the buffer.
 * 
 * Returns
 * -------
 * 
 * void
 */
void buf_write(buf_t *buf, const void *data)
{
    return buf->write(buf, data);
}


/**
 * Reads a piece of data from the buffer.
 * 
 * Parameters
 * ----------
 * 
 * buf_t *buf: Pointer to the buffer to manipulate.
 * void *data: Pointer to the memory to copy the data into.
 * 
 * Returns
 * -------
 * 
 * void
 */
void buf_read(buf_t *buf, void *data)
{
    return buf->read(buf, data);
}


/**
 * Frees the buffer.
 * 
 * Parameters
 * ----------
 * 
 * buf_t *buf: Pointer to the buffer to manipulate.
 * 
 * Returns
 * -------
 * 
 * void
 */
void buf_free(buf_t *buf)
{
    return buf->free(buf);
}

#endif 