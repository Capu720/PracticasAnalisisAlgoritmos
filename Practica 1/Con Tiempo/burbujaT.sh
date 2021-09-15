#! /bin/bash
gcc burbujaT.c tiempo.c -o bur
./bur 100 < numeros10millones.txt > burbujaT.txt
./bur 1000 < numeros10millones.txt >> burbujaT.txt
./bur 5000 < numeros10millones.txt >> burbujaT.txt
./bur 10000 < numeros10millones.txt >> burbujaT.txt
./bur 50000 < numeros10millones.txt >> burbujaT.txt
./bur 100000 < numeros10millones.txt >> burbujaT.txt
./bur 200000 < numeros10millones.txt >> burbujaT.txt
./bur 400000 < numeros10millones.txt >> burbujaT.txt
./bur 600000 < numeros10millones.txt >> burbujaT.txt
./bur 800000 < numeros10millones.txt >> burbujaT.txt
./bur 1000000 < numeros10millones.txt >> burbujaT.txt
./bur 2000000 < numeros10millones.txt >> burbujaT.txt
./bur 3000000 < numeros10millones.txt >> burbujaT.txt
./bur 4000000 < numeros10millones.txt >> burbujaT.txt
./bur 5000000 < numeros10millones.txt >> burbujaT.txt
./bur 6000000 < numeros10millones.txt >> burbujaT.txt
./bur 7000000 < numeros10millones.txt >> burbujaT.txt
./bur 8000000 < numeros10millones.txt >> burbujaT.txt
./bur 9000000 < numeros10millones.txt >> burbujaT.txt
./bur 10000000 < numeros10millones.txt >> burbujaT.txt
