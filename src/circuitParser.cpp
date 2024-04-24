/**
 * @file circuitParser.cpp
 * @brief This file defines the Parser class, which is responsible for parsing the input circuit file.
*/


#include "circuitParser.h"

/**
 * @brief Parses a line of the netlist file.
 * 
 * This function parses a line of the netlist file and extracts the necessary information to build the circuit.
 * It identifies the type of line (input, output, wire, register, or operation) and calls the appropriate function to parse it.
 * 
 * @param line The line to be parsed.
 * @param topModule The top module of the circuit.
 * @return An integer indicating whether the line was parsed successfully.
 */
int Parser::parseLine(string line, TopModule * topModule) {
    istringstream lineStream(line);
    string identifier;
    lineStream >> identifier;

    if (identifier == INPUT) {
        topModule->setInputs(Parser::parseInput(line));
    } else if (identifier == OUTPUT) {
        topModule->setOutputs(Parser::parseOutput(line));
    } else if (identifier == WIRE) {
        topModule->setWires(Parser::parseWire(line));
    } else if (identifier == REGISTER || identifier == VARIABLE) {
        topModule->setRegisters(Parser::parseRegister(line));
        topModule->setWires(Parser::parseRegister(line));
    } else if (identifier != EMPTY && identifier.substr(0,2) != COMMENT) {
        HwComponent *temp = Parser::parseOperation(line, *topModule);
        if (temp->getOperation() == ERROR) {
            return -1; // report error
        } else {
            topModule->addModule(temp);
        }
    }
    return 0; // return no error
}



/**
 * @brief Parses the content of the netlist file.
 * 
 * This function parses the content of the netlist file and extracts the necessary information to build the circuit.
 * It identifies the type of line (input, output, wire, register, or operation) and calls the appropriate function to parse it.
 * 
 * @param lines The lines of the netlist file.
 * @param topModule The top module of the circuit.
 * @return An integer indicating whether the content was parsed successfully.
 */
int Parser::parseContent(vector<string> lines, TopModule * topModule) {
    for (unsigned int i = 0; i < lines.size(); i++) {
        if (lines[i].substr(0, 2) == IF) {
            i = ifFinder(i, lines, topModule);
        } else {
            if (Parser::parseLine(lines[i], topModule) == -1) {
                return -1; // report error
            }
        }
    }
    return 0; // return no error
}


/**
 * @brief Finds the if statement in the netlist file.
 * 
 * This function finds the if statement in the netlist file and extracts the necessary information to build the circuit.
 * It identifies the true and false computations and creates the necessary components to implement the if statement.
 * 
 * @param index The index of the if statement in the netlist file.
 * @param lines The lines of the netlist file.
 * @param topModule The top module of the circuit.
 * @return An integer indicating the index of the next line to be parsed.
 */

int Parser::ifFinder(int index, vector<string>& lines, TopModule * topModule)
{
	
	map<int, string> trueComputations;
	map<int, string> falseComputations;
	vector<int> falseSoloComputations; 
	unsigned int lineIndex;
	string elseIdentifier = "";
	stringstream variable(lines.at(index));
	string if_dummy, parenthesis_dummy, ifVariable;
	variable >> if_dummy >> parenthesis_dummy >> ifVariable;
	

	// for loop to find the true and false computations
	for (lineIndex = index + 1; lineIndex < lines.size(); ++lineIndex) {
		const auto& line = lines[lineIndex];
		std::istringstream lineStream(line);
		std::string nextIdentifier;
		lineStream >> nextIdentifier;

		if (nextIdentifier == "}") {
			index = lineIndex + 1;
			std::istringstream ss(lines.size() > index ? lines[index] : " ");
			ss >> elseIdentifier;
			break;
		}
		else if (nextIdentifier == EMPTY || nextIdentifier.substr(0, 2) == COMMENT) {
			continue;
		}
		else if (nextIdentifier == IF) {
			lineIndex = ifFinder(lineIndex, lines, topModule);
		}
		else {
			trueComputations.emplace(lineIndex, line);
		}
	}

	if (elseIdentifier == ELSE) {
		for (lineIndex = index + 1; lineIndex < lines.size(); ++lineIndex) {
			const auto& line = lines[lineIndex];
			std::istringstream lineStream(line);
			std::string nextIdentifier;
			lineStream >> nextIdentifier;

			if (nextIdentifier == "}") {
				break;
			}
			else if (nextIdentifier == EMPTY || nextIdentifier.substr(0, 2) == COMMENT) {
				continue;
			}
			else if (nextIdentifier == IF) {
				lineIndex = ifFinder(lineIndex, lines, topModule);
			}
			else {
				falseComputations.emplace(lineIndex, line);
				falseSoloComputations.emplace_back(lineIndex);
			}
		}
	}

	vector<Wire*> trueWires;
	vector<Wire*> falseWires;
	bool inBoth = false; 
	bool inFile = false; 

	for (auto& operationLine1 : trueComputations) {
		inBoth = false;
		inFile = false;
		stringstream inputStream1(operationLine1.second);
		string outputName1;
		inputStream1 >> outputName1;
		Wire* output1 = topModule->findOutputWire(outputName1);
		for (auto& operationLine2 : falseComputations) {
			string outputName2;
			stringstream(operationLine2.second) >> outputName2;
			Wire* output2 = topModule->findOutputWire(outputName2);

			if (outputName1 != outputName2) continue;

			inBoth = inFile = true;
			falseSoloComputations.erase(remove(falseSoloComputations.begin(), falseSoloComputations.end(), operationLine2.first), falseSoloComputations.end());

			operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), (outputName1 + " =").length(), outputName1 + "_True =");
			operationLine2.second.replace(operationLine2.second.find(outputName2 + " ="), (outputName2 + " =").length(), outputName2 + "_False =");

			Wire* trueWire = new Wire(outputName1 + "_True", output1->getType());
			Wire* falseWire = new Wire(outputName1 + "_False", output2->getType());
			topModule->addWire(*trueWire);
			topModule->addWire(*falseWire);

			HwComponent* trueModule = parseOperation(operationLine1.second, *topModule);
			HwComponent* falseModule = parseOperation(operationLine2.second, *topModule);
			trueWire->setPrev(trueModule);
			falseWire->setPrev(falseModule);
			topModule->addModule(trueModule);
			topModule->addModule(falseModule);

			vector<Wire*> inputWires = {trueWire, falseWire, topModule->findInputWire(ifVariable)};
			Wire* outputWire = topModule->findOutputWire(outputName1);
			string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
			HwComponent* mux = new  HwComponent("MUX", inputWires, outputWire, operationString);
			topModule->addModule(mux);
		}
		if (!inBoth) {
			for (int i = 0; i < lines.size(); i++) {
				stringstream inputStream2(lines.at(i));
				string outputName2;
				inputStream2 >> outputName2;
				Wire* output2 = topModule->findOutputWire(outputName2);
				if (outputName1 == outputName2 && i != operationLine1.first) {
					if (i < operationLine1.first) { // Will go in here if the matching statement is before the if statement
						// Create the True module and wire and the false wire
						operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True ="); // change operation line so has {var_name}_True
						Wire* trueWire = new Wire(outputName1 + "_True", output1->getType()); // creating the new wires that will be inputs into the mux
						Wire* falseWire = new Wire(outputName1 + "_False", output2->getType());
						falseWire->setNext(topModule->findOutputWire(outputName1)->next); // connected the false wire to where the previous wire was, as that wire will now be the output of the mux
						falseWire->setPrev(topModule->findOutputWire(outputName1)->prev);
						// Making previous module be connected to false wire
						topModule->findOutputWire(outputName1)->prev->setOutput(falseWire);
						string operationLine = topModule->findOutputWire(outputName1)->prev->getOperationLine();
						operationLine.replace(operationLine.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_False =");
						topModule->findOutputWire(outputName1)->prev->setOperationLine(operationLine);
						topModule->addWire(*falseWire);
						topModule->addWire(*trueWire);
						HwComponent* trueModule = parseOperation(operationLine1.second, *topModule);
						trueWire->setPrev(trueModule);
						topModule->addModule(trueModule);
						
						// Creating the mux
						vector<Wire*> inputWires = { trueWire, falseWire, topModule->findInputWire(ifVariable) };
						Wire* outputWire = topModule->findOutputWire(outputName1);
						string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
						HwComponent* mux = new  HwComponent("MUX", inputWires, outputWire, operationString);
						topModule->addModule(mux);

					}
					else { // Will go in here if the matching statement is after the if statement
						// Create the True and False modules and wires
						operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True =");
						lines.at(i).replace(lines.at(i).find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_False =");
						
						// Creating both the wires
						Wire* trueWire = new Wire(outputName1 + "_True", output1->getType());
						Wire* falseWire = new Wire(outputName1 + "_False", output2->getType());
						topModule->addWire(*trueWire);
						topModule->addWire(*falseWire);

						// Creating the modules and attaching the wires
						HwComponent* trueModule = parseOperation(operationLine1.second, *topModule);
						HwComponent* falseModule = parseOperation(lines.at(i), *topModule);
						trueWire->setPrev(trueModule);
						falseWire->setPrev(falseModule);
						topModule->addModule(trueModule);
						topModule->addModule(falseModule);

						// Creating the Mux
						vector<Wire*> inputWires = { trueWire, falseWire, topModule->findInputWire(ifVariable) };
						Wire* outputWire = topModule->findOutputWire(outputName1);
						string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
						HwComponent* mux = new  HwComponent("MUX", inputWires, outputWire,  operationString);
						topModule->addModule(mux);
						lines.erase(lines.begin() + i);
					}
					inFile = true;
					break;
				}
			}
		}
		if (!inFile) { 
			HwComponent* trueModule = parseOperation(operationLine1.second, *topModule); 
			topModule->addModule(trueModule);
		}

	}

	for (int lineNumber : falseSoloComputations) { 
		HwComponent* trueModule = parseOperation(lines.at(lineNumber), *topModule); 
		topModule->addModule(trueModule);
	}

	return lineIndex;
}


/**
 * @brief Parses an input line.
 * 
 * This function parses an input line and extracts the necessary information to build the circuit.
 * It identifies the type of input (input or output) and creates the necessary components to implement the input.
 * 
 * @param inputString The input line to be parsed.
 * @return A vector of wires representing the inputs.
 */
vector<Wire> Parser::parseInput(string inputString)
{
	
	stringstream inputStream(inputString);
	vector<Wire> inputs;
	Wire bufferInput;
	string bufferName;
	string type;
	string dummy;

	inputStream >> dummy >> type;

	while (inputStream >> bufferName)
	{
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferInput = Wire(bufferName, type);
		inputs.push_back(bufferInput);
	}
	return inputs;
}


/**
 * @brief Parses an output line.
 * 
 * This function parses an output line and extracts the necessary information to build the circuit.
 * It identifies the type of output (input or output) and creates the necessary components to implement the output.
 * 
 * @param outputString The output line to be parsed.
 * @return A vector of wires representing the outputs.
 */
vector<Wire> Parser::parseOutput(string outputString)
{

	stringstream outputStream(outputString);
	vector<Wire> outputs;
	Wire bufferOutput;
	string bufferName;
	string type;
	string dummy;

	outputStream >> dummy >> type;

	while (outputStream >> bufferName)
	{
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferOutput = Wire(bufferName, type);
		outputs.push_back(bufferOutput);
	}
	return outputs;
}



/**
 * @brief Parses a wire line.
 * 
 * This function parses a wire line and extracts the necessary information to build the circuit.
 * It identifies the type of wire (input or output) and creates the necessary components to implement the wire.
 * 
 * @param wireString The wire line to be parsed.
 * @return A vector of wires representing the wires.
 */
vector<Wire> Parser::parseWire(string wireString)
{
	stringstream wireStream(wireString);
	vector<Wire> wires;
	Wire bufferWire;
	string bufferName;
	string type;
	string dummy;

	wireStream >> dummy >> type;

	while (wireStream >> bufferName)
	{
		if (!isalnum(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = Wire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}


/**
 * @brief Parses a register line.
 * 
 * This function parses a register line and extracts the necessary information to build the circuit.
 * It identifies the type of register (input or output) and creates the necessary components to implement the register.
 * 
 * @param registerString The register line to be parsed.
 * @return A vector of wires representing the registers.
 */
vector<Wire> Parser::parseRegister(string registerString)
{
	stringstream registerStream(registerString);
	vector<Wire> registers;
	Wire bufferWire;
	string bufferName;
	string type;
	string dummy;

	registerStream >> dummy >> type;

	while (registerStream >> bufferName)
	{
		if (!isalnum(bufferName.back()))		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = Wire(bufferName, type);
		registers.push_back(bufferWire);
	}
	return registers;
}


/**
 * @brief Parses an operation line.
 * 
 * This function parses an operation line and extracts the necessary information to build the circuit.
 * It identifies the type of operation (addition, subtraction, multiplication, etc.) and creates the necessary components to implement the operation.
 * 
 * @param operationString The operation line to be parsed.
 * @param topModule The top module of the circuit.
 * @return A pointer to the hardware component representing the operation.
 */
HwComponent* Parser::parseOperation(string operationString, TopModule &topModule)
{
    std::string dummy, operatorChar, inputChar1, inputChar2, inputChar3, outputChar;
    std::vector<Wire*> inputWires;
    Wire* outputWire;
    std::stringstream ss(operationString);
    HwComponent *opModule = NULL;

    ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3;

    std::map<std::string, std::string> operatorMap = {
        {ADD, "ADD"}, {SUB, "SUB"}, {MUL, "MUL"}, {GT, "GT"}, {LT, "LT"}, {EQ, "EQ"}, 
        {SEL, "MUX"}, {SHR, "SHR"}, {SHL, "SHL"}, {DIV, "DIV"}, {MOD, "MOD"}, {REG, "REG"}
    };

    auto findAndPushInputWire = [&](const std::string& inputChar) {
        Wire* tempInput = topModule.findInputWire(inputChar);
        if (tempInput == NULL) {
            opModule = new HwComponent("ERROR");
            return false;
        }
        inputWires.push_back(tempInput);
        return true;
    };

    inputWires.push_back(topModule.findInputWire(inputChar1));
    if (inputChar2.compare("\0") != 0 && inputChar2.compare("1") != 0 && !findAndPushInputWire(inputChar2)) 
        return opModule;
    if (inputChar3.compare("\0") != 0 && !findAndPushInputWire(inputChar3)) 
        return opModule;

    outputWire = topModule.findOutputWire(outputChar);
    if (outputWire == NULL) {
        opModule = new HwComponent("ERROR");
        return opModule;
    }

    if (operatorChar.compare(ADD) == 0 && inputChar2 == "1") 
        operatorChar = "INC";
    else if (operatorChar.compare(SUB) == 0 && inputChar2 == "1") 
        operatorChar = "DEC";

    if (operatorMap.find(operatorChar) != operatorMap.end()) 
        opModule = new HwComponent(operatorMap[operatorChar], inputWires, outputWire, operationString);
    else 
        opModule = new HwComponent("ERROR");

    return opModule;
}