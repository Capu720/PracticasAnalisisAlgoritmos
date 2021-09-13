#!/bin/bash
gcc Shell.c -o Shell
./Shell 10000000 < numeros10millones.txt > resultado.txt
