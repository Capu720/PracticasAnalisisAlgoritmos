#! /bin/bash
gcc ABBTiempo.c tiempo.c -o abb
./abb 100 < numeros10millones.txt > ABBTiempo.txt
./abb 1000 < numeros10millones.txt >> ABBTiempo.txt
./abb 5000 < numeros10millones.txt >> ABBTiempo.txt
./abb 10000 < numeros10millones.txt >> ABBTiempo.txt
./abb 50000 < numeros10millones.txt >> ABBTiempo.txt
./abb 100000 < numeros10millones.txt >> ABBTiempo.txt
./abb 200000 < numeros10millones.txt >> ABBTiempo.txt
./abb 400000 < numeros10millones.txt >> ABBTiempo.txt
./abb 600000 < numeros10millones.txt >> ABBTiempo.txt
./abb 800000 < numeros10millones.txt >> ABBTiempo.txt
./abb 1000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 2000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 3000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 4000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 5000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 6000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 7000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 8000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 9000000 < numeros10millones.txt >> ABBTiempo.txt
./abb 10000000 < numeros10millones.txt >> ABBTiempo.txt
