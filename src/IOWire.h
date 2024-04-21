#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Module.h"


class Module;

using namespace std;

class IOWire {
	private:
		string name;
		string type;
		int bitWidth;
		bool isSigned;
		

	public:
		Module *prev;
		vector<Module*> next;

		IOWire();
		IOWire(string name, string type);

		void setNext(vector<Module*> next);
		void addNext(Module *next);
		void setPrev(Module *prev);
		void setName(string name);
		string getName();
		string getType();
		int getBitWidth();
		bool getSigned();

		string printIOWire();
		string printBitWidth();


};