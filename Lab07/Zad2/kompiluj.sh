#!/bin/bash
echo "[COMPILE]: Kompilowanie pliku kolko_i_krzyzyk.c"
mkdir -p bin
gcc -std=gnu99 -o bin/kolko_i_krzyzyk kolko_i_krzyzyk.c
exit 0
