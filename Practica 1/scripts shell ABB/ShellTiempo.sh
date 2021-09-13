#!/bin/bash
gcc ShellTiempo.c tiempo.c -o ShellTiempo
./ShellTiempo 10000000 < numeros10millones.txt > resultado.txt
