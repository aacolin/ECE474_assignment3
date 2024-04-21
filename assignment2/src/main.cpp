#include <iostream> // Standard input/output stream objects
#include <fstream>  // File stream objects
#include <string>   // String types and functions
#include <vector>   // Dynamic array-like container
#include <memory>   // Smart pointers
#include "circuitParser.h" // Header file for circuit parser

using namespace std; // Using the standard namespace for convenience.

// Function prototypes. 
vector<string> read_netlist(string fileName);
void write_Verilog_file(string circuitName, TopModule *topModule);
bool check_arguments_errors(int argc, char*  argv[]);

int main(int argc, char* argv[]) 
{
	// check for argument errors or input file errors
	if (!check_arguments_errors(argc, argv)){return 1;}

	// Read the contents of the netlist file specified in the command line argument argv[1]
	// and store them in a vector of strings named netlist
    vector<string> netlist = read_netlist( argv[1]);
	
	// Use unique_ptr for automatic memory management (no need to use "delete")
    unique_ptr<TopModule> topModule(new TopModule());

	//pasrse lines of netlist file
	for (const auto& line : netlist)
    {
		// Parse the current line of the netlist file using the Parser class,
		// and update the topModule with the parsed information
        CircuitParser::parseLine(line, topModule.get()); 
    }

	/*
	Call the function to write Verilog code to a file
	Parameters:
		- argv[2]: The name of the Verilog file to write (command line argument)
		- topModule.get(): Pointer to the top module of the design
	*/
    write_Verilog_file(argv[2], topModule.get());
	return 0;
}

/*
	Function: bool check_arguments(int argc, char*  argv[])
	Function to check the validity of command line arguments
	Parameters:
		- argc: Number of command line arguments
		- argv[]: Array of command line arguments
	Returns:
		- True if the arguments are valid, false otherwise
*/

bool check_arguments_errors(int argc, char*  argv[]) {	
	if (argc != 3){
		cout << "Syntax error: \n\n\tIncorrect number arguments.\n" << endl;
		cout << "Syntax: dpgen <INPUT-netlistFile> <OUTPUT-verilogFile>\n" << endl;
		cout << "\tExample: --> dpgen 474a_circuit1.txt circuit1.v" << endl;
		return false;
	}

	vector<string> 	netlist = read_netlist( argv[1]);

	if (netlist.empty()){
		cout << "Error: \n\n\tUnable to read file --> " << argv[1] << endl;
		cout << "\nCommon errors: \n\n\t- Empty file \n\t- Wrong file name \n\t- Corrupted file" << endl;
		return false;
	}
	
	// Use unique_ptr for automatic memory management
	// Smart pointers like std::unique_ptr ensure that the memory allocated for an object is properly 
	// deallocated when the smart pointer goes out of scope. No need to use keyword <delete>.
    unique_ptr<TopModule> topModule(new TopModule());

	 for (const auto& line : netlist){
        // Check for errors in netlist file
        if (CircuitParser::parseLine(line, topModule.get()) == -1){
            cout << "\nUnable parse line. \nNetlist file containts errors." << endl;
            return false;
        }
    }
	return true;
}

/*  
	Function: vector<string> read_netlist(string fileName)
	Function to read the contents of a netlist file into a vector of strings
	Parameters:
		- fileName: The name of the netlist file to read
	Returns:
		- A vector of strings containing the lines of the netlist file
*/
vector<string> read_netlist(string fileName)
{
    ifstream netlistFile(fileName); // Open the netlist file
    vector<string> netlist;    		// Create a vector to store the netlist
    string line;    // Temporary string to store each line read from the file

    // Check if the file is open and in good state
    if (netlistFile.is_open() && netlistFile.good()){
        // Read each line from the file until the end is reached
        while (getline(netlistFile, line)){
            netlist.push_back(line);	// Add the line to the netlist vector
        }
        netlistFile.close();      // Close the file after reading
    }
    return netlist;     // Return the netlist vector
}


/*
	Function: void write_Verilog_file(string circuitName, TopModule *topModule)
	Function to write the Verilog code to a file
	Parameters:
		- circuitName: The name of the Verilog file to write
		- topModule: Pointer to the top module of the design
*/

// Function to write Verilog file based on the provided circuit name and top module
void write_Verilog_file(string circuitName, TopModule *topModule) {
    // Open the Verilog file
    ofstream circuitFile;
    circuitFile.open(circuitName);

    // Write module name
    string moduleName = circuitName.substr(0, circuitName.size() - 2);
    topModule->writeModuleName(circuitFile, moduleName);

    // Write inputs, outputs, and wires
    topModule->writeInputs(circuitFile);
    topModule->writeOutputs(circuitFile);
    topModule->writeWires(circuitFile);

    circuitFile << endl;   // Add a newline for clarity
    topModule->writeModules(circuitFile); // Write module instances
    circuitFile << "\nendmodule" << endl;     // Write endmodule

    // Close the file
    circuitFile.close();
}
