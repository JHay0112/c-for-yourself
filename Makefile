# Makefile for C-for-yourself
#
# Author: J. L. Hay


include scripts/build/c.mk
include scripts/build/test.mk


# Sources
SRC_DIRS := $(dir $(shell find $(SRC_DIR) -name '*.c'))
SRC_SRCS := $(wildcard $(addsuffix *.c, $(SRC_DIRS)))
SRC_DEPS := $(addprefix $(BUILD_DIR)/, $(SRC_SRCS:.c=.d))
SRC_TARGETS := $(addprefix $(BUILD_DIR)/, $(SRC_SRCS:.c=.o))

LIB_DIRS := $(dir $(shell find $(LIB_DIR) -name '*.c'))


# Build directory
$(BUILD_DIR):
	@echo MKDIR $(BUILD_DIR)
	@mkdir -p $(addprefix $(BUILD_DIR)/, $(SRC_DIRS)) 
	@mkdir -p $(addprefix $(BUILD_DIR)/, $(LIB_DIRS)) 
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)

# Cleanup
.PHONY: clean
clean: | $(BUILD_DIR)
	@echo RM $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)


# Dependencies
-include $(SRC_DEPS)
-include $(TEST_DEPS)