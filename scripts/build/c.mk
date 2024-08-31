# Makefile for C files common to the entire library.
#
# Author: J. L. Hay

ifndef C_MK_INCLUDED
C_MK_INCLUDED = 1


include conf.mk


# Compiler information
CC := gcc
CFLAGS := -Wall -Werror -MD $(addprefix -I, $(INC_DIRS))


# Generic C rules
$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	@echo CC $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.d: $(BUILD_DIR)/%.o


endif