#!/bin/bash

server=serwerfifo
folder="$HOME"
klient="$folder/klientfifo"

trap "rm -f $klient" EXIT

if [[ ! -p $klient ]]; then
    mkdir -p $folder
    mkfifo $klient
fi

if [[ ! -p $server ]]; then
    echo "Lacze nazwane serwera nie istnieje (nie dziala)"
    exit 1
fi

echo $klient $1 > $server
read line < $klient
echo $line
