#!/bin/bash
gcc Seleccion.c -o seleccion
./seleccion 10000000 > resultado.txt < numeros10millones.txt
