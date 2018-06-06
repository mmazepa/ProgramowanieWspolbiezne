#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/klient klient.c -lX11 #-Wall
gcc -o bin/serwer serwer.c -lX11 #-Wall
echo "Done!"
