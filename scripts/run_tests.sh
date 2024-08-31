#!/bin/bash

# Test runner
#
# Author: J. L. Hay

BUILD_DIR=build
TEST_DIR=tests
TEST_EXT=out

# Setup test programs
make tests

# Find test programs
tests=$(find $BUILD_DIR/$TEST_DIR/ -name "*.$TEST_EXT" -type f)

chmod +x $tests
$tests