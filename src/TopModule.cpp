#include "TopModule.h"
#include <iostream>

TopModule::TopModule()
{
	this->inputs = vector<IOWire>(0);
	this->outputs = vector<IOWire>(0);
	this->wires = vector<IOWire>(0);
	this->wires.reserve(100);
	this->registers = vector<IOWire>(0);
	this->modules = vector<Module*>(0);
	this->addSubGraph = vector<float>(0);
	this->logicGraph = vector<float>(0);
	this->mulGraph = vector<float>(0);
	this->divModGraph = vector<float>(0);
}

void TopModule::setInputs(vector<IOWire> inputs)
{
	this->inputs.insert(this->inputs.end(), inputs.begin(), inputs.end());
	return;
}

void TopModule::setOutputs(vector<IOWire> outputs)
{
	this->outputs.insert(this->outputs.end(), outputs.begin(), outputs.end());
	return;
}

void TopModule::setWires(vector<IOWire> wires)
{
	this->wires.insert(this->wires.end(), wires.begin(), wires.end());
	return;
}

void TopModule::setRegisters(vector<IOWire> registers)
{
	this->registers.insert(this->registers.end(), registers.begin(), registers.end());
	return;
}

void TopModule::addModule(Module* module)
{
	this->modules.push_back(module);
}

IOWire* TopModule::findInputWire(string wireName)
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

IOWire* TopModule::findOutputWire(string wireName)
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

	//cout << "No Module output found for: " << wireName << endl;

	return NULL;
}

IOWire* TopModule::findOutputRegister(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		if (this->registers.at(i).getName().compare(wireName) == 0)
		{
			return &(this->registers.at(i));
		}
	}
	//cout << "No Module register found for: " << wireName << endl;

	return NULL;
}

void TopModule::printInputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->inputs.size(); i++)
	{
		circuitFile << "\tinput " << this->inputs.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::printOutputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		circuitFile << "\toutput reg " << this->outputs.at(i).printIOWire() << ";" << endl;
	}

}

void TopModule::printWires(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->wires.size(); i++)
	{
		circuitFile << "\treg " << this->wires.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::printRegisters(ofstream & circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		circuitFile << "\registers " << this->registers.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::addWire(IOWire& wire)
{
	this->wires.push_back(wire);
}

void TopModule::printModuleName(ofstream& circuitFile, string CircuitName)
{
	if (CircuitName.substr(0, 5) == "474a_" || CircuitName.substr(0, 5) == "574a_") {
		CircuitName.erase(0, 5);
	}
	string inputOutputList = "(Clk, Rst, Start, Done, ";
	unsigned int i;

	for (i = 0; i < this->inputs.size(); i++)
	{
		inputOutputList += this->inputs.at(i).getName() + ", ";
		//cout << this->wires.at(i).printIOWire() << endl;
	}
	for (i = 0; i < this->outputs.size(); i++)
	{
		if (i != (this->outputs.size() - 1)) {
			inputOutputList += this->outputs.at(i).getName() + ", ";
		}
		else {
			inputOutputList += this->outputs.at(i).getName() + ");";
		}
			//cout << this->wires.at(i).printIOWire() << endl;
	}

	circuitFile << "module " << CircuitName << inputOutputList << endl << endl;
}

void TopModule::printModules(ofstream& circuitFile) {
	unsigned int i = 0;

	for (i = 0; i < this->modules.size(); i++)
	{
		circuitFile << "\t";
		this->modules.at(i)->PrintModuleStatement(circuitFile, i);
	}

}

double TopModule::findInputDelay(Module module)
{
	vector<double> inputDelays;
	unsigned int i = 0;

	for (i = 0; i < module.getInputs().size(); i++)
	{
		if (module.getInputs().at(i)->prev == NULL)
		{
			inputDelays.push_back(0);
		}
		else {
			inputDelays.push_back(findInputDelay(*module.getInputs().at(i)->prev));
		}
	}

	double largestDelay = 0;
	for (i = 0; i < inputDelays.size(); i++)
	{
		if (inputDelays.at(i) > largestDelay)
		{
			//cout << inputDelays.at(i) << endl;
			largestDelay = inputDelays.at(i);
		}
	}
	return largestDelay + module.getDelay();
}

void TopModule::findCriticalPath()
{
	vector<Module> outputModules;
	double totalDelay = 0;
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		outputModules.push_back(*this->outputs.at(i).prev);
	}

	for (i = 0; i < outputModules.size(); i++)
	{
		//cout << "Critical path for output " << i << endl;
		double delay = findInputDelay(outputModules.at(i));
		if (delay > totalDelay)
		{
			totalDelay = delay;
		}
	}

	cout << "Critical Path : " << totalDelay << " ns" << endl;
	//return totalDelay;
}

void TopModule::asapSchedule()
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int edge = 0;	//latest scheduled predecessor module time
	unsigned int tempEdge;	//current scheduled predecessor module time
	bool next;				//boolean to determine if module should be scheduled

	//iterate through modules
	for (i = 0; i < this->modules.size(); i++)
	{
		//if the module is not yet scheduled
		if (this->modules.at(i)->getTimeFrame().size() == 0)
		{
			next = true;
			//iterate through inputs of current module
			for (j = 0; j < this->modules.at(i)->getInputs().size(); j++)
			{
				//if one of the inputs has no predecessor node do nothing, check next input
				if (this->modules.at(i)->getInputs().at(j)->prev == NULL);
				
				//if predecessor node is not yet scheduled, move on to next node
				else if (modules.at(i)->getInputs().at(j)->prev->getTimeFrame().size() == 0)
				{
					next = false;
					break;
				}
				//if predecessor node is scheduled
				else
				{
					tempEdge = this->modules.at(i)->getInputs().at(j)->prev->getTimeFrame().at(0);
					//check for the latest scheduled predecessor node
					if (tempEdge > edge) 
					{
						edge = tempEdge;
					}
				}
			}
			//if all predecessor nodes are scheduled
			if (next)
			{
				//schedules node according to operation and previous node time
				if ((this->modules.at(i)->getOperation() == "DIV") || (this->modules.at(i)->getOperation() == "MOD"))
					this->modules.at(i)->setTimeFrame(edge + 3);
			
				else if (this->modules.at(i)->getOperation() == "MUL")
					this->modules.at(i)->setTimeFrame(edge + 2);

				else
					this->modules.at(i)->setTimeFrame(edge + 1);
					
				//unscheduled.erase(unscheduled.begin()+(i-1));
			}
		}
	}
}

void TopModule::alapSchedule(int latency)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int edge = latency;	//earliest successor node alap time
	unsigned int tempEdge;			//current successor node alap time
	unsigned int mod;				//successor node with earliest alap time
	bool next;

	//iterate through modules
	for (i = 0; i < this->modules.size(); i++)
	{
		//if the current node is not scheduled yet
		if (this->modules.at(i)->getTimeFrame().size() == 1)
		{
			next = true;
			//iterate through the output's successor modules
			for (j = 0; j < this->modules.at(i)->getOutputs()->next.size(); j++)
			{
				//if some successor modules do not exist do nothing, check next module
				if (this->modules.at(i)->getOutputs()->next.at(j) == NULL);

				//if a successor module is not scheduled move on to next module
				else if (this->modules.at(i)->getOutputs()->next.at(j)->getTimeFrame().size() == 1)
				{
					next = false;
					break;
				}
				//if successor modules scheduled
				else
				{
					tempEdge = this->modules.at(i)->getOutputs()->next.at(j)->getTimeFrame().at(1);
					//check for earliest scheduled successor nodes
					if (tempEdge <= edge)
					{
						edge = tempEdge;
						mod = j;
					}
				}
			}
			//if all successor nodes are scheduled
			if (next)
			{
				//schedule node according to operation and successor time
				if ((this->modules.at(i)->getOutputs()->next.at(mod)->getOperation() == "DIV") || (this->modules.at(i)->getOutputs()->next.at(mod)->getOperation() == "MOD"))
					this->modules.at(i)->setTimeFrame(edge - 3);
					
				else if (this->modules.at(i)->getOutputs()->next.at(mod)->getOperation() == "MUL")
					this->modules.at(i)->setTimeFrame(edge - 2);
					
				else
					this->modules.at(i)->setTimeFrame(edge - 1);
				//unscheduled.erase(unscheduled.begin()+(i-1));
			}
		}
	}
}

int TopModule::calculateTimeFrames(int latency)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int minLatency;
	//vector<Module> unscheduled;
	unsigned int u = this->modules.size();		//Number of unscheduled modules
	bool next;									//Boolean to check if node is to be scheduled

	//iterate through modules to schedule initial nodes
	for (i = 0; i < this->modules.size(); i++)
	{
		next = true;
		//iterate through inputs of a module
		for (j = 0; j < this->modules.at(i)->getInputs().size(); j++)
		{
			//if an input has predecessor node, do not schedule
			if (this->modules.at(i)->getInputs().at(j)->prev != NULL)
			{
				next = false;
				break;
			}
		}
		//if all inputs have no predecessor node
		if (next)
		{
			//schedule at timeframes according to resource latency
			if ((this->modules.at(i)->getOperation() == "DIV") || (this->modules.at(i)->getOperation() == "MOD"))
				this->modules.at(i)->setTimeFrame(3);
				
			else if (this->modules.at(i)->getOperation() == "MUL")
				this->modules.at(i)->setTimeFrame(2);
				
			else
				this->modules.at(i)->setTimeFrame(1);
				
			//unscheduled.erase(unscheduled.begin()+(i-1));
			u = u - 1;	//decrement unscheduled modules
		}		
	}
	//loop until all modules scheduled
	for (u; u > 0; u = u - 1)
	{
		asapSchedule();
	}
	//cout << "ASAP" << endl;
	minLatency = 0;
	for (u = 0; u < this->modules.size(); u++)
	{
		if (this->modules.at(u)->getTimeFrame().at(0) > minLatency)
		{
			minLatency = this->modules.at(u)->getTimeFrame().at(0);
		}
	}

	if (minLatency > latency)
		return minLatency;

	j = 0;
	i = 0;
	u = this->modules.size();

	//iterate through modules
	for (i = 0; i < this->modules.size(); i++)
	{
		next = true;
		//iterate through the output's successor modules
		for (j = 0; j < this->modules.at(i)->getOutputs()->next.size(); j++)
		{
			//check if the output has no sucessor nodes
			if (this->modules.at(i)->getOutputs()->next.at(j) != NULL)
			{
				next = false;
				break;
			}
		}
		//schedule at latest time;
		if (next)
		{
			this->modules.at(i)->setTimeFrame(latency);
			u = u - 1;
		}
	}
	for (u; u > 0; u = u - 1)
	{
		alapSchedule(latency);
	}

	//cout << endl << "ALAP" << endl;
	for (u = 0; u < this->modules.size(); u++)
	{
		//cout << this->modules.at(u)->getOperation() << " " << this->modules.at(u)->getTimeFrame().at(1) << endl;
	}
	return 0;
	//forceSchedule(latency);
}

void TopModule::populateGraph(int latency)
{
	unsigned int i = 0;
	unsigned int j = 0;
	float probability;
	vector<float> aGraph = vector<float>(latency);
	vector<float> lGraph = vector<float>(latency);
	vector<float> mGraph = vector<float>(latency);
	vector<float> dGraph = vector<float>(latency);


	//iterate through all modules
	for (i = 0; i < this->modules.size(); i++)
	{
		//get the reciprocal of timeFrame width
		probability = 1/((float)this->modules.at(i)->getTimeFrame().at(1)-(float)this->modules.at(i)->getTimeFrame().at(0) + 1);

		//iterate through the possible time's the module can be scheduled at
		j = this->modules.at(i)->getTimeFrame().at(0)-1;
		for (j ; j < this->modules.at(i)->getTimeFrame().at(1); j++)
		{
			//add the probability to the corresponding element in the corresponding graph
			if ((this->modules.at(i)->getOperation() == "ADD") || (this->modules.at(i)->getOperation() == "SUB"))
				aGraph.at(j) = aGraph.at(j) + probability;
			
			else if ((this->modules.at(i)->getOperation() == "DIV") || (this->modules.at(i)->getOperation() == "MOD"))
				dGraph.at(j) = dGraph.at(j) + probability;
			
			else if ((this->modules.at(i)->getOperation() == "MUL"))
				mGraph.at(j) = mGraph.at(j) + probability;
			
			else
				lGraph.at(j) = lGraph.at(j) + probability;
			
		}
	}
	
	this->addSubGraph = aGraph;	//make graphs size of latency
	this->logicGraph = lGraph;
	this->mulGraph = mGraph;
	this->divModGraph = dGraph;
	/*
	cout << "Add/Sub Graph" << endl;
	for (i = 0; i < latency; i++)
	{
		cout << i << " " << this->addSubGraph.at(i) << endl;
	}
	cout << endl;

	cout << "Div/Mod Graph" << endl;
	for (i = 0; i < latency; i++)
	{
		cout << i << " " << this->divModGraph.at(i) << endl;
	}
	cout << endl;

	cout << "Mul Graph" << endl;
	for (i = 0; i < latency; i++)
	{
		cout << i << " " << this->mulGraph.at(i) << endl;
	}
	cout << endl;

	cout << "logic Graph" << endl;
	for (i = 0; i < latency; i++)
	{
		cout << i << " " << this->logicGraph.at(i) << endl;
	}
	cout << endl;
	*/
	
}

vector<float> TopModule::selfForce(Module currMod, int next, int prev)
{
	unsigned int i = 0;
	unsigned int j = 0;
	float probability;

	float force = 0;
	vector<float> selfForces = vector<float>(0);
	vector<float> graph = vector<float>(0);


	//calculate the reciprocal of the timeframe width
	probability = 1/((float)currMod.getTimeFrame().at(1)-(float)currMod.getTimeFrame().at(0) + 1);

	if ((currMod.getOperation() == "DIV") || (currMod.getOperation() == "MOD"))
		graph = divModGraph;

	else if ((currMod.getOperation() == "ADD") || (currMod.getOperation() == "SUB"))
		graph = addSubGraph;
	
	else if (currMod.getOperation() == "MUL")
		graph = mulGraph;
	
	else
		graph = logicGraph;
	

	//iterate though the possible times this node can be scheduled at
	//in order to get the force assuming it is scheduled at time i
	i = next;
	for (i ; i < prev; i++)
	{
		force = 0;
		//iterate through the possibe times this node can be scheduled at
		//in order to add the forces
		j = currMod.getTimeFrame().at(0)-1;
		for (j; j < currMod.getTimeFrame().at(1); j++)
		{
			//if at assumed time, then this factor will be (distribution at time j)*(1 - probability)
			if (i == j)
				force = force + graph.at(j)*(1-probability);
			
			//else this factor will be (distribution at time j)*(0 - probability)
			else
				force = force + graph.at(j)*(0-probability);

		}
		//add self force at assumed time i to the vector of self forces
		selfForces.push_back(force);
	}
	return selfForces;
	
}

float TopModule::successorForces(Module *currMod, int assumedTime, string operation)
{
	unsigned int i = 0;
	float succForce = 0;		//sum of successive forces
	vector<float> tempForce;	//self forces of implicitly scheduled nodes

	//check the current operation in order to check how it is effected
	//from the previously scheduled operation
	if (operation == "DIV" || operation == "MOD")
	{
		//if the assumed time of the previous operation does not effect
		//when this operation is scheduled
		if ((assumedTime + 2) < (currMod->getTimeFrame().at(0) - 1))
			assumedTime = currMod->getTimeFrame().at(0) - 1;
		else
			assumedTime = assumedTime + 3;
	}
	else if (operation == "MUL")
	{
		if((assumedTime + 1) < (currMod->getTimeFrame().at(0) - 1))
			assumedTime = currMod->getTimeFrame().at(0) - 1;
		else
			assumedTime = assumedTime + 2;
	}
	else
	{
		if (assumedTime < (currMod->getTimeFrame().at(0) - 1))
			assumedTime = currMod->getTimeFrame().at(0) - 1;
		else
			assumedTime = assumedTime + 1;
	}

	//iterate through successor nodes if there are any
	for (i = 0; i < currMod->getOutputs()->next.size(); i++)
	{
		//if the next isn't null
		if (currMod->getOutputs()->next.at(i) != NULL)
			succForce = succForce + successorForces(currMod->getOutputs()->next.at(i), assumedTime, currMod->getOutputs()->next.at(i)->getOperation());
	}
	//calculate the self forces of implicitly shceduled nodes
	tempForce = selfForce(*currMod, assumedTime, currMod->getTimeFrame().at(1));

	//add up self forces
	for (i = 0; i < tempForce.size(); i++)
		succForce = succForce + tempForce.at(i);

	return succForce;
}

float TopModule::predecessorForces(Module *currMod, int assumedTime, string operation)
{
	unsigned int i = 0;
	float predForce = 0;		//sum of predecessor forces
	vector<float> tempForce;	//self forces of implicitly scheduled nodes

	if (operation == "DIV" || operation == "MOD")
	{
		//if the assumed time of the previous operation does not effect
		//when this operation is scheduled
		if ((assumedTime - 2) > (currMod->getTimeFrame().at(1) - 1))
			assumedTime = currMod->getTimeFrame().at(1) - 1;
		else
			assumedTime = assumedTime - 3;
	}
	else if (operation == "MUL")
	{
		if((assumedTime - 1) > (currMod->getTimeFrame().at(1) - 1))
			assumedTime = currMod->getTimeFrame().at(1) - 1;
		else
			assumedTime = assumedTime - 2;
	}
	else
	{
		if (assumedTime > (currMod->getTimeFrame().at(1) - 1))
			assumedTime = currMod->getTimeFrame().at(1) - 1;
		else
			assumedTime = assumedTime - 1;
	}

	//iterate through predecessor nodes if there are any
	for (i = 0; i < currMod->getInputs().size(); i++)
	{
		//if the next isn't null
		if (currMod->getInputs().at(i)->prev != NULL)
			predForce = predForce + predecessorForces(currMod->getInputs().at(i)->prev, assumedTime, currMod->getOperation());
	}
	//calculate the self forces of implicitly shceduled nodes
	tempForce = selfForce(*currMod, currMod->getTimeFrame().at(0) - 1, assumedTime + 1);

	//add up self forces
	for (i = 0; i < tempForce.size(); i++)
		predForce = predForce + tempForce.at(i);

	return predForce;

}

void TopModule::forceSchedule(int latency)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int assumedTime;
	int module;				//module with lowest force
	int time;				//time with lowest force
	int tempTime;			//current module's time with lowest force
	float tempForce;			//current module's lowest force
	float minForce = 32767;	//lowest force
	vector<float> force;	//module's forces
	
	populateGraph(latency);
	//iterate through modules
	for (i = 0; i < this->modules.size(); i++)
	{
		//check if already force scheduled
		if(this->modules.at(i)->getTimeFrame().size() == 2)
		{
			//calculate self forces for each time in a module
			tempForce = 32767;
			force = selfForce(*this->modules.at(i), this->modules.at(i)->getTimeFrame().at(0) - 1, this->modules.at(i)->getTimeFrame().at(1));

			//iterate thorugh the self forces
			for (j = 0; j < force.size(); j++)
			{
				assumedTime = j + this->modules.at(i)->getTimeFrame().at(0) - 1;
				//iterate through the successor nodes
				for (k = 0; k < this->modules.at(i)->getOutputs()->next.size(); k++)
				{
					//add predecessor and successor forces to the self forces
					if(this->modules.at(i)->getOutputs()->next.at(k) != NULL)
						force.at(j) = force.at(j) + successorForces(this->modules.at(i)->getOutputs()->next.at(k), assumedTime, this->modules.at(i)->getOutputs()->next.at(k)->getOperation());

					//cout << endl;
					//cout << successorForces(this->modules.at(i)->getOutputs()->next.at(k), assumedTime, this->modules.at(i)->getOutputs()->next.at(k)->getOperation());
				}
				for (k = 0; k < this->modules.at(i)->getInputs().size(); k++)
				{
					//add predecessor and successor forces to the self forces
					if(this->modules.at(i)->getInputs().at(k)->prev != NULL)
						force.at(j) = force.at(j) + predecessorForces(this->modules.at(i)->getInputs().at(k)->prev, assumedTime, this->modules.at(i)->getOperation());
				}

				//if this force is the minimum, update minimum
				//and update its time
				if (force.at(j) < tempForce)
				{
					tempForce = force.at(j);
					tempTime = this->modules.at(i)->getTimeFrame().at(0) + j;
				}
			}
			//if the min force of the module is less then the current min, 
			//update min, the module, and the time it is to be scheduled
			if (tempForce < minForce)
			{
				minForce = tempForce;
				module = i;
				time = tempTime;
			}
		}
	}
	//set the time frames to the new scheduled time
	this->modules.at(module)->updateAsap(time);
	this->modules.at(module)->updateAlap(time);
	this->modules.at(module)->setTimeFrame(time);
}
