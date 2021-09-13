#! /bin/bash
gcc quicksort.c tiempo.c -o sal
./sal 100 < numeros10millones.txt > quicksort.txt
./sal 1000 < numeros10millones.txt >> quicksort.txt
./sal 5000 < numeros10millones.txt >> quicksort.txt
./sal 10000 < numeros10millones.txt >> quicksort.txt
./sal 50000 < numeros10millones.txt >> quicksort.txt
./sal 100000 < numeros10millones.txt >> quicksort.txt
./sal 200000 < numeros10millones.txt >> quicksort.txt
./sal 400000 < numeros10millones.txt >> quicksort.txt
./sal 600000 < numeros10millones.txt >> quicksort.txt
./sal 800000 < numeros10millones.txt >> quicksort.txt
./sal 1000000 < numeros10millones.txt >> quicksort.txt
./sal 2000000 < numeros10millones.txt >> quicksort.txt
./sal 3000000 < numeros10millones.txt >> quicksort.txt
./sal 4000000 < numeros10millones.txt >> quicksort.txt
./sal 5000000 < numeros10millones.txt >> quicksort.txt
./sal 6000000 < numeros10millones.txt >> quicksort.txt
./sal 7000000 < numeros10millones.txt >> quicksort.txt
./sal 8000000 < numeros10millones.txt >> quicksort.txt
./sal 9000000 < numeros10millones.txt >> quicksort.txt
./sal 10000000 < numeros10millones.txt >> quicksort.txt
