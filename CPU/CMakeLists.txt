cmake_minimum_required(VERSION 3.6)
project(CPU)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp stack.cpp rfile.cpp)
add_executable(CPU ${SOURCE_FILES})