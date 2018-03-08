#!/bin/bash
declare -i liczba wynik
liczba=$1
wynik=1
while [ $liczba -ge 1 ];
do
wynik=$[$wynik * $liczba]
liczba=$[$liczba - 1]
done
# echo "[pp]: $1! = $wynik"
exit $wynik
