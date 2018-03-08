#!/bin/bash
declare -i x y
echo -n "Podaj liczbe calkowita: "
read x
./syn.sh $x &
y=x*x
wait $!
y=y+$?
echo "Wynik: $y"
exit 0
