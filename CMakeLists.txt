# Example how to instrument project with instructions for CMake to 
# build Makefiles for src code and test code using CppUTest framework 
# https://r4nd0m6uy.ch/cmake-and-cpputest.html
# Builds src into static library that can be linked against 
# our production application (main) or test main to run tests optionally 

# (1) CMake definitions, compiler flags and useful variables
cmake_minimum_required(VERSION 3.7)
project(CodingProblemsDemo)

# Check for CppUTest and bail out if they don't have it
if(DEFINED ENV{CPPUTEST_HOME})
  message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
else()
  message("CPPUTEST_HOME is not set; You must tell CMake where to find CppUTest")
  return()
endif()

enable_language(C)
enable_language(CXX)

set(APP_NAME CodingProblemsApp)
set(APP_LIB_NAME CodingProblemsLib)

# (2) Include application build instructions
add_subdirectory(src)

# (3) include tests build instructions   
option(COMPILE_TESTS "Compile the tests" OFF)
if(COMPILE_TESTS)
  add_subdirectory(tests)
endif(COMPILE_TESTS)
