cmake_minimum_required(VERSION 3.6)
project(language_of_programming)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rfile.cpp reccirc.cpp reccirc.h)
add_executable(language_of_programming ${SOURCE_FILES})