#!/bin/bash
echo "[COMPILE]: Kompilowanie plików klient.c i serwer.c"
mkdir -p bin
gcc -o bin/klient klient.c
gcc -o bin/serwer serwer.c
exit 0
