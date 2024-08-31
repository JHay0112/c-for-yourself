/**
 * Circular buffer implementation of the buffer interface.
 * 
 * Author: J. L. Hay
 */
#ifndef BUFFERS_CIRC_BUF_H_INCLUDED
#define BUFFERS_CIRC_BUF_H_INCLUDED

#include "../conf.h"
#include "buf.h"


/**
 * Dynamically initialises a circular buffer of the specified len and element sized.
 * 
 * Parameters
 * ----------
 * 
 * word_t len: The number of elements in the buffer.
 * word_t el_size: The size of the elements in bytes.
 */
buf_t *circ_buf_init(word_t len, word_t el_size);


#endif 