/**
 * @file verilog.cpp
 * 
 * @brief This file defines the Verilog class, which is responsible for processing the circuit and generating the Verilog output file.
 * 
 * The Verilog class is responsible for processing the circuit and generating the Verilog output file.
 * It reads the netlist file, parses the content, calculates the minimum latency, forces the schedule for each module,
 * and creates the output file.
 * 
 * 		- The processCircuit method processes the circuit and generates the output file.
 * 		- It reads the netlist file, parses the content, calculates the minimum latency, forces the schedule for each module, and creates the output file.
 * 		- The readNetlist method reads the netlist file and returns the contents as a vector of strings.
 * 		- The writeToFile method writes the circuit to the output file.
 * 		- The makeOutputFile method creates the output file.
 * 		- The Verilog constructor initializes the circuit name, latency, and output file name.
 * 
*/


#include "verilog.h"

/**
 * @brief Constructs a Verilog object.
 * 
 * This constructor initializes a Verilog object with the given circuit name, latency, and output file name.
 * 	
 * @param circuitName The name of the circuit file.
 * @param latency The latency of the circuit.
 * @param outputFileName The name of the output file.
 * 
*/
Verilog::Verilog(const string& circuitName, int latency, const string& outputFileName) 
	: circuitName(circuitName), latency(latency), outputFileName(outputFileName)
{}

/**
 * @brief Processes the circuit and generates the output file.
 * 
 * This function processes the circuit and generates the output file.
 * It reads the netlist file, parses the content, calculates the minimum latency, forces the schedule for each module, and creates the output file.
 * 
 * @param circuitName The name of the circuit file.
 * @param latency The latency of the circuit.
 * @param outputFileName The name of the output file.
 * 
 * @return A boolean indicating whether the circuit was processed successfully.
 * 
*/

bool Verilog::processCircuit(const string& circuitName, int latency, const string& outputFileName) {
    // Initialize variables
    vector<string> netlistContents;
    TopModule *topModule = new TopModule();

    // Read the netlist
    netlistContents = readNetlist(circuitName);

     // Check if the netlist is empty
    if (netlistContents.empty()) {
        cout << "Error: Unable to open the file '" << circuitName << "'. \nPlease ensure the file exists, is not in use by another program, and is not empty." << endl;
        delete topModule;
        return false;
    }

    // Parse the netlist content
    if (Parser::parseContent(netlistContents, topModule) == -1) {
        cout << "Error parsing file. Check the netlist file for errors." << endl;
        delete topModule;
        return false;
    }

    // Calculate the minimum latency
    int minLatency = topModule->calculateTimeFrames(latency);

    // Check if the entered latency is too small
    if (minLatency != 0) {
        cout << "Error: Invalid latency parameter. Expected latency >= " << minLatency  << endl;
        delete topModule;
        return false;
    }

    // Force schedule for each module
    for (size_t i = 0; i < topModule->modules.size(); i++) {
        topModule->forceSchedule(latency);
    }

    // Create the output file
    makeOutputFile(outputFileName, topModule);

    // Clean up
    delete topModule;

    return true;
}

/**
 * @brief Reads the netlist file and returns the contents as a vector of strings.
 * 
 * This function reads the netlist file and returns the contents as a vector of strings.
 * 
 * @param fileName The name of the netlist file.
 * 
 * @return A vector of strings containing the contents of the netlist file.
 * 
*/
vector<string> Verilog::readNetlist(const string& fileName){
    ifstream netlistFile(fileName);
    vector<string> netlistContents;

    if (!netlistFile){
        throw runtime_error("Unable to open file: " + fileName);
    }

    string line;
    while (getline(netlistFile, line)){
        netlistContents.push_back(line);
    }

    return netlistContents;
}


/**
 * @brief Writes the circuit to the output file.
 * 
 * This function writes the circuit to the output file.
 * 
 * @param circuitName The name of the circuit file.
 * @param topModule The top module of the circuit.
 * 
*/
void Verilog::writeToFile(string circuitName, TopModule *topModule) {
	ofstream circuitFile;
	circuitFile.open(circuitName);
	topModule->printModuleName(circuitFile, circuitName.substr(0, circuitName.size() - 2));
	topModule->printInputs(circuitFile);
	topModule->printOutputs(circuitFile);
	topModule->printWires(circuitFile);
	circuitFile << endl;
	topModule->printModules(circuitFile);
	circuitFile << "\nendmodule" << endl << endl;
	circuitFile.close();
}

/**
 * @brief Creates the output file.
 * 
 * This function creates the output file.
 * 
 * @param circuitName The name of the circuit file.
 * @param topModule The top module of the circuit.
 * 
*/
void Verilog::makeOutputFile(string circuitName, TopModule *topModule) {
	int maxSize = 0;

	for (HwComponent* a : topModule->modules) {
		if (a->getTimeFrame().at(0) > maxSize) {
			maxSize = a->getTimeFrame().at(0);
		}
	}
	
	maxSize = maxSize + 2;

	ofstream circuitFile;
	circuitFile.open(circuitName);

	topModule->printModuleName(circuitFile, "HLSM ");
	circuitFile << "\tinput Clk, Rst, Start;" << endl;
	circuitFile << "\toutput reg Done;" << endl;
	circuitFile << "\treg [" << ceil(log2(maxSize)) << ":0] Case;" << endl << endl;
	topModule->printInputs(circuitFile);
	topModule->printOutputs(circuitFile);
	topModule->printWires(circuitFile);
	circuitFile << endl << "\tinitial begin" << endl;
	circuitFile << "\t\tDone <= 0;" << endl;
	circuitFile << "\t\tCase <= 0;" << endl;
	circuitFile << "\tend" << endl << endl;
	circuitFile << "\talways @(posedge Clk) begin" << endl;
	circuitFile << "\t\tif (Rst) begin" << endl;
	circuitFile << "\t\t\tDone <= 0;" << endl;
	circuitFile << "\t\t\tCase <= 0;" << endl;
	circuitFile << "\t\tend" << endl << endl;
	circuitFile << "\t\tif (Start && Case == 0) begin" << endl;
	circuitFile << "\t\t\tCase <= Case + 1;" << endl;
	circuitFile << "\t\t\tDone <= 0;" << endl;
	circuitFile << "\t\tend" << endl;
	
	// Iterate over each case, excluding the first and last
	for (unsigned int i = 1; i < maxSize - 1; i++) {
		circuitFile << "\t\telse if (Case == " << i << ") begin" << endl;

		// Iterate over each module in the top module
		for (const auto& module : topModule->modules) {
			// Get the time frame and operation for readability
			int timeFrame = module->getTimeFrame().at(0);
			string operation = module->getOperation();

			// Check if the operation is MOD or DIV and it's the right time frame
			if ((i == timeFrame - 2) && (operation == "MOD" || operation == "DIV")) {
				circuitFile << "\t\t\t" << module->getOperationLine() << ";" << endl;
			}
			// Check if the operation is MUL and it's the right time frame
			else if ((i == timeFrame - 1) && operation == "MUL") {
				circuitFile << "\t\t\t" << module->getOperationLine() << ";" << endl;
			}
			// Check if the operation is not MOD, DIV, or MUL and it's the right time frame
			else if (i == timeFrame && operation != "MOD" && operation != "DIV" && operation != "MUL") {
				circuitFile << "\t\t\t" << module->getOperationLine() << ";" << endl;
			}
		}

		circuitFile << "\t\t\tCase <= Case + 1;" << endl;
		circuitFile << "\t\tend" << endl;
	}
	circuitFile << "\t\telse if (Case == " << maxSize - 1 << ") begin" << endl;
	circuitFile << "\t\t\tDone <= 1;" << endl;
	circuitFile << "\t\t\tCase <= 0;" << endl;
	circuitFile << "\t\tend" << endl;
	circuitFile << "\tend" << endl << endl;
	circuitFile << "endmodule" << endl;
	circuitFile.close();
}