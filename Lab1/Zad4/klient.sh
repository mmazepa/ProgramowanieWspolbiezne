#!/bin/bash
printf "\n"
printf "  KLIENT\n"
echo "  --------------------------"

if [ -s dane ] ; then
    rm dane
fi

if [ -s wynik ] ; then
    rm wynik
fi

echo "  Wielomian:    x^2 + 4x + 4"
printf "  Podaj liczbę: "
read liczba
echo $liczba > dane

while true
	do
		if [ -s wynik ]
		then
			read rezultat < wynik
			rm wynik
			echo "  Wynik:        $rezultat"
			break
		fi
	done

echo "  --------------------------"
printf "\n"
exit 0
