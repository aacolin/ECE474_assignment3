
# CMake Setup for Compiling dpgen. 
# This setup utilizes a single subdirectory (src)
# for all source (.cpp) and header (.h) files 

# CMake projects are forward compatible, but may not be backwards compatible. This
# commands defines the version of CMake used for the current setup.

cmake_minimum_required(VERSION 3.20)

# Use C++11
set (CMAKE_CXX_STANDARD 11)

# project name. 
project ( hlsyn )

# Add /src subdirectory to the project. 
add_subdirectory( src )
