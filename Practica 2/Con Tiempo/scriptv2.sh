#!/bin/bash
gcc lineal.c tiempo.c -o lineal.o
gcc ABB.c tiempo.c -o ABB.o
gcc binaria.c tiempo.c -o binaria.o
gcc exponencial.c tiempo.c -o exponencial.o
gcc fibonacci.c tiempo.c -o fibonacci.o

n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

echo \Lineal > salida.txt
for i in ${n[@]}
do
./lineal.o $i < numeros10millones.txt >> salida.txt
done

echo \ABB >> salida.txt
for i in ${n[@]}
do
./ABB.o $i < numeros10millones.txt >> salida.txt
done

echo \Binaria >> salida.txt
for i in ${n[@]}
do
./binaria.o $i < 10millones.txt >> salida.txt
done

echo \Exponencial >> salida.txt
for i in ${n[@]}
do
./exponencial.o $i < 10millones.txt >> salida.txt
done

echo \Fibonacci >> salida.txt
for i in ${n[@]}
do
./fibonacci.o $i < 10millones.txt >> salida.txt
done