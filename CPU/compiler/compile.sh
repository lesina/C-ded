#!/bin/bash

g++ -c compiler.cpp rfile.cpp --std=c++11;
g++ compiler.o rfile.o -o compiler;
./compiler;
cp comp ../;
cp comp ../decompiler/;
rm *.o;
