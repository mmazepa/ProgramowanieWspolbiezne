#!/bin/bash
clear
echo ""
echo "  ┌─┐┌─┐┬ ┬┬┌─┌─┐ ┬ ┌─┐┬ ┬"
echo "  └─┐┌─┘│ │├┴┐├─┤ │ └─┐├─┤"
echo "  └─┘└─┘└─┘┴ ┴┴ ┴└┘o└─┘┴ ┴"
echo ""

echo "  Nazwa skryptu:          $0"
echo "  Folder do przeszukania: $1"
echo "  Plik do znalezienia:    $2"
echo ""

declare -i x
dir=$(pwd)
if [ -s "$1" ]; then
  path_to_file="$dir/$1"
  cd $path_to_file
  step=0
  for i in $(ls); do
    if [ "$i" == "$2" ] ; then
      let x+=1
      echo "  [$x]: $(pwd)"
    else
      while [[ -s $i ]]; do
        step+=1
        # ls
        # echo $step
        if [[ -s $i ]]; then
          cd $i
        fi
        for z in $(ls); do
          if [[ "$z" == "$2" ]]; then
            let x+=1
            echo "  [$x]: $(pwd)"
          fi
          # for i in $(ls); do
          #   sleep 0
          # done
          if [[ $i == $2 ]]; then
            let x+=1
            echo "  [$x]: $(pwd)" # brak wydruku (???)
          fi
        done
      done
    fi
  done
else
  echo "  Podaj prawidłowy parametr."
fi
echo ""

if [ -z $3 ] ; then
  if [ -z $x ] ; then
    echo "  [WYNIK]: Niestety niczego nie znaleziono."
  else
    echo "  [WYNIK]: Plik/katalog został znaleziony ($x razy)."
  fi
fi
echo ""
