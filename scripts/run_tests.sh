#!/bin/bash

# Test runner
#
# Author: J. L. Hay

TEST_DIR=build/tests
TEST_LIB_DIR=lib/unity
RESULT_DIR=results

TEST_EXT=out
RESULT_EXT=result
PASS_EXT=testpass
FAIL_EXT=testfail

SUMMARY_FILE=${RESULT_DIR}/results.summary

PASS="PASS"
FAIL="FAIL"
IGNORE="IGNORE"


# Remove old results
rm -rf ${RESULT_DIR}


# Setup test summary file
mkdir -p ${RESULT_DIR}
> ${SUMMARY_FILE}


# Find test programs and execute
tests=$(find ${TEST_DIR} -name "*.${TEST_EXT}" -type f)
chmod +x $tests
for test in $tests 
do
    test_file=${test%.${TEST_EXT}}

    echo > ${test_file}.${RESULT_EXT}
    echo ${test_file} >> ${test_file}.${RESULT_EXT}
    ${test} >> ${test_file}.${RESULT_EXT}

    cat ${test_file}.${RESULT_EXT} >> ${SUMMARY_FILE}

    # Convert extension to pass or fail
    if grep -q -e ${FAIL} -e ${IGNORE} ${test_file}.${RESULT_EXT}
    then
        mv ${test_file}.${RESULT_EXT} ${test_file}.${FAIL_EXT}
    else
        mv ${test_file}.${RESULT_EXT} ${test_file}.${PASS_EXT}
    fi
done


# Move results into the results directory
results=$(find ${TEST_DIR} -name "*.${PASS_EXT}" -o -name "*.${FAIL_EXT}" -type f)
mv ${results} ${RESULT_DIR}

# Summarise the results
ruby ${TEST_LIB_DIR}/auto/unity_test_summary.rb ${RESULT_DIR} >> ${SUMMARY_FILE}
cat ${SUMMARY_FILE}


# Determine exit status from number of failures
exit $(find . -name "*.${FAIL_EXT}" | wc -l)