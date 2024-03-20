// This file defines the member functions of the HwComponent and Wire classes.
// These classes represent hardware components and wires respectively.

#include "hardwareComponent.h"  // Include header file for HwComponent class

// Default constructor for HwComponent class
HwComponent::HwComponent()
{
    // Initialize member variables
    this->operation = "";
    this->inputs = vector<Wire*>(0);
    this->output = new Wire();
    this->bitSize = 0;
    this->isSigned = false;
}

// Constructor with operation parameter for HwComponent class
HwComponent::HwComponent(string operation)
{
    // Initialize member variables with provided operation
    this->operation = operation;
    this->inputs = vector<Wire*>(0);
    this->output = new Wire();
    this->bitSize = 0;
    this->isSigned = false;
}

// Constructor with operation, inputs, and output parameters for HwComponent class
HwComponent::HwComponent(string operation, vector<Wire*> inputs, Wire *output)
{
    int tempbitSize = 0;
    unsigned int i = 0;

    // Initialize member variables with provided values
    this->operation = operation;
    this->inputs = inputs;
    this->output = output;
    this->isSigned = false;
    tempbitSize = this->output->getBitSize();

    // Calculate bit size based on inputs and output
    for (i = 0; i < inputs.size(); i++) {
        this->isSigned |= inputs.at(i)->getSigned();
    }
    this->isSigned |= output->getSigned();

    for (i = 0; i < inputs.size(); i++) {
        this->inputs.at(i)->addNext(this);
        if ((inputs.at(i)->getBitSize() > tempbitSize) && (operation == "GT" || operation == "LT" || operation == "EQ")) {
            tempbitSize = inputs.at(i)->getBitSize();
        }
    }
    if (this->operation == "MUX") {
        tempbitSize = this->inputs.at(1)->getBitSize() > this->inputs.at(2)->getBitSize() ? this->inputs.at(1)->getBitSize() : this->inputs.at(2)->getBitSize();
    }

    this->output->setPrev(this);
    this->bitSize = tempbitSize;
}

// Getter method for operation member variable of HwComponent class
string HwComponent::getOperation() { return this->operation; }

// Getter method for inputs member variable of HwComponent class
vector<Wire*> HwComponent::getInputs() { return this->inputs; }

// Getter method for output member variable of HwComponent class
Wire* HwComponent::getOutputs() { return this->output; }

// Function to print information about the hardware component
void HwComponent::writeHwComponent()
{
    cout << "Component Name: " << this->operation << endl;
}

// Function to print the hardware component statement to a file
void HwComponent::writeHwComponentStatement(ofstream& circuitFile, int HwComponentNum)
{
    string inputs;
    string output;
    string statement = "";

    // Parse and format input names
    for (const auto& input : this->inputs) {
        if (this->isSigned) {
            inputs += "$signed(" + input->getName() + "), ";
        }
        else {
            inputs += input->getName() + ", ";
        }
    }
    inputs = inputs.substr(0, inputs.length() - 2); // Remove trailing comma and space

    // If the operation is MUX, rearrange input names
    if (this->operation == "MUX") {
        inputs = this->inputs.at(2)->getName() + ", " + this->inputs.at(1)->getName() + ", " + this->inputs.at(0)->getName();
    }

    // Get output name
    output = this->output->getName();

    // Prefix for signed statements
    if (this->isSigned) {
        statement = "S";
    }

    // Format the final output statement based on the operation
    if (this->operation == "GT") {
        statement += "COMP #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", " + output + ", , );";
    }
    else if (this->operation == "LT") {
        statement += "COMP #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", ," + output + ", );";
    }
    else if (this->operation == "EQ") {
        statement += "COMP #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", , ," + output + ");";
    }
    else if (this->operation == "REG") {
        statement += "REG #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", clk, rst, " + output + ");";
    }
    else if (this->operation == "MUX") {
        statement += this->operation + "2x1" + " #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", " + output + ");";
    }
    else {
        statement += this->operation + " #(" + to_string(this->getBitSize()) + ")" + this->operation + "_" + to_string(HwComponentNum) + "(" + inputs + ", " + output + ");";
    }
    circuitFile << statement << endl; // Write the statement to the output file
}


// Getter method for bitSize member variable of HwComponent class
int HwComponent::getBitSize() { return this->bitSize; }

// Setter method for operation member variable of HwComponent class
void HwComponent::setOperation(string operation) { this->operation = operation; }

// Default constructor for Wire class
Wire::Wire()
{
    // Initialize member variables
    this->name = "";
    this->type = "";
    this->prev = NULL;
    this->bitSize = 0;
    this->next = vector<HwComponent*>();
    this->isSigned = false;
}

// Constructor with name and type parameters for Wire class
Wire::Wire(string name, string type)
{
    string intString = "";
    stringstream stringStreamBuffer;
    int bitSize = 0;

    // Extract bit size from type string
    if (type.find("UInt") != std::string::npos)
    {
        intString = type.substr(4, type.length());
        bitSize = stoi(intString);
        this->isSigned = false;
    }
    else if (type.find("Int") != std::string::npos)
    {
        intString = type.substr(3, type.length());
        bitSize = stoi(intString);
        this->isSigned = true;
    }

    // Initialize member variables with provided values
    this->name = name;
    this->type = type;
    this->prev = NULL;
    this->next = vector<HwComponent*>();
    this->bitSize = bitSize;
}

// Setter method for prev member variable of Wire class
void Wire::setPrev(HwComponent *prev) { this->prev = prev; }

// Setter method for next member variable of Wire class
void Wire::setNext(vector<HwComponent*> next) { this->next = next; }

// Function to add a hardware component to the next member variable of Wire class
void Wire::addNext(HwComponent *next) { this->next.push_back(next); }

// Getter method for name member variable of Wire class
string Wire::getName() { return this->name; }

// Getter method for type member variable of Wire class
string Wire::getType() { return this->type; }

// Getter method for bitSize member variable of Wire class
int Wire::getBitSize() { return this->bitSize; }

// Getter method for isSigned member variable of Wire class
bool Wire::getSigned() { return this->isSigned; }

// Function to write wire declaration string
string Wire::writeWire()
{
    string retString = "";

    if (this->isSigned)
    {
        retString = "signed " + this->writeBitSize() + " " + this->name;
    }
    else {
        retString = this->writeBitSize() + " " + this->name;
    }

    return retString;
}

// Function to write bit size declaration string
string Wire::writeBitSize()
{
    stringstream stringStreamBuffer;
    if (this->bitSize > 1) {
        stringStreamBuffer << "[" << (this->bitSize - 1) << ":0]";
    }
    else {
        stringStreamBuffer << "";
    }

    return stringStreamBuffer.str();
}
