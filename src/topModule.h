#ifndef TOPMODULE_H
#define TOPMODULE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "hardwareComponent.h"

using namespace std;

class TopModule {
	private:
		float criticalPathDelay;
	public:
		vector<HwComponent*> modules;
		vector<IOWire> inputs;
		vector<IOWire> outputs;
		vector<IOWire> wires;
		vector<IOWire> registers;
		vector<float>addSubGraph;
		vector<float>logicGraph;
		vector<float>mulGraph;
		vector<float>divModGraph;


		TopModule();

		void setInputs(vector<IOWire> inputs);
		void setOutputs(vector<IOWire> outputs);
		void setWires(vector<IOWire> wires);
		void setRegisters(vector<IOWire> registers);
		void addModule(HwComponent* module);
		IOWire* findInputWire(const string& wireName);
		IOWire* findOutputWire(const string& wireName);
		IOWire* findOutputRegister(const string& wireName);

		void printInputs(ofstream& circuitFile);
		void printOutputs(ofstream& circuitFile);
		void printWires(ofstream& circuitFile);
		void printRegisters(ofstream& circuitFile);
		void addWire(IOWire& wire);
		void printModuleName(ofstream& circuitFile, string CircuitName);
		void printModules(ofstream& circuitFile);

		double findInputDelay(HwComponent module);
		int calculateTimeFrames(int latency);
		void alapSchedule(int latency);
		void asapSchedule();
		void populateGraph(int latency);
		void forceSchedule(int latency);
		vector<float> selfForce(HwComponent currMod, int next, int prev);
		float successorForces(HwComponent *currMod, int assumedTime, string operation);
		float predecessorForces(HwComponent *currMod, int assumedTime, string operation);
};

#endif // TOPMODULE_H