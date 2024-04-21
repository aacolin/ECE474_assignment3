#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "IOWire.h"

class IOWire;

using namespace std;


class Module
{
	private:
		string operation;
		string operationLine;
		vector<IOWire*> inputs;
		IOWire* output;
		double delay;
		int maxBitWidth;
		bool isSigned;
		vector<int> timeFrame;

	public:
		Module();
		Module(string operation);
		Module(string operation, vector<IOWire*> inputs, IOWire *output, vector<double> latency, string operationLine);

		double calculateDelay(vector<double> latency);
		string getOperation();
		string getOperationLine();
		void setOperationLine(string operationLine);
		vector<IOWire*> getInputs();
		IOWire* getOutputs();
		void setOutput(IOWire* output);
		double getDelay();
		int getMaxBitWidth();
		vector<int> getTimeFrame();
		void setTimeFrame(int edge);
		void updateAsap(int edge);
		void updateAlap(int edge);
		void PrintModule();
		void PrintModuleStatement(ofstream& circuitFile, int moduleNum);
		void setOperation(string operation);
		
};