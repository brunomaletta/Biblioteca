#!/bin/bash

# Provide default values
: ${TEAMNAME:="Xerebêlerebébis"}
: ${MEMBERS:="Emanuel Silva, Bruno Monteiro \\& Rafael Grandsire"}
: ${UNIVERSITY:="UFMG"}

cat > env.tex <<EOF
\def\teamname{$TEAMNAME}
\def\teammembers{$MEMBERS}
\def\teamuni{$UNIVERSITY}
EOF

g++ -std=c++17 -o getlatex getlatex.cpp -O2
./getlatex $1 > biblioteca.tex
rubber -d biblioteca
mv biblioteca.pdf ../pdf
rm tmp.cpp
rm getlatex biblioteca.aux biblioteca.toc biblioteca.out
rm -f biblioteca.rubbercache

pushd ../theoretical
latexmk -pdf theoretical -outdir=../pdf
latexmk -pdf theoretical -outdir=../pdf -c
popd

rm env.tex
