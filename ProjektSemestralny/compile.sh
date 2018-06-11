#!/bin/bash
echo "Compiling files..."

binDirectory=bin

if [ ! -e $binDirectory ]; then
  mkdir $binDirectory
fi

gcc -o bin/mieszalnik mieszalnik.c -lX11 -Wall

gcc -o bin/shm_server shm_server.c
gcc -o bin/shm_client shm_client.c

echo "Done!"
