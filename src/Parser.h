#pragma once
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Parser.h"
#include "Module.h"
#include "IOWire.h"
#include "TopModule.h"

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


using namespace std;

class Parser
{
	private:

	public:
		static int parseLine(string line, TopModule *topModule, map<string, vector<double>> m);
		static vector<IOWire> parseInput(string inputString);
		static vector<IOWire> parseOutput(string outputString);
		static vector<IOWire> parseWire(string wireString);
		static vector<IOWire> parseRegister(string registerString);
		static Module* parseOperation(string operationString, TopModule &topModule, map<string, vector<double>> m);
		static int parseContent(vector<string> line, TopModule * topModule, map<string, vector<double>> m);
		static int ifFinder(int index, vector<string>& lines, TopModule * topModule, map<string, vector<double>> m);

};