#!/bin/bash
printf "\n"
printf "  KLIENT\n"
echo "  --------------------------"

if [ -f dane ] ; then
    rm dane
fi

if [ -f wynik ] ; then
    rm wynik
fi

echo "  Wielomian:    x^2 + 4x + 4"
printf "  Podaj liczbę: "
read -r liczba
echo $liczba > dane

while true
	do
		if [ -s wynik ]
			then
				#plik istnieje i nie jest pusty
				read rezultat < wynik
				rm wynik
				echo "  Wynik:        $rezultat"
				break
			#else
				#plik nie istnieje lub jest pusty
		fi
	done

echo "  --------------------------"
printf "\n"
exit 0
