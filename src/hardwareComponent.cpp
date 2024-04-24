/**
 * @file Module.cpp
 * @brief Implementation file for the Module class.
 * 
 * This file contains the implementation of the Module class, which represents a module in a circuit.
 * A module consists of an operation, inputs, output, delay, maximum bit width, signed flag, and time frame.
 * It provides methods to get and set the operation, inputs, output, delay, maximum bit width, and time frame.
 * It also provides methods to print the module, print the module statement, and update the scheduling time frame.
 */

#include "hardwareComponent.h"
#include <map>


HwComponent::HwComponent()
    : operation(""), inputs(), output(new IOWire()), delay(0), 
      maxBitWidth(0), isSigned(false), timeFrame()
{}

HwComponent::HwComponent(string operation)
    : operation(operation), inputs(), output(new IOWire()), delay(0), 
      maxBitWidth(0), isSigned(false), timeFrame()
{}

/**
 * @brief Constructs a Hardware Component object.
 * 
 * This constructor initializes a HwComponent object with a given operation, a list of input wires, an output wire, and an operation line.
 * It also sets the 'isSigned' attribute based on the output wire and input wires, and the 'maxBitWidth' attribute based on the operation and the bit widths of the input wires.
 * The constructor also updates the connections between the module and its input and output wires.
 * 
 * @param operation The operation performed by the module.
 * @param inputs The input wires to the module.
 * @param output The output wire from the module.
 * @param operationLine The line of code that represents the operation.
 */

HwComponent::HwComponent(string operation, vector<IOWire*> inputs, IOWire *output, string operationLine)
    : operation(operation), inputs(inputs), output(output), operationLine(operationLine), 
      isSigned(output->getSigned()), maxBitWidth(output->getBitWidth()), timeFrame(0)
{
    // Update the connections between the module and its input and output wires
    for (auto& input : inputs) {
        isSigned |= input->getSigned();
        input->addNext(this);

        // Update the maximum bit width based on the operation and the bit widths of the input wires
        if (operation == "GT" || operation == "LT" || operation == "EQ") {
            maxBitWidth = max(maxBitWidth, input->getBitWidth());
        }
    }

    // Update the maximum bit width based on the operation and the bit widths of the input wires
    if (operation == "MUX") {
        maxBitWidth = max(inputs[1]->getBitWidth(), inputs[2]->getBitWidth());
    }

    output->setPrev(this);
}

/**
 * @brief Prints the name of the module.
 * 
 * This function outputs the name of the module to the standard output. The name of the module is the operation it performs.
 */

void HwComponent::PrintModule() { cout << "Module Name: " << this->operation << endl; }


/**
 * @brief Updates the As Soon As Possible (ASAP) time frame of the module.
 * 
 * This function sets the ASAP time frame of the module to the given edge time. It then uses a map to determine the delay for different operations.
 * It iterates over the modules connected to the output of this module and updates their ASAP time frames if necessary.
 * 
 * @param edge The current time edge.
 */
void HwComponent::updateAsap(int edge){
    // Set the ASAP time frame of the module to the given edge time
	timeFrame.at(0) = edge;

    // Map of operation delays
	map<string, int> operationDelays = { 
		{"DIV", 3},{"MOD", 3},{"MUL", 2},{"default", 1}
	};

    // Iterate over the modules connected to the output of this module
	for (auto& output : this->getOutputs()->next)	{
        // Get the delay for the operation
		string operation = output->getOperation();
		int delay = operationDelays.count(operation) ? operationDelays[operation] : operationDelays["default"];
    
        // Update the ASAP time frame of the module connected to the output
		if (edge + delay - 1 >= output->getTimeFrame().at(0))		{
			output->updateAsap(edge + delay);
		}
	}
}


/**
 * @brief Updates the As Late As Possible (ALAP) time frame of the module.
 * 
 * This function sets the ALAP time frame of the module to the given edge time. It then uses a map to determine the delay for different operations.
 * It iterates over the modules connected to the input of this module and updates their ALAP time frames if necessary.
 * 
 * @param edge The current time edge.
 */

void HwComponent::updateAlap(int edge){
    // Set the ALAP time frame of the module to the given edge time
    timeFrame.at(1) = edge;

    // Map of operation delays
    map<string, int> operationDelays = {
        {"DIV", 3}, {"MOD", 3}, {"MUL", 2}, {"default", 1}
    };

    // Iterate over the modules connected to the input of this module
    for (auto& input : this->getInputs()) {

        if (input->prev != NULL) {
            // Get the delay for the operation
            string operation = this->getOperation();
            int delay = operationDelays.count(operation) ? operationDelays[operation] : operationDelays["default"];

            // Update the ALAP time frame of the module connected to the input
            if (edge - delay + 1 <= input->prev->getTimeFrame().at(1))            {
                input->prev->updateAlap(edge - delay);
            }
        }
    }
}

/**
 * @brief Prints the module statement to a circuit file.
 * 
 * This function generates a string representation of the module and writes it to a given circuit file. 
 * The string representation includes the operation, inputs, and output of the module, as well as its bit width and whether it is signed.
 * The format of the string representation depends on the operation of the module.
 * 
 * @param circuitFile The output file stream to write the module statement to.
 * @param moduleNum The number of the module.
 */
void HwComponent::PrintModuleStatement(ofstream& circuitFile, int moduleNum)
{
    string inputs;
    string output = this->output->getName();
    string statement = this->isSigned ? "S" : "";
    // Get the inputs of the module
    for (auto& input : this->inputs) {
        inputs += (this->isSigned ? "$signed(" + input->getName() + "), " : input->getName() + ", ");
    }
    // Remove the trailing comma and space
    inputs = inputs.substr(0, inputs.length()-2);

    if (this->operation == "MUX") {
        inputs = this->inputs.at(2)->getName() + ", " + this->inputs.at(1)->getName() + ", " + this->inputs.at(0)->getName();
    }
    // Map of operation formats
    map<string, string> operationFormats = {
        {"GT", "COMP #(%d)%s_(%d)(%s, %s, , );"},
        {"LT", "COMP #(%d)%s_(%d)(%s, ,%s, );"},
        {"EQ", "COMP #(%d)%s_(%d)(%s, , ,%s);"},
        {"REG", "REG #(%d)%s_(%d)(%s, clk, rst, %s);"},
        {"MUX", "%s2x1 #(%d)%s_(%d)(%s, %s);"},
        {"default", "%s #(%d)%s_(%d)(%s, %s);"}
    };
    // Get the format of the operation
    string format = operationFormats.count(this->operation) ? operationFormats[this->operation] : operationFormats["default"];

    char buffer[256];
    // Print the statement to the circuit file
    sprintf(buffer, format.c_str(), this->getMaxBitWidth(), this->operation.c_str(), moduleNum, inputs.c_str(), output.c_str());
    // Append the statement to the module statement
    statement += buffer;
    // Write the statement to the circuit file
    circuitFile << statement << endl;
}

// Setters
void HwComponent::setOperationLine(string operationLine) { this->operationLine = operationLine; }
void HwComponent::setOutput(IOWire * output) { this->output = output; }
void HwComponent::setOperation(string operation) { this->operation = operation; }
void HwComponent::setTimeFrame(int edge) { timeFrame.push_back(edge); }

// Getters
string HwComponent::getOperation() { return this->operation; }
string HwComponent::getOperationLine() { return this->operationLine; }
vector<IOWire*> HwComponent::getInputs() { return this->inputs; }
IOWire* HwComponent::getOutputs() { return this->output; }
double HwComponent::getDelay() { return this->delay; }
int HwComponent::getMaxBitWidth() { return this->maxBitWidth; }
vector<int> HwComponent::getTimeFrame() { return this->timeFrame; }








IOWire::IOWire() : name(""), type(""), prev(nullptr), bitWidth(0), isSigned(false) {}

IOWire::IOWire(string name, string type) : name(name), type(type), prev(nullptr), isSigned(false)
{
    size_t pos = type.find("UInt");
    if (pos != std::string::npos) 
    {
        bitWidth = stoi(type.substr(4));
    }
    else if ((pos = type.find("Int")) != std::string::npos) 
    {
        bitWidth = stoi(type.substr(3));
        isSigned = true;
    }
}

void IOWire::setPrev(HwComponent *prev){
	this->prev = prev;
	return;
}

void IOWire::setName(string name){
	this->name = name;
}

void IOWire::setNext(vector<HwComponent*> next){
	this->next = next;
	return;
}

void IOWire::addNext(HwComponent *next){
	this->next.push_back(next);
	return;
}

string IOWire::getName(){
	return this->name;
}

string IOWire::getType(){
	return this->type;
}

int IOWire::getBitWidth(){
	return this->bitWidth;
}

string IOWire::printIOWire(){
	string retString = "";

	if (this->isSigned)	{
		retString = "signed " + this->printBitWidth() + " " + this->name;
	}
	else {
		retString = this->printBitWidth() + " " + this->name;
	}
	
	return retString;
}




string IOWire::printBitWidth() {
    // Create a stringstream to build the bit width string
    stringstream bitWidthStream;

    // If the bit width is greater than 1, format it as a range [bitWidth-1:0]
    if (this->bitWidth > 1) {
        bitWidthStream << "[" << (this->bitWidth - 1) << ":0]";
    }
    // If the bit width is not greater than 1, add an empty string to the stream
    else {
        bitWidthStream << "";
    }

    // Return the string representation of the bit width
    return bitWidthStream.str();
}


bool IOWire::getSigned(){
	return this->isSigned;
}