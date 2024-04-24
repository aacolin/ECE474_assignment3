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