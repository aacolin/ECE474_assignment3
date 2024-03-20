#ifndef TOP_MODULE_H
#define TOP_MODULE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "hardwareComponent.h"

using namespace std;

// Class representing the top module
class TopModule 
{
	private:

	public:
		// Member variables
		vector<HwComponent> modules;
		vector<Wire> inputs;
		vector<Wire> outputs;
		vector<Wire> wires;
		vector<Wire> registers;

		// Constructor
		TopModule();

		// Setter methods
		void setInputs(vector<Wire> inputs);
		void setOutputs(vector<Wire> outputs);
		void setWires(vector<Wire> wires);
		void setRegisters(vector<Wire> registers);
		void addModule(HwComponent module);

		// Search methods
		Wire* findInputWire(string wireName);
		Wire* findOutputWire(string wireName);
		Wire* findOutputRegister(string wireName);

		// Methods for writing Verilog
		void writeInputs(ofstream& circuitFile);
		void writeOutputs(ofstream& circuitFile);
		void writeWires(ofstream& circuitFile);
		void writeRegisters(ofstream& circuitFile);
		void addWire(Wire& wire);
		void writeModuleName(ofstream& circuitFile, string CircuitName);
		void writeModules(ofstream& circuitFile);
};

#endif // TOP_MODULE_H
