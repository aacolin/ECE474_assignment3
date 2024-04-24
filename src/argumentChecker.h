#ifndef ARGUMENTCHECKER_H
#define ARGUMENTCHECKER_H

#include <iostream>
#include <string>


/**
 * @brief The ArgumentChecker class.
 * 
 * This class is used to validate and process the command-line arguments provided by the user.
 */
class ArgumentChecker {

    public:
        ArgumentChecker(int argc, char* argv[]);    // Constructor with arguments
        bool checkArguments();                      // Check the validity of the arguments    
        int getLatency() const ;                    // Get the latency argument     

    private:
        int argc;                                   // Number of arguments
        char** argv;                                // Array of arguments
        int latency;                                // Latency argument
};

#endif 
