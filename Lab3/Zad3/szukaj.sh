#!/bin/bash
declare -i ilosc_plikow
ilosc_plikow=0
CHILDREN=

if [ "$#" -lt 2 ]; then
	echo "Za mało argmentów, prawidłowy format to ./szukaj.sh [katalog] [plik]."
	exit
else
	if [ ! -d "$1" ]; then
		echo "'$1' nie jest katalogiem"
		exit
	fi
fi

for item in $1/*; do
	if [ -d "$item" ]; then
		"$0" "$item" "$2" "$$" &
		CHILDREN+=("$!")
	elif [ -f "$item" ]; then
		if [ $(basename $item) == "$2" ]; then
			echo "[$2]: $1"
			ilosc_plikow=$((ilosc_plikow+1))
		fi
	fi
done

for i in "${CHILDREN[@]}"; do
	if [ "$i" ]; then
		wait "$i"
		ilosc_plikow=$((ilosc_plikow+$?))
	fi
done

if [ -z "$3" ]; then
	if [ "$ilosc_plikow" -eq 0 ]; then
		echo "Nie znaleziono żadnego pliku."
	else
		echo "Znalezionych plików: $ilosc_plikow"
	fi
fi

exit "$ilosc_plikow"
