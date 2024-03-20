#include "topModule.h"

//contructor
TopModule::TopModule()
{
	this->inputs = vector<Wire>(0);
	this->outputs = vector<Wire>(0);
	this->wires = vector<Wire>(0);
	this->registers = vector<Wire>(0);
	this->modules = vector<HwComponent>(0);
}

void TopModule::setInputs(vector<Wire> inputs)
{
	this->inputs.insert(this->inputs.end(), inputs.begin(), inputs.end());
	return;
}

void TopModule::setOutputs(vector<Wire> outputs)
{
	this->outputs.insert(this->outputs.end(), outputs.begin(), outputs.end());
	return;
}

void TopModule::setWires(vector<Wire> wires)
{
	this->wires.insert(this->wires.end(), wires.begin(), wires.end());
	return;
}

void TopModule::setRegisters(vector<Wire> registers)
{
	this->registers.insert(this->registers.end(), registers.begin(), registers.end());
	return;
}

void TopModule::addModule(HwComponent module)
{
	this->modules.push_back(module);
}

Wire* TopModule::findInputWire(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->inputs.size(); i++)
	{
		if (this->inputs.at(i).getName().compare(wireName) == 0)
		{
			return &(this->inputs.at(i));
		}
 	}

	for (i = 0; i < this->wires.size(); i++)
	{
		if (this->wires.at(i).getName().compare(wireName) == 0)
		{
			return &(this->wires.at(i));
		}
	}

	//cout << "No Module input found for: " << wireName << endl;

	return NULL;
}

Wire* TopModule::findOutputWire(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		if (this->outputs.at(i).getName().compare(wireName) == 0)
		{
			return &(this->outputs.at(i));
		}
	}

	for (i = 0; i < this->wires.size(); i++)
	{
		if (this->wires.at(i).getName().compare(wireName) == 0)
		{
			return &(this->wires.at(i));
		}
	}
	return NULL;
}

Wire* TopModule::findOutputRegister(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		if (this->registers.at(i).getName().compare(wireName) == 0)
		{
			return &(this->registers.at(i));
		}
	}
	return NULL;
}

void TopModule::writeInputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	circuitFile << "\tinput clk, rst;" << endl;
	for (i = 0; i < this->inputs.size(); i++)
	{
		circuitFile << "\tinput " << this->inputs.at(i).writeWire() << ";" << endl;
	}
}

void TopModule::writeOutputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		circuitFile << "\toutput " << this->outputs.at(i).writeWire() << ";" << endl;
	}

}

void TopModule::writeWires(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->wires.size(); i++)
	{
		circuitFile << "\twire " << this->wires.at(i).writeWire() << ";" << endl;
	}
}

void TopModule::writeRegisters(ofstream & circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		circuitFile << "\registers " << this->registers.at(i).writeWire() << ";" << endl;
	}
}

void TopModule::addWire(Wire& wire)
{
	this->wires.push_back(wire);
}

void TopModule::writeModuleName(ofstream& circuitFile, string CircuitName)
{
	if (CircuitName.substr(0, 5) == "474a_") {
		CircuitName.erase(0, 5);
	}
	string inputOutputList = "(clk, rst, ";
	unsigned int i;

	for (i = 0; i < this->inputs.size(); i++)
	{
		inputOutputList += this->inputs.at(i).getName() + ", ";
	}
	for (i = 0; i < this->outputs.size(); i++)
	{
		if (i != (this->outputs.size() - 1)) {
			inputOutputList += this->outputs.at(i).getName() + ", ";
		}
		else {
			inputOutputList += this->outputs.at(i).getName() + ");";
		}
	}

	circuitFile << "module " << CircuitName << inputOutputList << endl << endl;
}

void TopModule::writeModules(ofstream& circuitFile) {
	unsigned int i = 0;

	for (i = 0; i < this->modules.size(); i++)
	{
		circuitFile << "\t";
		this->modules.at(i).writeHwComponentStatement(circuitFile, i);
	}

}

