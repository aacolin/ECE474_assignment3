#!/bin/zsh

# This is a simple test script for the hlsyn binary

# Compiling the hlsyn binary
working_dir=$(pwd)
rm -fr $working_dir/build
clear
echo "Compiling hlsyn binary..."
mkdir -p build
cd build
cmake ..
make
cp $working_dir/build/src/hlsyn $working_dir/testing/hlsyn 
rm -r $working_dir/testing/*.v


# Running tests

echo "|-------------------------------------------------------------|"
echo "|                     Running tests                           |"              
echo "|-------------------------------------------------------------|"
cd $working_dir/testing

# Test 1
# hlsyn with no arguments
output=$(./hlsyn)
expected_output="    Error: The number of input arguments provided is incorrect.

    Usage: hlsyn <cFile> <latency> <verilogFile>

        <cFile>       : Netlist file to convert.
        <latency>     : Scheduling duration constrain.
        <verilogFile> : Output Verilog file."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 1: hlsyn with no arguments                  |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 1: hlsyn with no arguments                  |  \e[31mFAILED\e[0m  |"
    echo -e "| Test 1 Error : output != expected_output                               |\n"
    diff <(echo "$output") <(echo "$expected_output")
fi


# Test 2
# hlsyn with 1 argument (cFile)
output=$(./hlsyn error1.c)
expected_output="    Error: The number of input arguments provided is incorrect.

    Usage: hlsyn <cFile> <latency> <verilogFile>

        <cFile>       : Netlist file to convert.
        <latency>     : Scheduling duration constrain.
        <verilogFile> : Output Verilog file."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 2: hlsyn with 1 arguments                   |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 2 Error : output != expected_output                               |\n"
    diff <(echo "$output") <(echo "$expected_output")
fi


# Test 3
# hlsyn with 2 arguments (cFile, latency)
output=$(./hlsyn error1.c 10)
expected_output="    Error: The number of input arguments provided is incorrect.

    Usage: hlsyn <cFile> <latency> <verilogFile>

        <cFile>       : Netlist file to convert.
        <latency>     : Scheduling duration constrain.
        <verilogFile> : Output Verilog file."

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 3: hlsyn with 2 arguments                   |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 3: Error : output != expected_output        |  \e[31mFAILED\e[0m  |"
    diff <(echo "$output") <(echo "$expected_output")
fi

# Test 3a
# # hlsyn with 3 arguments (cFile, latency (invalid, not a number), verilogFile)
output=$(./hlsyn error1.c q10 error1.v)
expected_output="Invalid input: Expected an integer value for latency, but received: q10" ;

if [ "$output" = "$expected_output" ]; then
    echo -e "| Test 3b: hlsyn with invalid latency              |  \e[32mPASSED\e[0m  |"
else
    echo -e "| Test 3b: Error output != expected_output         |  \e[31mFAILED\e[0m  |"
    echo -e "| Test 3b Error : output != expected_output                              |\n"
    diff <(echo "$output") <(echo "$expected_output")
fi

# Test 4
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error1.c)
output=$(./hlsyn error1.c 10 error1.v)
expected_output="Error parsing file. Check the netlist file for errors."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 4: hlsyn error test (error1.c)              |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 4: hlsyn error test (error1.c)              |  \e[31mFAILED\e[0m  |"
fi



# Test 5
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error2.c)
output=$(./hlsyn error2.c 10 error2.v)
expected_output="Error parsing file. Check the netlist file for errors."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 5: hlsyn error test (error2.c)              |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 5: hlsyn error test (error2.c)              |  \e[31mFAILED\e[0m  |"
fi


# Test 6
# hlsyn with 3 arguments (cFile, latency, verilogFile) and invalid netlist (error3.c)
output=$(./hlsyn error3.c 10 error3.v)
expected_output="Error parsing file. Check the netlist file for errors."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 6: hlsyn error test (error3.c)              |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 6: hlsyn error test (error3.c)              |  \e[31mFAILED\e[0m  |"
fi

# Test 6a
# hlsyn with 3 arguments (cFile, latency, verilogFile) empty netlist (error4.c)
output=$(./hlsyn error4.c 10 error4.v)
expected_output="Error: Unable to open the file 'error4.c'. 
Please ensure the file exists, is not in use by another program, and is not empty."
if [ "$output" = "$expected_output" ]; then
    echo "| Test 6a: hlsyn error test (error4.c)             |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 6a: Error : output != expected_output       |  \e[31mFAILED\e[0m  |"
    diff <(echo "$output") <(echo "$expected_output")
fi

# Test 7
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (test_if1.c)
./hlsyn test_if1.c 10 test_if1.v
diff test_if1.v test_if1.bm 
if [ $? -eq 0 ]; then
    echo "| Test 7: hlsyn if test (test_if1.c)               |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 7: test_if1.v and test_if1.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 8
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (test_if2.c)
./hlsyn test_if2.c 10 test_if2.v
diff test_if2.v test_if2.bm 
if [ $? -eq 0 ]; then
    echo "| Test 8: hlsyn if test (test_if2.c)               |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 8: test_if2.v and test_if2.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 9
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (test_if3.c)
./hlsyn test_if3.c 12 test_if3.v
diff test_if3.v test_if3.bm 
if [ $? -eq 0 ]; then
    echo "| Test 9: hlsyn if test (test_if3.c)               |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 9: test_if3.v and test_if3.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 10
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (test_if4.c)
./hlsyn test_if4.c 12 test_if4.v
diff test_if4.v test_if4.bm
if [ $? -eq 0 ]; then
    echo "| Test 10: hlsyn if test (test_if4.c)              |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 10: test_if4.v and test_if4.bm are different|  \e[31mFAILED\e[0m  |"
fi

# Test 11 Latency
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test1.c)
./hlsyn hls_lat_test1.c 8 hls_lat_test1.v
diff hls_lat_test1.v hls_lat_test1.bm
if [ $? -eq 0 ]; then
    echo "| Test 11: hlsyn latency (hls_lat_test1.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 11: hls_lat_test1.v and hls_lat_test1.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 12 Latency
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test2.c)
./hlsyn hls_lat_test2.c 8 hls_lat_test2.v
diff hls_lat_test2.v hls_lat_test2.bm
if [ $? -eq 0 ]; then
    echo "| Test 12: hlsyn latency (hls_lat_test2.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 12: hls_lat_test2.v and hls_lat_test2.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 13 Latency
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test3.c)
./hlsyn hls_lat_test3.c 8 hls_lat_test3.v
diff hls_lat_test3.v hls_lat_test3.bm
if [ $? -eq 0 ]; then
    echo "| Test 13: hlsyn latency (hls_lat_test3.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 13: hls_lat_test3.v and hls_lat_test3.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 14 Latency
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test4.c)
./hlsyn hls_lat_test4.c 8 hls_lat_test4.v
diff hls_lat_test4.v hls_lat_test4.bm
if [ $? -eq 0 ]; then
    echo "| Test 14: hlsyn latency (hls_lat_test4.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 14: hls_lat_test4.v and hls_lat_test4.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 15 Latency
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test5.c)
./hlsyn hls_lat_test5.c 8 hls_lat_test5.v
diff hls_lat_test5.v hls_lat_test5.bm
if [ $? -eq 0 ]; then
    echo "| Test 15: hlsyn latency (hls_lat_test5.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 15: hls_lat_test5.v and hls_lat_test5.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 16 Latency

# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_lat_test6.c)
./hlsyn hls_lat_test6.c 8 hls_lat_test6.v
diff hls_lat_test6.v hls_lat_test6.bm
if [ $? -eq 0 ]; then
    echo "| Test 16: hlsyn latency (hls_lat_test6.c)         |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 16: hls_lat_test6.v and hls_lat_test6.bm are different |  \e[31mFAILED\e[0m  |"
fi


# Test 17 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test1.c)
./hlsyn hls_test1.c 10 hls_test1.v
diff hls_test1.v hls_test1.bm
if [ $? -eq 0 ]; then
    echo "| Test 17: hlsyn standard test (hls_test1.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 17: hls_test1.v and hls_test1.bm are different |  \e[31mFAILED\e[0m  |"
fi

# Test 18 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test2.c)
./hlsyn hls_test2.c 10 hls_test2.v
diff hls_test2.v hls_test2.bm
if [ $? -eq 0 ]; then
    echo "| Test 18: hlsyn standard test (hls_test2.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 18: hls_test2.v and hls_test2.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 19 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test3.c)
./hlsyn hls_test3.c 10 hls_test3.v
diff hls_test3.v hls_test3.bm
if [ $? -eq 0 ]; then
    echo "| Test 19: hlsyn standard test (hls_test3.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 19: hls_test3.v and hls_test3.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 20 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test4.c)
./hlsyn hls_test4.c 10 hls_test4.v
diff hls_test4.v hls_test4.bm
if [ $? -eq 0 ]; then
    echo "| Test 20: hlsyn standard test (hls_test4.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 20: hls_test4.v and hls_test4.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 21 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test5.c)
./hlsyn hls_test5.c 10 hls_test5.v
# diff hls_test5.v hls_test5.bm
if [ $? -eq 0 ]; then
    echo "| Test 21: hlsyn standard test (hls_test5.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 21: hls_test5.v and hls_test5.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 22 standard test (minimum latency = 34)
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test6.c)
./hlsyn hls_test6.c 34 hls_test6.v
diff hls_test6.v hls_test6.bm
if [ $? -eq 0 ]; then
    echo "| Test 22: hlsyn standard test (hls_test6.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 22: hls_test6.v and hls_test6.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 23 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test7.c)
./hlsyn hls_test7.c 10 hls_test7.v
diff hls_test7.v hls_test7.bm
if [ $? -eq 0 ]; then
    echo "| Test 23: hlsyn standard test (hls_test7.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 23: hls_test7.v and hls_test7.bm are different |  \e[31mFAILED\e[0m  |"
fi
# Test 24 standard test
# hlsyn with 3 arguments (cFile, latency, verilogFile) and valid netlist (hls_test8.c)
./hlsyn hls_test8.c 10 hls_test8.v
diff hls_test8.v hls_test8.bm
if [ $? -eq 0 ]; then
    echo "| Test 24: hlsyn standard test (hls_test8.c)       |  \e[32mPASSED\e[0m  |"
else
    echo "| Test 24: hls_test8.v and hls_test8.bm are different |  \e[31mFAILED\e[0m  |"
fi

echo "|-------------------------------------------------------------|\n"