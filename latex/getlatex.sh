#!/bin/bash

g++ -std=c++17 -o getlatex getlatex.cpp -O2
./getlatex $1 > biblioteca.tex
rubber -d biblioteca
mv biblioteca.pdf ../pdf
rm tmp.cpp
rm getlatex biblioteca.aux biblioteca.toc biblioteca.out
rm -f biblioteca.rubbercache
