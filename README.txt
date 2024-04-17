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

	Example: hlsyn hls_test1.c hls_test1.v

Note: if the cFile is not located in the same folder as the binary dpgen, the full path to the 
netlistFile must be provided.

The included bash script test_hlsyn.sh can be used to build & test the binary hlsyn against all the 
test files but it is ultimately not a requirement, feel free to use it. 

4) Individual Contributions

