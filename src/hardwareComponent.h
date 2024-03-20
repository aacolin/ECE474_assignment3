#ifndef HARDWARE_COMPONENT_H  // Header guard to prevent multiple inclusion
#define HARDWARE_COMPONENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>    // standard library headers for string stream operations.

class Wire;  // Forward declaration of the Wire class

using namespace std;

// Class representing a hardware component
class HwComponent
{
private:
    string operation;       // Operation performed by the hardware component
    vector<Wire*> inputs;   // Vector containing pointers to input wires
    Wire* output;           // Pointer to the output wire
    int bitSize;            // Size of the data in bits
    bool isSigned;          // Indicates whether the data is signed

public:
    // Constructors
    HwComponent();                                  // Default constructor
    HwComponent(string operation);                  // Constructor with operation parameter
    HwComponent(string operation, vector<Wire*> inputs, Wire *output);  // Constructor with operation, inputs, and output parameters
    
    // Utility functions
    void remove_comas(string& str);                 // Function to remove commas from a string
    
    // Getter methods
    string getOperation();                          // Function to get the operation of the hardware component
    vector<Wire*> getInputs();                      // Function to get the input wires of the hardware component
    Wire* getOutputs();                             // Function to get the output wire of the hardware component
    int getBitSize();                               // Function to get the size of the data in bits
    
    // Output functions
    void writeHwComponent();                        // Function to print information about the hardware component
    void writeHwComponentStatement(ofstream& circuitFile, int HwComponentNum);  // Function to print the hardware component statement to a file
    
    // Setter method
    void setOperation(string operation);            // Function to set the operation of the hardware component
};


// Class representing a wire
class Wire {
private:
    string name;        // Name of the wire
    string type;        // Type of the wire (e.g., input, output, internal)
    int bitSize;        // Size of the wire in bits
    bool isSigned;      // Indicates whether the wire data is signed

public:
    HwComponent *prev;              // Pointer to the previous hardware component connected to this wire
    vector<HwComponent*> next;      // Vector containing pointers to the next hardware components connected to this wire

    Wire();                         // Default constructor
    Wire(string name, string type); // Constructor with name and type parameters

    // Setter methods
    void setNext(vector<HwComponent*> next);  // Set the next hardware components connected to this wire
    void addNext(HwComponent *next);          // Add a hardware component to the list of next components
    void setPrev(HwComponent *prev);          // Set the previous hardware component connected to this wire

    // Getter methods
    string getName();       // Get the name of the wire
    string getType();       // Get the type of the wire
    int getBitSize();       // Get the size of the wire in bits
    bool getSigned();       // Check if the wire data is signed

    // Methods to generate Verilog code
    string writeWire();     // Generate Verilog code for the wire declaration
    string writeBitSize();  // Generate Verilog code for the wire bit size
};

#endif  // End of header guard
