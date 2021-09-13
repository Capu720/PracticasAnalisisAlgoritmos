#!/bin/bash
gcc main.c tiempo.c -o mergesort
./mergesort 10000000 > resultado.txt < numeros10millones.txt
