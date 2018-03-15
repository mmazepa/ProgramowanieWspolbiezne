#!/bin/bash

server=serwerfifo
klient="$1""/klientfifo"

trap "rm -f $klient" EXIT

if [[ ! -p $klient ]]; then
    mkdir -p $1
    mkfifo $klient
fi

if [[ ! -p $server ]]; then
    echo "Lacze nazwane serwera nie istnieje (nie dziala)"
    exit 1
fi

echo $klient $2 > $server
read line < $klient
echo $line
