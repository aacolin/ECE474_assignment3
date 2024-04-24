/**
 * @file verilog.h
 * @brief This file defines the Verilog class, which is responsible for generating the Verilog output file.
 * 
 * The Verilog class is responsible for processing the circuit and generating the Verilog output file.
 * It reads the netlist file, parses the content, calculates the minimum latency, forces the schedule for each module,
 * and creates the output file.
 * 
*/

#ifndef VERILOG_H
#define VERILOG_H

#include "circuitParser.h"
#include <cmath> 

using namespace std;

class Verilog
{

public:
    Verilog(const string& circuitName, int latency, const string& outputFileName);
    static bool processCircuit(const string& circuitName, int latency, const string& outputFileName);
    static vector<string> readNetlist(string fileName);
    static void writeToFile(string circuitName, TopModule *topModule);
    static void makeOutputFile(string circuitName, TopModule *topModule) ;

private:
   
    string circuitName;
    int latency;
    string outputFileName;

};


#endif