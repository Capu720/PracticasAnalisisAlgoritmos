#! /bin/bash
gcc mergesort.c tiempo.c -o merge
./merge 100 < numeros10millones.txt > mergesort.txt
./merge 1000 < numeros10millones.txt >> mergesort.txt
./merge 5000 < numeros10millones.txt >> mergesort.txt
./merge 10000 < numeros10millones.txt >> mergesort.txt
./merge 50000 < numeros10millones.txt >> mergesort.txt
./merge 100000 < numeros10millones.txt >> mergesort.txt
./merge 200000 < numeros10millones.txt >> mergesort.txt
./merge 400000 < numeros10millones.txt >> mergesort.txt
./merge 600000 < numeros10millones.txt >> mergesort.txt
./merge 800000 < numeros10millones.txt >> mergesort.txt
./merge 1000000 < numeros10millones.txt >> mergesort.txt
./merge 2000000 < numeros10millones.txt >> mergesort.txt
./merge 3000000 < numeros10millones.txt >> mergesort.txt
./merge 4000000 < numeros10millones.txt >> mergesort.txt
./merge 5000000 < numeros10millones.txt >> mergesort.txt
./merge 6000000 < numeros10millones.txt >> mergesort.txt
./merge 7000000 < numeros10millones.txt >> mergesort.txt
./merge 8000000 < numeros10millones.txt >> mergesort.txt
./merge 9000000 < numeros10millones.txt >> mergesort.txt
./merge 10000000 < numeros10millones.txt >> mergesort.txt
./merge 500000 < numeros10millones.txt >> mergesort.txt
