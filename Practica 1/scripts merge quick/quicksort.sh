#!/bin/bash
gcc quicksort.c -o quicksort
./quicksort 5 > resultado.txt < numeros10millones.txt
