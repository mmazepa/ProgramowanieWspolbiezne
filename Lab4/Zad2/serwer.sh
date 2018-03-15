#!/bin/bash

server=serwerfifo

if [[ "$1" ]]; then
	if [[ ! -p $1 ]]; then
		echo "Lacze nazwane klienta nie istnieje (nie dziala)"
	else
		echo $(expr $2 \* $2) > $1
	fi
else
	trap "rm -f $server" EXIT
	trap "" SIGTERM
	trap "" SIGHUP

	if [[ ! -p $server ]]; then
		mkfifo $server
	fi

	while true
	do
		if read line < $server; then
			$0 $line &
		fi
	done
fi
