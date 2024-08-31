/**
 * Stack implementation of the buffer interface.
 * 
 * Author: J. L. Hay
 */
#ifndef BUFFERS_STACK_H_INCLUDED
#define BUFFERS_STACK_H_INCLUDED

#include "../conf.h"
#include "buf.h"


/**
 * Dynamically initialises a stack of the specified len and element sized.
 * 
 * Parameters
 * ----------
 * 
 * word_t len: The number of elements in the buffer.
 * word_t el_size: The size of the elements in bytes.
 */
buf_t *stack_init(uword_t len, uword_t el_size);


#endif