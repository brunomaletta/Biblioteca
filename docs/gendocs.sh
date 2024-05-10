#!/bin/bash

g++ -std=c++17 -o gendocs gendocs.cpp -O2
./gendocs $1
rm gendocs
