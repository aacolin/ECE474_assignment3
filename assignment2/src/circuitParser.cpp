#include "circuitParser.h"  // Including the header file for the circuit parser

// Function to remove trailing commas from a string
void remove_commas(string& str) {
    // Check if the string is not empty
    if (!str.empty()) {
        // Check if the last character of the string is a comma
        if (str.back() == ',') {
            // Remove the trailing comma by reducing the length of the string
            str.pop_back();
        }
    }
}

// Function to parse a line of input and update the top module
int CircuitParser::parseLine(string inputLine, TopModule* topModule) {
    istringstream lineStream(inputLine); 	// Create a string stream from the input line
    string lineType;
    lineStream >> lineType;				    // Extract the line type from the input line

    // Check if the line is empty or a comment; if so, ignore it
    if (lineType.empty() || lineType.substr(0, 2) == COMMENT) {
        return 0; // Return 0 to indicate successful parsing
    }

    // Parse the line based on its type
    if (lineType == INPUT || lineType == OUTPUT || lineType == WIRE || lineType == REGISTER) {
        // If the line type is INPUT, OUTPUT, WIRE, or REGISTER, parse corresponding signals and set them in topModule
        if (lineType == REGISTER) {
            topModule->setRegisters(CircuitParser::parseRegister(inputLine));
            topModule->setWires(CircuitParser::parseRegister(inputLine)); // Also set wires (assuming registers are also wires)
        } else if (lineType == INPUT) {
            topModule->setInputs(CircuitParser::parseInput(inputLine));
        } else if (lineType == OUTPUT) {
            topModule->setOutputs(CircuitParser::parseOutput(inputLine));
        } else if (lineType == WIRE) {
            topModule->setWires(CircuitParser::parseWire(inputLine));
        }
    } else {
        // If the line is an operator, parse the operation and add it to topModule
        HwComponent temp = CircuitParser::parseOperation(inputLine, *topModule);
        // Check if parsing resulted in an error
        if (temp.getOperation() == ERROR) {
            // If an error occurred, print an error message and return -1
            cout << "Error in line --> " << inputLine <<  endl;
            return -1; // Return -1 to indicate an error during parsing
        }
        topModule->addModule(temp);    // If parsing was successful, add the parsed module to topModule
    }
    return 0;
}



// Function to parse the input string and create Wire objects for each input
vector<Wire> CircuitParser::parseInput(string inputString)
{	
    stringstream inputStream(inputString);	    // Creating a stringstream to process the input string
    vector<Wire> inputs;					    // Vector to store the parsed input wires
    Wire bufferInput;    	// Temporary Wire object to hold each input wire
	string bufferName, wireType, emptyChar;		// Temporary variables to store wire name, wireType, and an empty character for parsing

    inputStream >> emptyChar >> wireType;	   // Extracting the wireType of wires from the input stream

    // Looping through the input stream to extract each input wire
    while (inputStream >> bufferName)
    {
        remove_commas(bufferName);		        // Removing any commas from the wire name
        bufferInput = Wire(bufferName, wireType);   // Creating a Wire object with the extracted name and wireType
        inputs.push_back(bufferInput);        	// Adding the Wire object to the vector of inputs
    }
    return inputs;    // Returning the vector of parsed input wires
}

// Function to parse the output string and return a vector of Wire objects
vector<Wire> CircuitParser::parseOutput(string outputString)
{
	stringstream outputStream(outputString);	// Creating a stringstream from the outputString for easier parsing
	vector<Wire> outputs;	// Vector to store the parsed output wires
	Wire bufferOutput;		// Temporary Wire object to hold each parsed wire
	string bufferName, wireType, emptyChar;		// Temporary variables to store wire name, wireType, and an empty character for parsing

	outputStream >> emptyChar >> wireType;	// Extracting the wireType of wires from the stringstream

	// Looping through the stringstream to extract each wire name
	while (outputStream >> bufferName)
	{
		remove_commas(bufferName);		// Removing commas between outputs
		bufferOutput = Wire(bufferName, wireType);		// Creating a Wire object with the extracted name and wireType
		outputs.push_back(bufferOutput);			// Adding the Wire object to the vector of outputs
	}

	return outputs;	// Returning the vector of parsed output wires
}

// Function to parse wire string and return vector of wires
vector<Wire> CircuitParser::parseWire(string wireString)
{
    stringstream wireStream(wireString); // Creating string stream from wire string
    vector<Wire> wires; // Vector to store wires
    Wire bufferWire;    // Temporary wire object to store parsed wires
    string bufferName, wireType, emptyChar;    // Temporary variables to store wire name, wireType, and an empty character for parsing
    
    wireStream >> emptyChar >> wireType;    // Parsing the wire string to extract wire wireType

    // Looping to parse wire names and create wire objects
    while (wireStream >> bufferName)
    {
        remove_commas(bufferName);        // Remove commas between wires
        bufferWire = Wire(bufferName, wireType); // Creating wire object with name and wireType
        wires.push_back(bufferWire); // Adding wire object to vector
    }
    
    return wires; 	// Returning vector of wires
}
//Function to parse register string and return vector of wires
vector<Wire> CircuitParser::parseRegister(string registerString)
{
	stringstream registerStream(registerString); //Creating string stream from registerString
	vector<Wire> registers; 	//Vector to store registers
	Wire bufferWire; 			//Temporary wire object to store parsed wires
	string bufferName; 			//Temporary string to store wire names
	string wireType; 			//Type of wires (e.g., input, output, wire)
	string emptyChar;			 //Empty character for parsing

	registerStream >> emptyChar >> wireType; 	//Parsing register stream to extract wire type


	//Looping to parse wire names and create wire objects
	while (registerStream >> bufferName)
	{
		remove_commas(bufferName); //removes commas between wires
		bufferWire = Wire(bufferName, wireType); //Creating wire object with name and type
		registers.push_back(bufferWire); //Adding wire object to vector
	}

	return registers; //Returning vector of registers
}


HwComponent CircuitParser::parseOperation(string operationType, TopModule &topModule)
{
	string emptyChar, operatorChar, inputChar1, inputChar2, inputChar3, outputChar;
	vector<string> inputs;
	std::vector<Wire*> inputWires;
	Wire* outputWire;
	Wire* outputWire2;
	Wire* tempInput = NULL;
	stringstream operationTypeStream(operationType);
	HwComponent *opModule = NULL;
	
	operationTypeStream >> outputChar >> emptyChar >> inputChar1 >> operatorChar >> inputChar2 >> emptyChar >> inputChar3;

	inputWires.push_back(topModule.findInputWire(inputChar1));
	if (inputChar2.compare("\0") != 0 && inputChar2.compare("1") != 0) 
	{ 
		tempInput = topModule.findInputWire(inputChar2);
		if (tempInput == NULL) {
			opModule = new HwComponent("ERROR"); 
			return *opModule;
		}
		inputWires.push_back(tempInput); 
	}
	if (inputChar3.compare("\0") != 0) 
	{ 
		tempInput = topModule.findInputWire(inputChar2);
		if (tempInput == NULL) {
			opModule = new HwComponent("ERROR"); 
			return *opModule;
		}
		inputWires.push_back(tempInput); 
	}
	
	outputWire = topModule.findOutputRegister(outputChar);
	if (outputWire != NULL) {
		if (operatorChar.compare("\0") == 0) {
			outputWire = topModule.findOutputWire(outputChar);
			opModule = new HwComponent("REG", inputWires, outputWire);
			return *opModule;
		}
		else {
			outputWire2 = new Wire(outputWire->getName() + "_0", outputWire->getType());
			
			if (operatorChar.compare(ADD) == 0) {
				if (inputChar2 == "1") {
					opModule = new HwComponent("INC", inputWires, outputWire2);
				}
				else {
					opModule = new HwComponent("ADD", inputWires, outputWire2);
				}
			}
			else if (operatorChar.compare(SUB) == 0) {
				if (inputChar2 == "1") {
					opModule = new HwComponent("DEC", inputWires, outputWire2);
				}
				else {
					opModule = new HwComponent("SUB", inputWires, outputWire2);
				}
			}
			else if (operatorChar.compare(MUL) == 0) {
				opModule = new HwComponent("MUL", inputWires, outputWire2);
			}
			else if (operatorChar.compare(GT) == 0) {
				opModule = new HwComponent("GT", inputWires, outputWire2);
			}
			else if (operatorChar.compare(LT) == 0) {
				opModule = new HwComponent("LT", inputWires, outputWire2);
			}
			else if (operatorChar.compare(EQ) == 0) {
				opModule = new HwComponent("EQ", inputWires, outputWire2);
			}
			else if (operatorChar.compare(SEL) == 0) {
				opModule = new HwComponent("MUX", inputWires, outputWire2);
			}
			else if (operatorChar.compare(SHR) == 0) {
				opModule = new HwComponent("SHR", inputWires, outputWire2);
			}
			else if (operatorChar.compare(SHL) == 0) {
				opModule = new HwComponent("SHL", inputWires, outputWire2);
			}
		
			topModule.addModule(*opModule);
			outputWire = topModule.findOutputWire(outputChar);
			vector<Wire*> temp;
			temp.push_back(outputWire2);
			opModule = new HwComponent("REG", temp, outputWire);
			topModule.addWire(*outputWire2);
			return *opModule;
		}
	}
	outputWire = topModule.findOutputWire(outputChar);
	if (outputWire == NULL) {
		opModule = new HwComponent("ERROR"); 
		return *opModule;
	}
	if (operatorChar.compare(ADD) == 0) {
		if (inputChar2 == "1") {
			opModule = new HwComponent("INC", inputWires, outputWire);
		}
		else {
			opModule = new HwComponent("ADD", inputWires, outputWire);
		}
	}
	else if(operatorChar.compare(SUB) == 0) {
		if (inputChar2 == "1") {
			opModule = new HwComponent("DEC", inputWires, outputWire);
		}
		else {
			opModule = new HwComponent("SUB", inputWires, outputWire);
		}
	}
	else if(operatorChar.compare(MUL) == 0) {
		opModule = new HwComponent("MUL", inputWires, outputWire);
	}
	else if(operatorChar.compare(GT) == 0) {
		opModule = new HwComponent("GT", inputWires, outputWire);
	}
	else if(operatorChar.compare(LT) == 0) {
		opModule = new HwComponent("LT", inputWires, outputWire);
	}
	else if(operatorChar.compare(EQ) == 0) {
		opModule = new HwComponent("EQ", inputWires, outputWire);
	}
	else if(operatorChar.compare(SEL) == 0) {
		opModule = new HwComponent("MUX", inputWires, outputWire);
	}
	else if(operatorChar.compare(SHR) == 0) {
		opModule = new HwComponent("SHR", inputWires, outputWire);
	}
	else if(operatorChar.compare(SHL) == 0) {
		opModule = new HwComponent("SHL", inputWires, outputWire);
	}
	else if(operatorChar.compare(REG) == 0) {
		opModule = new HwComponent("REG", inputWires, outputWire); 
	}
	else {
		opModule = new HwComponent("ERROR"); 
	}



	return *opModule;
}
