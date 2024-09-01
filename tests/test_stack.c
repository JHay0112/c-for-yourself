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


static buf_t *stack;


// Test cases

void test_stack_empty_stack_reads_zero(void)
{
    EL_TYPE data = 32;

    buf_read(stack, (void *) &data);

    TEST_ASSERT_EQUAL(0, data);
}

void test_stack_is_filo(void)
{
    EL_TYPE write_val = 32;
    EL_TYPE read_val = 21;

    buf_write(stack, (void *) &write_val);
    buf_read(stack, (void *) &read_val);

    TEST_ASSERT_EQUAL(write_val, read_val);
}


// Test framework setup and tear down

void setUp(void)
{
    stack = stack_init(BUF_LEN, EL_SIZE);
}


void tearDown(void)
{
    buf_free(stack);
}