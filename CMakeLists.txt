cmake_minimum_required(VERSION 3.21)
project(gramatic_calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(gramatic_calculator main.cpp Token.cpp Token.h grammar.cpp grammar.h Token_stream.cpp Token_stream.h)
