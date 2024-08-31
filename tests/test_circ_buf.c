/**
 * Tests for the circular buffer.
 * 
 * Author: J. L. Hay
 */


#include "unity.h"
#include "buffers/buf.h"
#include "buffers/circ_buf.h"


#define BUF_LEN 10
#define EL_TYPE int16_t 
#define EL_SIZE sizeof(EL_TYPE)


static buf_t *buf;


// Test cases

void test_circ_buf_empty_buf_reads_zero(void)
{
    for (size_t i = 0; i < BUF_LEN; i++)
    {
        EL_TYPE el = 1;
        buf_read(buf, (void *) &el);
        TEST_ASSERT_EQUAL(0, el);
    }
}

void test_circ_buf_fifo(void)
{
    EL_TYPE write_val = 36;
    EL_TYPE read_val = 0;

    buf_write(buf, &write_val);
    buf_read(buf, &read_val);

    TEST_ASSERT_EQUAL(write_val, read_val);
}

void test_circ_buf_fifo_range(void)
{
    EL_TYPE write_val = 36;
    EL_TYPE read_val = 0;

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_write(buf, &write_val);
        buf_read(buf, &read_val);

        TEST_ASSERT_EQUAL(write_val, read_val);

        write_val++;
    }
}

void test_circ_buf_rindex_rollover(void)
{
    EL_TYPE write_val = 36;
    EL_TYPE read_val = 0;

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_write(buf, &write_val);
        buf_read(buf, &read_val);

        TEST_ASSERT_EQUAL(write_val, read_val);

        write_val++;
    }

    write_val -= BUF_LEN;

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_read(buf, &read_val);

        TEST_ASSERT_EQUAL(write_val, read_val);

        write_val++;
    }
}

void test_circ_buf_windex_rollover(void)
{
    EL_TYPE write_val = 36;
    EL_TYPE read_val = 0;

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_write(buf, &write_val);
        write_val++;
    }

    for (size_t i = 0; i < BUF_LEN; i++)
    {
        buf_write(buf, &write_val);
        buf_read(buf, &read_val);

        TEST_ASSERT_EQUAL(write_val, read_val);

        write_val++;
    }
}


// Test framework setup and tear down

void setUp(void)
{
    buf = circ_buf_init(BUF_LEN, EL_SIZE);
}


void tearDown(void)
{
    buf_free(buf);
}