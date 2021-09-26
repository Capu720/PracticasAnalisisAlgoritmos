#! /bin/bash
gcc seleccionTie.c tiempo.c -o sel
./sel 100    < numeros10millones.txt > seleccionTie.txt
./sel 1000   < numeros10millones.txt >> seleccionTie.txt
./sel 2000   < numeros10millones.txt >> seleccionTie.txt
./sel 3000   < numeros10millones.txt >> seleccionTie.txt
./sel 5000   < numeros10millones.txt >> seleccionTie.txt
./sel 8000   < numeros10millones.txt >> seleccionTie.txt
./sel 10000  < numeros10millones.txt >> seleccionTie.txt
./sel 20000  < numeros10millones.txt >> seleccionTie.txt
./sel 30000  < numeros10millones.txt >> seleccionTie.txt
./sel 40000  < numeros10millones.txt >> seleccionTie.txt
./sel 50000  < numeros10millones.txt >> seleccionTie.txt
./sel 60000  < numeros10millones.txt >> seleccionTie.txt
./sel 70000  < numeros10millones.txt >> seleccionTie.txt
./sel 80000  < numeros10millones.txt >> seleccionTie.txt
./sel 90000  < numeros10millones.txt >> seleccionTie.txt
./sel 100000 < numeros10millones.txt >> seleccionTie.txt
./sel 200000 < numeros10millones.txt >> seleccionTie.txt
./sel 300000 < numeros10millones.txt >> seleccionTie.txt
./sel 400000 < numeros10millones.txt >> seleccionTie.txt
./sel 500000 < numeros10millones.txt >> seleccionTie.txt
