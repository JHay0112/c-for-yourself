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

void test_stack_filo_range(void)
{
    EL_TYPE write_val = 21;
    EL_TYPE read_val = 0;

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        write_val++;
        buf_write(stack, (void *) &write_val);
    }

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_read(stack, (void *) &read_val);
        TEST_ASSERT_EQUAL(write_val, read_val);
        write_val--;
    }
}

void test_stack_rejects_when_full(void)
{
    EL_TYPE write_val = 21;
    EL_TYPE read_val = 0;

    for (size_t i = 0; i < BUF_LEN+ 1; i++)
    {
        write_val++;
        buf_write(stack, (void *) &write_val);
    }

    write_val--;
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