#!/bin/bash

# This script tests circuits and error files using dpgen.

# Define paths and commands
DPGEN=$(pwd)/build/src/./dpgen
CIRCUITS_PATH=$(pwd)/circuits
CLEAR_SCREEN="clear"

# Check if dpgen does NOT exist
if [[ ! -x "$DPGEN" ]]; then
    # Build dpgen
    mkdir -p build && cd build && cmake .. && make && cd ..
    echo "----------------------------------------------" 
    echo "dpgen built successfully, executing script ..." && sleep 3
    
    # Check again if dpgen exists
    if [[ ! -x "$DPGEN" ]]; then
        echo "Error: dpgen not found in $(pwd)/build/src"
        exit 1
    fi
fi

# Function to test circuits
test_circuit() {
    local FILE_NAME=$1
    echo ""
    echo "-----------------------------------------------------------------"
    echo "Testing circuit file: $FILE_NAME"
    echo ""
    $DPGEN "$CIRCUITS_PATH/$FILE_NAME" "$FILE_NAME.v" && cat "$FILE_NAME.v"
}

# Function to test error files
test_error() {
    local FILE_NAME=$1
    echo ""
    echo "-----------------------------------------------------------------"
    echo "Testing error file $FILE_NAME"
    echo ""
    $DPGEN "$CIRCUITS_PATH/$FILE_NAME" "$FILE_NAME.v"
}

# Clear screen
$CLEAR_SCREEN

# Testing circuits 1-4
test_circuit "474a_circuit1.txt"
test_circuit "474a_circuit2.txt"
test_circuit "474a_circuit3.txt"
test_circuit "474a_circuit4.txt"

# Testing mixed circuits 1-3
test_circuit "mixedcircuit1.txt"
test_circuit "mixedcircuit2.txt"
test_circuit "mixedcircuit3.txt"

# Testing unsigned circuits 1-3
test_circuit "ucircuit1.txt"
test_circuit "ucircuit2.txt"
test_circuit "ucircuit3.txt"

# Test error files
test_error "error1.txt"
test_error "error2.txt"
test_error "error3.txt"
test_error "error4.txt"

# Clean up
rm $(pwd)/{474a_circuit*,mixedcircuit*,ucircuit*}.v
rm -fr $(pwd)/build
