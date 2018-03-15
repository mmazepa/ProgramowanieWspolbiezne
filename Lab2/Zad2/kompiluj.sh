#!/bin/bash
echo "[COMPILE]: Kompilowanie plików klient.c i serwer.c"
mkdir -p bin
gcc -o bin/klient klient.c
gcc -o bin/serwer serwer.c
rm -f dane.txt
rm -f wyniki.txt
rm -f bin/lockfile
exit 0
