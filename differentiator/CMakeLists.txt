cmake_minimum_required(VERSION 3.6)
project(differentiator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp binary_tree.cpp differentiator.cpp differentiator.h)
add_executable(differentiator ${SOURCE_FILES})