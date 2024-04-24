# ifndef IOWIRE_H
# define IOWIRE_H

#include <iostream>
#include <sstream>
#include <string>
#include "hardwareComponent.h"


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
# endif // IOWIRE_H