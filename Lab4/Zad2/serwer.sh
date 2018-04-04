#!/bin/bash

potok_serwera=serwerfifo

function szescian {
  let potega=$1**3
}

trap "echo Caught SIGUSR1; exit 1" SIGUSR1;
if [[ "$1" ]]; then
	if [[ ! -p $1 ]]; then
		echo "Łącze klienta nie odpowiada!"
	else
    szescian "$2"
		echo "[serwer: $USER] Wynik: $2^3 = $potega" > $1
	fi
else
	trap "rm -f $potok_serwera" EXIT
	trap "" SIGTERM
	trap "" SIGHUP

	if [[ ! -p $potok_serwera ]]; then
		mkfifo $potok_serwera
	fi

	while true
	do
		if read odczyt < $potok_serwera; then
			$0 $odczyt &
		fi
	done
fi
