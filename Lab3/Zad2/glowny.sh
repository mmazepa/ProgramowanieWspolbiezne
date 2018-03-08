#!/bin/bash
declare -i n k w1 w2 w3 pid1 pid2 pid3
echo -n "Podaj n: "
read n

if [ $n -gt 5 ]; then
  echo "Liczba n nie może być większa od 5."
  exit 0
fi

if [ $n -lt 0 ]; then
  echo "Liczba n nie może być mniejsza od 0."
  exit 0
fi

echo -n "Podaj k: "
read k

if [ $k -gt 5 ]; then
  echo "Liczba k nie może być większa od 5."
  exit 0
fi

if [ $k -lt 0 ]; then
  echo "Liczba k nie może być mniejsza od 0."
  exit 0
fi

if [ $k -gt $n ]; then
  echo "Liczba k nie może być większa od liczby n."
  exit 0
fi

./silnia.sh $n &
pid1=$!

./silnia.sh $k &
pid2=$!

./silnia.sh $((n-k)) &
pid3=$!

wait $pid1
w1=$?

wait $pid2
w2=$?

wait $pid3
w3=$?

echo ""

echo "$n! = $w1"
echo "$k! = $w2"
echo "$((n-k))! = $w3"

exit 0
