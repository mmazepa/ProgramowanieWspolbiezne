#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/mieszalnik mieszalnik.c
echo "Done!"
