#!/bin/bash
gcc ABBTiempo.c tiempo.c -o ABBTiempo
./ABBTiempo 10000000 < numeros10millones.txt > resultado.txt
