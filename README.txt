1) Name and NetIDs

Aaron Colin Del Angel	aaroncolin
Michael Cesar-Torres    mcesartorres
Tej Scott               tfscott
George Collias          gcollias          

2) Course

Aaron Colin Del Angel	474a
Michael Cesar-Torres    474a
Tej Scott               474a
George Collias          474a 

3) Description

The binary dpgen (short for datapath generator) converts a behavioral netlist specification into a 
synthesizable Verilog datapath implementation.

The program uses command-line argument to specify the input and output files using the following syntax:
	
    Syntax:	dpgen <INPUT-netlistFile> <OUTPUT-verilogFile>\n
	
	Example: dpgen 474a_circuit1.txt circuit1.v

Note: if the netlistFile is not located in the same folder as the binary dpgen, the full path to the 
netlistFile must be provided.

The included bash script test_dpgen.sh can be used to build & test the binary dpgen against all the 
netlists (circuits) but it is ultimately not a requirement, feel free to use it. 

4) Individual Contributions

Aaron Colin Del Angel
- Implemented hardware component and wire class
- Implemented testing script test_dpgen.sh

Michael Cesar-Torres
- Implemented main.cpp
- Updated the library to include signed integer modules.
- Error checking for arguments

Tej Scott
- Implemented circuitParser.cpp

George Collias
- Implemented topModule.cpp
