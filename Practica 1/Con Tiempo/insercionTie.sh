#! /bin/bash
gcc insercionTie.c tiempo.c -o ins
./ins 100 < numeros10millones.txt > insercionTie.txt
./ins 1000 < numeros10millones.txt >> insercionTie.txt
./ins 5000 < numeros10millones.txt >> insercionTie.txt
./ins 10000 < numeros10millones.txt >> insercionTie.txt
./ins 50000 < numeros10millones.txt >> insercionTie.txt
./ins 100000 < numeros10millones.txt >> insercionTie.txt
./ins 200000 < numeros10millones.txt >> insercionTie.txt
./ins 400000 < numeros10millones.txt >> insercionTie.txt
./ins 600000 < numeros10millones.txt >> insercionTie.txt
./ins 800000 < numeros10millones.txt >> insercionTie.txt
./ins 1000000 < numeros10millones.txt >> insercionTie.txt
./ins 2000000 < numeros10millones.txt >> insercionTie.txt
./ins 3000000 < numeros10millones.txt >> insercionTie.txt
./ins 4000000 < numeros10millones.txt >> insercionTie.txt
./ins 5000000 < numeros10millones.txt >> insercionTie.txt
./ins 6000000 < numeros10millones.txt >> insercionTie.txt
./ins 7000000 < numeros10millones.txt >> insercionTie.txt
./ins 8000000 < numeros10millones.txt >> insercionTie.txt
./ins 9000000 < numeros10millones.txt >> insercionTie.txt
./ins 10000000 < numeros10millones.txt >> insercionTie.txt
