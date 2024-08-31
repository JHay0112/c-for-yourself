/**
 * Circular buffer implementation of the buffer interface.
 * 
 * Author: J. L. Hay
 */

#include <stdlib.h>
#include <string.h>

#include "buf.h"
#include "circ_buf.h"


typedef struct {
    buf_t buf; // Buffer abstraction layer
    uint8_t *mem; // Buffer memory
    uword_t windex;
    uword_t rindex;
    uword_t len;
    uword_t el_size;
} circ_buf_t;


static void circ_buf_write(struct buf_s *buf, const void *data);
static void circ_buf_read(struct buf_s *buf, void *data);
static void circ_buf_free(struct buf_s *buf);


buf_t *circ_buf_init(uword_t len, uword_t el_size)
{
    // Setup buffer
    circ_buf_t *buf = (circ_buf_t *) calloc(1, sizeof(circ_buf_t));

    // Allocate memory to the buffer
    buf->mem = (uint8_t *) calloc(len, el_size);
    buf->windex = 0;
    buf->rindex = 0;
    buf->len = len;
    buf->el_size = el_size;

    // Allocate functions
    buf->buf.write = circ_buf_write;
    buf->buf.read = circ_buf_read;
    buf->buf.free = circ_buf_free;

    return (buf_t *) buf;
}


void circ_buf_write(struct buf_s *buf_p, const void *data)
{
    circ_buf_t *buf = (circ_buf_t *) buf_p;
    
    // Calculate starting location in buffer
    uword_t loc = buf->el_size * buf->windex;

    // Copy value into buffer
    memcpy(&(buf->mem[loc]), data, buf->el_size);
    
    // Increment reading position
    buf->windex++;
    if (buf->windex >= buf->len)
    {
        buf->windex = 0;
    }
}

void circ_buf_read(struct buf_s *buf_p, void *data)
{
    circ_buf_t *buf = (circ_buf_t *) buf_p;
    
    // Calculate starting location in buffer
    uword_t loc = buf->el_size * buf->rindex;

    // Copy out value from buffer
    memcpy(data, &(buf->mem[loc]), buf->el_size);
    
    // Increment reading position
    buf->rindex++;
    if (buf->rindex >= buf->len)
    {
        buf->rindex = 0;
    }
}

void circ_buf_free(struct buf_s *buf_p)
{
    circ_buf_t *buf = (circ_buf_t *) buf_p;

    free(buf->mem);
    free(buf);
}
