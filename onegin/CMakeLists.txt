cmake_minimum_required(VERSION 3.6)
project(onegin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rfile.cpp rfile.h)
add_executable(onegin ${SOURCE_FILES})