#! /bin/bash
gcc seleccionTie.c tiempo.c -o sel
./sel 100 < numeros10millones.txt > seleccionTie.txt
./sel 1000 < numeros10millones.txt >> seleccionTie.txt
./sel 5000 < numeros10millones.txt >> seleccionTie.txt
./sel 10000 < numeros10millones.txt >> seleccionTie.txt
./sel 50000 < numeros10millones.txt >> seleccionTie.txt
./sel 100000 < numeros10millones.txt >> seleccionTie.txt
./sel 200000 < numeros10millones.txt >> seleccionTie.txt
./sel 400000 < numeros10millones.txt >> seleccionTie.txt
./sel 600000 < numeros10millones.txt >> seleccionTie.txt
./sel 800000 < numeros10millones.txt >> seleccionTie.txt
./sel 1000000 < numeros10millones.txt >> seleccionTie.txt
./sel 2000000 < numeros10millones.txt >> seleccionTie.txt
./sel 3000000 < numeros10millones.txt >> seleccionTie.txt
./sel 4000000 < numeros10millones.txt >> seleccionTie.txt
./sel 5000000 < numeros10millones.txt >> seleccionTie.txt
./sel 6000000 < numeros10millones.txt >> seleccionTie.txt
./sel 7000000 < numeros10millones.txt >> seleccionTie.txt
./sel 8000000 < numeros10millones.txt >> seleccionTie.txt
./sel 9000000 < numeros10millones.txt >> seleccionTie.txt
./sel 10000000 < numeros10millones.txt >> seleccionTie.txt
