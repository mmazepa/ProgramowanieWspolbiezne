#!/bin/bash
sciezka=$(pwd)
plik=$1
folder=$2

clear
echo ""

echo "  ┌─┐┌─┐┬ ┬┬┌─┌─┐ ┬       ┌─┐┬  ┬┬┌─  ┌─┐┌─┐┬  ┌┬┐┌─┐┬─┐"
echo "  └─┐┌─┘│ │├┴┐├─┤ │  ───  ├─┘│  │├┴┐  ├┤ │ ││   ││├┤ ├┬┘"
echo "  └─┘└─┘└─┘┴ ┴┴ ┴└┘       ┴  ┴─┘┴┴ ┴  └  └─┘┴─┘─┴┘└─┘┴└─"

echo "  ------------------------------------------------------"

echo "  [sciezka]: $sciezka"
echo "  [plik]:    $plik"
echo "  [folder]:  $folder"

# przykładowe wywołanie tymczasowe...
./wsparcie.sh $plik $folder
./wsparcie.sh $plik $folder
./wsparcie.sh $plik $folder

echo ""
exit 0
