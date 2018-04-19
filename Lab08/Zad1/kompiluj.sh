#!/bin/bash
echo "[COMPILE]: Kompilowanie plików klient.c i serverstud.c"
mkdir -p bin
gcc -o bin/klient klient.c
gcc -o bin/serverstud serverstud.c
exit 0
