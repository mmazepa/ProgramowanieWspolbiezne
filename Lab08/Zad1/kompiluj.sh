#!/bin/bash
# echo "[COMPILE]: Kompilowanie plików klient.c i serverstud.c"
echo "[COMPILE]: Kompilowanie pliku klient.c"
mkdir -p bin
gcc -o bin/klient klient.c -lm
# gcc -o bin/serverstud serverstud.c
exit 0
