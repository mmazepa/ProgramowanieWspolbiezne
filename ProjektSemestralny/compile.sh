#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/klient klient.c #-Wall
gcc -o bin/serwer serwer.c #-Wall
echo "Done!"
