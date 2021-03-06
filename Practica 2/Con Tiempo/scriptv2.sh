#!/bin/bash
gcc lineal.c tiempo.c -o lineal.o
gcc ABB.c tiempo.c -o ABB.o
gcc binaria.c tiempo.c -o binaria.o
gcc exponencial.c tiempo.c -o exponencial.o
gcc fibonacci.c tiempo.c -o fibonacci.o

n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

echo -e "Lineal" > salida.txt
for i in ${n[@]}
do
./lineal.o $i < numeros10millones.txt >> salida.txt
done

echo -e "\nABB" >> salida.txt
for i in ${n[@]}
do
./ABB.o $i < numeros10millones.txt >> salida.txt
done

echo -e "\nBinaria" >> salida.txt
for i in ${n[@]}
do
./binaria.o $i < 10millones.txt >> salida.txt
done

echo -e "\nExponencial" >> salida.txt
for i in ${n[@]}
do
./exponencial.o $i < 10millones.txt >> salida.txt
done

echo -e "\nFibonacci" >> salida.txt
for i in ${n[@]}
do
./fibonacci.o $i < 10millones.txt >> salida.txt
done