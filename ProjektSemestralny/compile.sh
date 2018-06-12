#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/mieszalnik mieszalnik.c -lX11 -Wall

echo "Done!"
