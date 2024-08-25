# Makefile for C-for-yourself
#
# Author: J. L. Hay


include scripts/build/c.mk
include scripts/build/test_lib.mk


# Sources
SRC_DIRS := $(dir $(shell find $(SRC_DIR) -name '*.c'))
SRC_SRCS := $(wildcard $(addsuffix *.c, $(SRC_DIRS)))
SRC_DEPS := $(addprefix $(BUILD_DIR)/, $(SRC_SRCS:.c=.d))
SRC_TARGETS := $(addprefix $(BUILD_DIR)/, $(SRC_SRCS:.c=.o))

LIB_DIRS := $(dir $(shell find $(LIB_DIR) -name '*.c'))

TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)
TEST_DEPS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.d))
TEST_TARGETS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.o))


# Tests
.PHONY: test 
test: test_lib tests 

.PHONY: tests
tests: $(SRC_TARGETS)


# Build directory
$(BUILD_DIR):
	@echo Making $(BUILD_DIR)
	@mkdir -p $(addprefix $(BUILD_DIR)/, $(SRC_DIRS)) 
	@mkdir -p $(addprefix $(BUILD_DIR)/, $(LIB_DIRS)) 
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)

# Cleanup
.PHONY: clean
clean: | $(BUILD_DIR)
	@echo Removing $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)


# Dependencies
-include $(SRC_DEPS)
-include $(TEST_DEPS)