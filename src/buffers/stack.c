/**
 * Stack implementation of the buffer interface.
 * 
 * Author: J. L. Hay
 */

#include <stdlib.h>
#include <string.h>

#include "buf.h"
#include "stack.h"


typedef struct {
    buf_t buf; // Buffer abstraction layer
    uint8_t *mem; // Buffer memory
    uword_t pos;
    uword_t len;
    uword_t el_size;
} stack_t;


static void stack_write(buf_t *buf, const void *data);
static void stack_read(buf_t *buf, void *data);
static void stack_free(buf_t *buf);


buf_t *stack_init(uword_t len, uword_t el_size)
{
    // Setup buffer
    stack_t *buf = (stack_t *) calloc(1, sizeof(stack_t));

    // Allocate memory to the buffer
    buf->mem = (uint8_t *) calloc(len, el_size);
    buf->pos = 0;
    buf->len = len;
    buf->el_size = el_size;

    // Allocate functions
    buf->buf.write = stack_write;
    buf->buf.read = stack_read;
    buf->buf.free = stack_free;

    return (buf_t *) buf;
}


void stack_write(buf_t *buf_p, const void *data)
{
    stack_t *stack = (stack_t *) buf_p;

    // Copy data from pointer into stack
    memcpy(&(stack->mem[stack->pos * stack->el_size]), data, stack->el_size);

    // Update position
    if (stack->pos < stack->len)
    {
        stack->pos += 1;
    }
}

void stack_read(buf_t *buf_p, void *data)
{
    stack_t *stack = (stack_t *) buf_p;

    // Update position
    if (stack->pos > 0)
    {
        stack->pos -= 1;
    }

    // Copy data from stack into pointer
    memcpy(data, &(stack->mem[stack->pos * stack->el_size]), stack->el_size);
}

void stack_free(buf_t *buf_p)
{
    stack_t *stack = (stack_t *) buf_p;

    free(stack->mem);
    free(stack);
}