/**
 * @file argumentChecker.cpp
 * @brief This file defines the ArgumentChecker class, which is responsible for checking the validity of the command-line arguments.
*/

#include "argumentChecker.h"
using namespace std;

/**
 * @brief Constructs an ArgumentChecker object.
 * 
 * This constructor initializes an ArgumentChecker object with the given command-line arguments. 
 * The ArgumentChecker object can be used to validate and process these arguments.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
ArgumentChecker::ArgumentChecker(int argc, char* argv[]) : argc(argc), argv(argv) {}

/**
 * @brief Checks the validity of the command-line arguments.
 * 
 * This function checks if the correct number of arguments has been provided and if the latency argument is a valid integer.
 * If the arguments are not valid, it prints an error message and returns false. If the arguments are valid, it returns true.
 * 
 * @return A boolean indicating whether the arguments are valid.
 */
bool ArgumentChecker::checkArguments() {
    if (argc != 4) {
        cout << "    Error: The number of input arguments provided is incorrect.\n" << endl
            << "    Usage: hlsyn <cFile> <latency> <verilogFile>\n" << endl
            << "        <cFile>       : Netlist file to convert." << endl
            << "        <latency>     : Scheduling duration constrain." << endl
            << "        <verilogFile> : Output Verilog file." << endl;
        return false;
    }

    try {
        latency = stoi(argv[2]);
    }
    catch (invalid_argument&) {
        cout << "Invalid input: Expected an integer value for latency, but received: " << argv[2] << endl;
        return false;
    }

    return true;
}

/**
 * @brief Returns the latency argument.
 * 
 * This function returns the latency argument provided in the command-line arguments.
 * 
 * @return The latency argument.
 */
int ArgumentChecker::getLatency() const {
    return latency;
}

