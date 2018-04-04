#!/bin/bash

potok_serwera=serwerfifo
folder="$HOME"
potok_klienta="$folder/klientfifo"

if [[ ! $1 -eq null ]]; then
  trap "rm -f $potok_klienta" EXIT
  if [[ ! -p $potok_klienta ]]; then
      mkdir -p $folder
      mkfifo $potok_klienta
  fi
  if [[ ! -p $potok_serwera ]]; then
      echo "Łącze serwera nie odpowiada!"
      exit 1
  else
    echo $potok_klienta $1 > $potok_serwera
    read odczyt < $potok_klienta
    echo $odczyt
  fi
else
  echo "Nie podano parametru!"
fi
