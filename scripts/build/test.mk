# Makefile for testing
# Provides the targets: test tests
#
# Author: J. L. Hay

ifndef TEST_MK_INCLUDED
TEST_MK_INCLUDED = 1


include conf.mk
include scripts/build/c.mk
include scripts/build/test_lib.mk


TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)
TEST_DEPS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.d))
TEST_TARGETS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.o))
TEST_EXES := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.c=.out))


# Tests
.PHONY: test 
test: tests 
	@chmod +x $(TEST_EXES)
	$(foreach test, $(TEST_EXES), @echo TEST $(notdir $(test:_Runner=)) && $(test);)


.PHONY: tests
tests: $(TEST_EXES)


# Build test runners
$(BUILD_DIR)/$(TEST_DIR)/test_%.out: $(BUILD_DIR)/$(TEST_DIR)/test_%.o $(BUILD_DIR)/$(TEST_DIR)/test_%_Runner.o $(TEST_LIB_TARGETS)
	@echo CC $@
	@$(CC) $(CFLAGS) -o $@ $^

$(TEST_DIR)/test_%_Runner.c: $(TEST_DIR)/test_%.c
	@echo GEN $@
	@ruby $(TEST_LIB_DIR)/auto/generate_test_runner.rb $< $@


endif