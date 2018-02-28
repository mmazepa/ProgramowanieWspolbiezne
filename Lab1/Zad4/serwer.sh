#!/bin/bash
echo "  Serwer oczekuje na zgłoszenia..."
while true
	do
		if [ -s dane ]
			then
				#plik istnieje i nie jest pusty
				read liczba < dane
				rm dane
				echo "$((liczba ** 2 + 4 * liczba + 4))" > wynik
			#else
				#plik nie istnieje lub jest pusty
		fi
	done
exit 0
