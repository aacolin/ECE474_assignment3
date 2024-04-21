#!/bin/zsh

# This is a simple test script for the hlsyn binary

# Compiling

echo "Compiling hlsyn"
sleep 1
working_dir=$(pwd)
clear
rm -fr $working_dir/build
echo "Test 1: Running hlsyn with no arguments"
mkdir -p build && cd build && cmake .. && make
echo "Compilation done"
sleep 1
clear
echo "Moving hlsyn binary to testing directory"
cp $working_dir/build/src/hlsyn $working_dir/testing/hlsyn 

clear
# Running tests
echo "|-------------------------------------------------------------|"
echo "|                     Running tests                           |"              
echo "|-------------------------------------------------------------|"
cd $working_dir/testing

# Test 1
# hlsyn with no arguments
output=$(./hlsyn)
expected_output="Error, incorrect number of input arguments.

Syntax:  hlsyn cFile latency verilogFile

  cFile       : The path to the netlist you wish to convert.
  latency     : How long the graph has to be scheduled.
  verilogFile : The path to for the output verilogFile."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 1: hlsyn with no arguments                  |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 1: hlsyn with no arguments                  |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 2
# hlsyn with 1 argument (cFile)
output=$(./hlsyn error1.c)
expected_output="Error, incorrect number of input arguments.

Syntax:  hlsyn cFile latency verilogFile

  cFile       : The path to the netlist you wish to convert.
  latency     : How long the graph has to be scheduled.
  verilogFile : The path to for the output verilogFile."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 2: hlsyn with 1 arguments                   |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 2: hlsyn with 1 arguments                   |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 3
# hlsyn with 2 arguments (cFile, latency)
output=$(./hlsyn error1.c 10)
expected_output="Error, incorrect number of input arguments.

Syntax:  hlsyn cFile latency verilogFile

  cFile       : The path to the netlist you wish to convert.
  latency     : How long the graph has to be scheduled.
  verilogFile : The path to for the output verilogFile."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 3: hlsyn with 2 arguments                   |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 3: hlsyn with 2 arguments                   |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 4
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error1.c)
output=$(./hlsyn error1.c 10 error1.v)
expected_output="Error in parseLine
Error: Couldn't parse a line. Check the netlist for errors. Exiting."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 4: hlsyn with invalid netlist (error1.c)    |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 4: hlsyn with invalid netlist (error1.c)    |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 5
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error2.c)
output=$(./hlsyn error2.c 10 error2.v)
expected_output="Error in parseLine
Error: Couldn't parse a line. Check the netlist for errors. Exiting."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 5: hlsyn with invalid netlist (error2.c)    |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 5: hlsyn with invalid netlist (error2.c)    |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 6
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error3.c)
output=$(./hlsyn error3.c 10 error3.v)
expected_output="Error in parseLine
Error: Couldn't parse a line. Check the netlist for errors. Exiting."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 6: hlsyn with invalid netlist (error3.c)    |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 6: hlsyn with invalid netlist (error3.c)    |  \e[31mFAILED\e[0m  |"
fi
sleep 1

# Test 7
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (test_if1.c)

output=$(./hlsyn test_if1.c 10 test_if1.v)
expected_output="Critical Path : 22.619 ns"
if [ "$output" = "$expected_output" ]; then
    echo "| Test 7: hlsyn with valid netlist (test_if1.c)    |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 7: hlsyn with valid netlist (test_if1.c)    |  \e[31mFAILED\e[0m  |"
fi
sleep 1
