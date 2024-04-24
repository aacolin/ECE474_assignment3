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
        vector<Wire*> inputs; 							// The input wires to the module
        Wire* output; 									// The output wire from the module
        double delay; 										// The delay of the module
        int maxBitWidth; 									// The maximum bit width of the module
        bool isSigned; 										// Whether the module operates on signed numbers
        vector<int> timeFrame; 								// The time frame of the module
	
	// Declare the public members of the Module class
    public:
        HwComponent(); 											// Default constructor
        HwComponent(string operation); 							// Constructor that takes an operation
        HwComponent(string operation, vector<Wire*> inputs, 	// Constructor that takes an operation, inputs, output, and operation line
			   Wire *output, string operationLine); 		
        
		void updateAsap(int edge); 							// Method to update the module as soon as possible
        void updateAlap(int edge); 							// Method to update the module as late as possible
        void PrintModule(); 								// Method to print the module
        void PrintModuleStatement(ofstream& circuitFile, 	// Method to print the module statement
								  int moduleNum); 			

		// Setters
		void setOperationLine(string operationLine); 		// Setter for the operation line
		void setOperation(string operation); 				// Setter for the operation
		void setOutput(Wire* output); 					// Setter for the output
		void setTimeFrame(int edge); 						// Setter for the time frame

		// Getters
		string getOperation(); 								// Getter for the operation
        string getOperationLine(); 							// Getter for the operation line
        vector<Wire*> getInputs(); 						// Getter for the inputs
        Wire* getOutputs(); 								// Getter for the output
        double getDelay(); 									// Getter for the delay
        int getMaxBitWidth(); 								// Getter for the maximum bit width
        vector<int> getTimeFrame(); 						// Getter for the time frame   
};


class Wire {
	private:
		string name;
		string type;
		int bitWidth;
		bool isSigned;
		

	public:
		HwComponent *prev;
		vector<HwComponent*> next;

		Wire();
		Wire(string name, string type);

		void setNext(vector<HwComponent*> next);
		void addNext(HwComponent *next);
		void setPrev(HwComponent *prev);
		void setName(string name);
		string getName();
		string getType();
		int getBitWidth();
		bool getSigned();

		string printWire();
		string printBitWidth();


};

# endif 