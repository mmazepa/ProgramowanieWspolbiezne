#!/bin/bash
echo "  Serwer oczekuje na zgłoszenia..."
while true
	do
		if [ -s dane ]
		then
			read liczba < dane
			rm dane
			echo "$((liczba ** 2 + 4 * liczba + 4))" > wynik
		fi
	done
exit 0
