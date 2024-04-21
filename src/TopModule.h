#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Module.h"
#include "IOWire.h"

using namespace std;

class TopModule {
	private:
		float criticalPathDelay;
	public:
		vector<Module*> modules;
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
		void addModule(Module* module);
		IOWire* findInputWire(string wireName);
		IOWire* findOutputWire(string wireName);
		IOWire* findOutputRegister(string wireName);

		void printInputs(ofstream& circuitFile);
		void printOutputs(ofstream& circuitFile);
		void printWires(ofstream& circuitFile);
		void printRegisters(ofstream& circuitFile);
		void addWire(IOWire& wire);
		void printModuleName(ofstream& circuitFile, string CircuitName);
		void printModules(ofstream& circuitFile);

		double findInputDelay(Module module);
		void findCriticalPath();
		int calculateTimeFrames(int latency);
		void alapSchedule(int latency);
		void asapSchedule();
		void populateGraph(int latency);
		void forceSchedule(int latency);
		vector<float> selfForce(Module currMod, int next, int prev);
		float successorForces(Module *currMod, int assumedTime, string operation);
		float predecessorForces(Module *currMod, int assumedTime, string operation);
};