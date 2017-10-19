#!/bin/bash

g++ -c decompiler.cpp rfile.cpp --std=c++11;
g++ decompiler.o rfile.o -o decompiler;
./decompiler;
rm *.o;
