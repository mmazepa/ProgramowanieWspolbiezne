#!/bin/bash
echo "[COMPILE]: Kompilowanie plików klient.c i serwer.c"
mkdir -p bin
gcc -o bin/klient klient.c -Wall
gcc -o bin/serwer serwer.c -Wall
exit 0
