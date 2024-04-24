/**
 * @file circuitParser.h
 * @brief This file defines the Parser class, which is responsible for parsing the netlist file 
 * and extracting the necessary information to build the circuit.
*/


# ifndef CIRCUITPARSER_H
# define CIRCUITPARSER_H

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "hardwareComponent.h"
#include "topModule.h"

#define INPUT "input"
#define OUTPUT "output"
#define WIRE "wire"
#define REGISTER "register"
#define VARIABLE "variable"
#define IF "if"
#define ELSE "else"
#define COMMENT "//"
#define EMPTY "\0"
#define ADD "+"
#define SUB "-"
#define MUL "*"
#define GT ">"
#define LT "<"
#define EQ	"=="
#define SEL "?"
#define SHR ">>"
#define SHL "<<"
#define DIV "/"
#define MOD "%"
#define REG ""
#define ERROR "ERROR"


// Use the standard namespace
using namespace std;

/**
 * @brief The Parser class is responsible for parsing the netlist file and extracting the necessary information
 * to build the circuit.
*/

// Define the Parser class
class Parser
{
	private:

	public:
		static int parseLine(string line, TopModule *topModule);							// Parse a line of the netlist file				
		static vector<Wire> parseInput(string inputString);									// Parse an input line
		static vector<Wire> parseOutput(string outputString);								// Parse an output line
		static vector<Wire> parseWire(string wireString);									// Parse a wire line
		static vector<Wire> parseRegister(string registerString);							// Parse a register line
		static HwComponent* parseOperation(string operationString, TopModule &topModule);	// Parse an operation line
		static int parseContent(vector<string> line, TopModule * topModule );				// Parse the content of the netlist file
		static int ifFinder(int index, vector<string>& lines, TopModule * topModule);		// Find the if statement

};

# endif // PARSER_H
