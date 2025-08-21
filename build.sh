#!/bin/sh

rm -r bin
rm -r build

mkdir bin
mkdir build
mkdir build/src

echo "Redid Folder Structure"

g++ -c src/main.cpp -o build/src/main.cpp.o

echo "Compiled Program"

g++ build/src/main.cpp.o -o bin/brik

echo "Linked Executable"
