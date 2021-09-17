#! /bin/bash
gcc quicksort.c tiempo.c -o quick
./quick 100 < numeros10millones.txt > quicksort.txt
./quick 1000 < numeros10millones.txt >> quicksort.txt
./quick 5000 < numeros10millones.txt >> quicksort.txt
./quick 10000 < numeros10millones.txt >> quicksort.txt
./quick 50000 < numeros10millones.txt >> quicksort.txt
./quick 100000 < numeros10millones.txt >> quicksort.txt
./quick 200000 < numeros10millones.txt >> quicksort.txt
./quick 400000 < numeros10millones.txt >> quicksort.txt
./quick 600000 < numeros10millones.txt >> quicksort.txt
./quick 800000 < numeros10millones.txt >> quicksort.txt
./quick 1000000 < numeros10millones.txt >> quicksort.txt
./quick 2000000 < numeros10millones.txt >> quicksort.txt
./quick 3000000 < numeros10millones.txt >> quicksort.txt
./quick 4000000 < numeros10millones.txt >> quicksort.txt
./quick 5000000 < numeros10millones.txt >> quicksort.txt
./quick 6000000 < numeros10millones.txt >> quicksort.txt
./quick 7000000 < numeros10millones.txt >> quicksort.txt
./quick 8000000 < numeros10millones.txt >> quicksort.txt
./quick 9000000 < numeros10millones.txt >> quicksort.txt
./quick 10000000 < numeros10millones.txt >> quicksort.txt
./quick 500000 < numeros10millones.txt >> quicksort.txt
