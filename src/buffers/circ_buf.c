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


static void circ_buf_write(struct buf_s *buf, const void *data);
static void circ_buf_read(struct buf_s *buf, void *data);
static void circ_buf_free(struct buf_s *buf);


buf_t *circ_buf_init(word_t len, word_t el_size)
{
    // Setup buffer
    circ_buf_t *buf = (circ_buf_t *) calloc(1, sizeof(circ_buf_t));

    // Allocate memory to the buffer
    buf->mem = calloc(len, el_size);

    // Allocate functions
    buf->buf.write = circ_buf_write;
    buf->buf.read = circ_buf_read;
    buf->buf.free = circ_buf_free;

    return (buf_t *) buf;
}


void circ_buf_write(struct buf_s *buf, const void *data)
{

}

void circ_buf_read(struct buf_s *buf, void *data)
{

}

void circ_buf_free(struct buf_s *buf)
{

}
