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
		vector<Wire> inputs;
		vector<Wire> outputs;
		vector<Wire> wires;
		vector<Wire> registers;
		vector<float>addSubGraph;
		vector<float>logicGraph;
		vector<float>mulGraph;
		vector<float>divModGraph;


		TopModule();

		void setInputs(vector<Wire> inputs);
		void setOutputs(vector<Wire> outputs);
		void setWires(vector<Wire> wires);
		void setRegisters(vector<Wire> registers);
		void addModule(HwComponent* module);
		Wire* findInputWire(const string& wireName);
		Wire* findOutputWire(const string& wireName);
		Wire* findOutputRegister(const string& wireName);

		void printInputs(ofstream& circuitFile);
		void printOutputs(ofstream& circuitFile);
		void printWires(ofstream& circuitFile);
		void printRegisters(ofstream& circuitFile);
		void addWire(Wire& wire);
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