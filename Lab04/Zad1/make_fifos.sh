#!/bin/bash
echo "Tworzenie kolejek 'fifo1' i 'fifo2'."
if [[ ! -p fifo1 ]]; then
  mkfifo fifo1
  echo "Kolejka 'fifo1' została utworzona."
else
  echo "Kolejka 'fifo1' już istnieje."
fi

if [[ ! -p fifo2 ]]; then
  mkfifo fifo2
  echo "Kolejka 'fifo2' została utworzona."
else
  echo "Kolejka 'fifo2' już istnieje."
fi
