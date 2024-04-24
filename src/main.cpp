#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "circuitParser.h"
#include <cmath> 
#include "argumentChecker.h"
#include "verilog.h"

using namespace std;

int main(int argc, char* argv[])
{
    
	ArgumentChecker checker(argc, argv);                // Instantiate the argument checker
    if (!checker.checkArguments()) { return 0; }        // Check if the arguments are valid
    int latency = checker.getLatency();                 // Get the latency if it is correct
	vector<string> circuits = { argv[1] };              // get netlist file
    Verilog verilog(argv[1], latency, argv[3]);         // Instantiate the Verilog class
    
    for (const string& circuitName : circuits) {        // Process the netlist file
        
        if (!Verilog::processCircuit(circuitName, latency, argv[3])) {
            return 1;
        }
    }
    return 0;
}

