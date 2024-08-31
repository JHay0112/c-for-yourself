# Makefile for C-for-yourself
#
# Author: J. L. Hay


include conf.mk
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
TEST_EXES := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.out))


.PHONY: tests
tests: $(TEST_EXES)


# Build test runners
$(BUILD_DIR)/$(TEST_DIR)/test_%.out: $(BUILD_DIR)/$(TEST_DIR)/test_%.o $(BUILD_DIR)/$(TEST_DIR)/test_%_Runner.o $(TEST_LIB_TARGETS) $(SRC_TARGETS)
	@echo CC $@
	@$(CC) $(CFLAGS) -o $@ $^

$(TEST_DIR)/test_%_Runner.c: $(TEST_DIR)/test_%.c
	@echo GEN $@
	@ruby $(TEST_LIB_DIR)/auto/generate_test_runner.rb $< $@

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