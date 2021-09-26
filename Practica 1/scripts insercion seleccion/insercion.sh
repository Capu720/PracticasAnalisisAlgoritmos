#!/bin/bash
gcc Insercion.c -o insercion
./insercion 10000000 > resultado.txt < numeros10millones.txt
