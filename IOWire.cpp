#include "IOWire.h"

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

void IOWire::setPrev(Module *prev){
	this->prev = prev;
	return;
}

void IOWire::setName(string name){
	this->name = name;
}

void IOWire::setNext(vector<Module*> next){
	this->next = next;
	return;
}

void IOWire::addNext(Module *next){
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