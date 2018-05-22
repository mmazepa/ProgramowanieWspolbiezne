#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/wyznacznik wyznacznik.c -lpthread
echo "Done!"
