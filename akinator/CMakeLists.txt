cmake_minimum_required(VERSION 3.6)
project(akinator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp binary_tree.cpp binary_tree.h akinator.cpp akinator.h)
add_executable(akinator ${SOURCE_FILES})