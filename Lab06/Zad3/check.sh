#!/bin/bash

# tablica słów do pętli
slownik=(
# słowa zawarte w słowniku
"kot"         "pies"      "krowa" "dzik"    "czas"
"uniwersytet" "kwiat"     "zegar" "drzewo"  "mysz"
"sieć"        "samochód"  "pająk" "cegła"   "ścieżka"
"wysiłek"     "nauka"     "stos"  "wiedza"   "zadanie"
# słowo niezawarte w słowniku
"krzak")

# pętla wywołująca program klienta
for i in {0..21}
do
  echo "Wywołanie nr $((i+1)):"
   ./bin/klient ${slownik[i]}
   sleep 0.2
done
