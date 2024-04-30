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

The binary  hlsyn (high-level synthesizer) converts a C-like behavioral description into a
scheduled high-level statement machine implemented in Verilog.


The program uses command-line argument to specify the input and output files using the following syntax:
	
    Syntax:	 hlsyn <INPUT-cFile> <INPUT-latency> <OUTPUT-verilogFile>
	
             hlsyn cFile latency verilogFile

	Example: hlsyn hls_test1.c 10 hls_test1.v

Note: if the cFile is not located in the same folder as the binary dpgen, the full path to the 
netlistFile must be provided.

The verilog file will be placed in the same directory as the hlsyn binary

The included bash/zsh script test_hlsyn.sh can be used to build & test the binary hlsyn against all the 
test files but it is ultimately not a requirement, feel free to use it. 

4) Individual Contributions

Aaron Colin:
    - Implementation of argumentChecker class
    - Refactoring of circuitParser (parseContent and ifFinder methods added)
    - Implementation of verilog class
    - Documented classes, functions and hard to read code
    - Implementation of testing script test_hlsyn.sh
Michael Cesar-Torres:
    - Verified R-List scheduling protocol and functionality
    - If statement parsing and edge cases
    - Error checking and detection

