#!/bin/bash
echo "[COMPILE]: Kompilowanie plików producent.c i konsument.c"
mkdir -p bin
gcc -o bin/producent producent.c
gcc -o bin/konsument konsument.c
exit 0
