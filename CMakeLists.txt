cmake_minimum_required(VERSION 3.8)
project(cpp_not_so_simple_calculator_tomahawk)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Calculator.cpp Calculator.h Evaluable.hpp Tester.hpp)
add_executable(cpp_not_so_simple_calculator_tomahawk ${SOURCE_FILES})