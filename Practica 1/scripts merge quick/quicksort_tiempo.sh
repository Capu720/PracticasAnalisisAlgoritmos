#!/bin/bash
gcc main.c tiempo.c -o quicksort
./quicksort 5 > resultado.txt < numeros10millones.txt
