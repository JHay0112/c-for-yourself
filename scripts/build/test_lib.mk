# Makefile for the test library.
# Provides the target: test_lib
#
# Author: J. L. Hay

ifndef TEST_LIB_MK_INCLUDED
TEST_LIB_MK_INCLUDED = 1


include conf.mk 
include scripts/build/c.mk


# Test library
TEST_LIB_DIR := $(LIB_DIR)/unity
TEST_LIB_SRCS := $(wildcard $(TEST_LIB_DIR)/src/*.c)
TEST_LIB_INCS := $(wildcard $(TEST_LIB_DIR)/src/*.h)
TEST_LIB_DEPS := $(addprefix $(BUILD_DIR)/, $(TEST_LIB_SRCS:.c=.d))
TEST_LIB_TARGETS := $(addprefix $(BUILD_DIR)/, $(TEST_LIB_SRCS:.c=.o))


.PHONY: test_lib
test_lib: $(BUILD_DIR)/$(TEST_LIB)

$(BUILD_DIR)/$(TEST_LIB): $(TEST_LIB_TARGETS) $(BUILD_DIR)


# Test library dependencies
-include $(TEST_LIB_DEPS)

endif