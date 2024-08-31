/**
 * Tests for the stack implementation.
 * 
 * Author: J. L. Hay
 */


#include "unity.h"
#include "buffers/buf.h"
#include "buffers/stack.h"


#define BUF_LEN 10
#define EL_TYPE int16_t 
#define EL_SIZE sizeof(EL_TYPE)


static buf_t *buf;


// Test cases



// Test framework setup and tear down

void setUp(void)
{
    buf = stack_init(BUF_LEN, EL_SIZE);
}


void tearDown(void)
{
    buf_free(buf);
}