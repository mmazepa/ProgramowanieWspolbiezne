#!/bin/bash
echo "+------------------------------------------------+"
echo "| [COMPILE]: Kompilowanie plików komk.c i koms.c |"
echo "+------------------------------------------------+"
mkdir -p bin
echo "+--------------------------------------+"
echo "| [COMPILE]: Kompilowanie pliku komk.c |"
echo "+--------------------------------------+"
gcc -o bin/komk komk.c
echo "+--------------------------------------+"
echo "| [COMPILE]: Kompilowanie pliku koms.c |"
echo "+--------------------------------------+"
gcc -o bin/koms koms.c
exit 0
