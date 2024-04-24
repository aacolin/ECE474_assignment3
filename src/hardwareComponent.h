/**
 * @brief This file defines the Module class which represents a module in a circuit.
 */

# ifndef HARDWARECOMPONENT_H
# define HARDWARECOMPONENT_H

// Include necessary standard library headers
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>




// Forward declaration of the Wire class to resolve circular dependencies
class Wire;

// Use the standard namespace
using namespace std;

// Define the Module class
class HwComponent
{
	// Declare the private members of the Module class
    private:
        string operation; 									// The operation performed by the module
        string operationLine; 								// The line of code that represents the operation
        vector<Wire*> inputs; 								// The input wires to the module
        Wire* output; 										// The output wire from the module
        double delay; 										// The delay of the module
        int maxBitWidth; 									// The maximum bit width of the module
        bool isSigned; 										// Whether the module operates on signed numbers
        vector<int> timeFrame; 								// The time frame of the module
	
	// Declare the public members of the Module class
    public:
        HwComponent(); 										// Default constructor
        HwComponent(string operation); 						// Constructor that takes an operation
        HwComponent(string operation, vector<Wire*> inputs, // Constructor that takes an operation, inputs, output, and operation line
			   Wire *output, string operationLine); 		
        
		void updateAsap(int edge); 							// Method to update the module as soon as possible
        void updateAlap(int edge); 							// Method to update the module as late as possible
        void PrintModule(); 								// Method to print the module
        void PrintModuleStatement(ofstream& circuitFile, 	// Method to print the module statement
								  int moduleNum); 			

		// Setters
		void setOperationLine(string operationLine); 		// Setter for the operation line
		void setOperation(string operation); 				// Setter for the operation
		void setOutput(Wire* output); 						// Setter for the output
		void setTimeFrame(int edge); 						// Setter for the time frame

		// Getters
		string getOperation(); 								// Getter for the operation
        string getOperationLine(); 							// Getter for the operation line
        vector<Wire*> getInputs(); 							// Getter for the inputs
        Wire* getOutputs(); 								// Getter for the output
        double getDelay(); 									// Getter for the delay
        int getMaxBitWidth(); 								// Getter for the maximum bit width
        vector<int> getTimeFrame(); 						// Getter for the time frame   
};

//	Define the Wire class
class Wire {
	private:
		string name;										// The name of the wire
		string type;										// The type of the wire				
		int bitWidth;										// The bit width of the wire
		bool isSigned;										// Whether the wire is signed
		

	public:
		HwComponent *prev;									// The previous component
		vector<HwComponent*> next;							// The next components

		Wire();												// Default constructor
		Wire(string name, string type);						// Constructor that takes a name and type

		void setNext(vector<HwComponent*> next);			// Setter for the next components
		void addNext(HwComponent *next);					// Method to add a next component
		void setPrev(HwComponent *prev);					// Setter for the previous component
		void setName(string name);							// Setter for the name
		string getName();									// Getter for the name
		string getType();									// Getter for the type
		int getBitWidth();									// Getter for the bit width
		bool getSigned();									// Getter for whether the wire is signed

		string printWire();									// Method to print the wire
		string printBitWidth();								// Method to print the bit width


};

# endif 