/**
 * Tests for the circular buffer.
 * 
 * Author: J. L. Hay
 */


#include "unity.h"
#include "buffers/buf.h"
#include "buffers/circ_buf.h"


#define BUF_LEN 10
#define EL_TYPE uint8_t 
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


// Test framework setup and tear down

void setUp(void)
{
    buf = circ_buf_init(BUF_LEN, EL_SIZE);
}


void tearDown(void)
{
    buf_free(buf);
}