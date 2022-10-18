g++ -std=c++17 -o getlatex getlatex.cpp
./getlatex $1 > biblioteca.tex
rubber -d biblioteca
mv biblioteca.pdf ../pdf
rm tmp.cpp
rm getlatex biblioteca.aux biblioteca.toc biblioteca.out
