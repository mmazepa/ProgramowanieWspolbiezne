#!/bin/bash
declare -i ilosc_plikow
ilosc_plikow=0
procesy_potomne=""

if [ "$#" -lt 2 ]; then
	echo '[BŁĄD]: Za mało argumentów! Powinny być dokładnie 2.'
  echo '        Prawidłowy format: '$0' [katalog] [plik].'
	exit
else
	if [ ! -d "$1" ]; then
		echo "[PORAŻKA]: Katalog o nazwie '$1' nie został znaleziony."
		exit
	fi
fi

for item in $1/*; do
	if [ -d "$item" ]; then
		"$0" "$item" "$2" "trzeci_argument" &
		procesy_potomne+=("$!")
	elif [ -f "$item" ]; then
		if [ $(basename $item) == "$2" ]; then
			ilosc_plikow=$((ilosc_plikow+1))
      echo "[SUKCES]: Plik '$2' znajduje się w $1."
		fi
	fi
done

for i in "${procesy_potomne[@]}"; do
	if [ "$i" ]; then
		wait "$i"
		ilosc_plikow=$((ilosc_plikow+$?))
	fi
done

if [ -z "$3" ]; then
	if [ "$ilosc_plikow" -eq 0 ]; then
		echo "[PORAŻKA]: Nie znaleziono żadnego pliku o nazwie '$2' w katalogu '$1'."
	else
		echo "Wystąpień pliku '$2' w katalogu '$1': $ilosc_plikow"
	fi
fi

exit "$ilosc_plikow"
