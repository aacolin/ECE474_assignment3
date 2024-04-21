#ifndef CIRCUIT_PARSER_H  // Header guard to prevent multiple inclusion
#define CIRCUIT_PARSER_H

#include <iostream>  // Standard input/output stream objects
#include <sstream>   // String stream classes
#include <string>    // String types and functions
#include <vector>    // Dynamic array-like container
#include "circuitParser.h"   // Header file for circuit parser
#include "hardwareComponent.h"  // Header file for hardware components
#include "topModule.h"    // Header file for top module

#define INPUT "input"   // Macro definition for input type
#define OUTPUT "output" // Macro definition for output type
#define WIRE "wire"     // Macro definition for wire type
#define REGISTER "register" // Macro definition for register type
#define COMMENT "//"       // Macro definition for comment indicator
#define EMPTY "\0"         // Macro definition for empty character
#define ADD "+"            // Macro definition for addition operator
#define SUB "-"            // Macro definition for subtraction operator
#define MUL "*"            // Macro definition for multiplication operator
#define GT ">"             // Macro definition for greater than operator
#define LT "<"             // Macro definition for less than operator
#define EQ	"=="           // Macro definition for equality operator
#define SEL "?"            // Macro definition for selector operator
#define SHR ">>"           // Macro definition for right shift operator
#define SHL "<<"           // Macro definition for left shift operator
#define REG ""             // Macro definition for register type (empty)
#define ERROR "ERROR"      // Macro definition for error indicator

using namespace std;  // Using the standard namespace for convenience

class CircuitParser
{
private:

// static methods can be called without needing to create an instance of the class.
public:
    // Static method to parse a line of code and update the top module accordingly
    static int parseLine(string line, TopModule *topModule);
    
    // Static method to parse input string and return vector of wires
    static vector<Wire> parseInput(string inputString);
    
    // Static method to parse output string and return vector of wires
    static vector<Wire> parseOutput(string outputString);
    
    // Static method to parse wire string and return vector of wires
    static vector<Wire> parseWire(string wireString);
    
    // Static method to parse register string and return vector of wires
    static vector<Wire> parseRegister(string registerString);
    
    // Static method to parse operation string and return hardware component
    static HwComponent parseOperation(string operationString, TopModule &topModule);
};

#endif  // End of header guard

/*
Note:
The purpose of using static methods in the CircuitParser class is to have utility methods 
that can be called without needing to create an instance of the class. 

Utility Functions:  The methods in the CircuitParser class perform specific tasks 
                    related to parsing input strings and generating hardware components. 
                    These methods don't require access to instance-specific data, 
                    so they can be declared as static.

Avoiding Object Creation: Since static methods belong to the class itself rather 
                    than instances of the class, they can be called directly using 
                    the class name (CircuitParser::methodName()) without needing 
                    to create an object of the class. This can be convenient when 
                    you just need to perform a specific task without needing to 
                    maintain state across multiple method calls.

Encapsulation:      By grouping related utility functions under the CircuitParser class, 
                    it helps organize the code and keep related functionality together. 
                    This can improve code readability and maintainability.

Ease of Use:        Static methods provide a clear interface for interacting with the 
                    functionality provided by the CircuitParser class. Users of the 
                    class can easily understand which methods are available and what 
                    tasks they perform.
*/