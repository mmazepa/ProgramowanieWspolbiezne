#!/bin/bash
echo "[COMPILE]: Kompilowanie plików producent.c i konsument.c"
gcc -o producent producent.c
gcc -o konsument konsument.c
exit 0
