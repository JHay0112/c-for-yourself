/**
 * Circular buffer implementation of the 
 */

#include <stdlib.h>

#include "buf.h"
#include "circ_buf.h"


typedef struct {
    buf_t buf; // Buffer abstraction layer
    void *mem; // Buffer memory
} circ_buf_t;


buf_t *circ_buf_init(word_t len, word_t el_size)
{
    // Setup buffer
    circ_buf_t *buf = (circ_buf_t *) calloc(1, sizeof(circ_buf_t));

    // Allocate memory to the buffer
    buf->mem = calloc(len, el_size);

    return (buf_t *) buf;
}
