#!/bin/bash
gcc lineal.c -o lineal.o
gcc ABB.c -o ABB.o
gcc binaria.c -o binaria.o
gcc exponencial.c -o exponencial.o
gcc fibonacci.c -o fibonacci.o

n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

for i in ${n[@]}
do
if [[ "$i" -eq "1000000" ]]
then
./lineal.o $i < numeros10millones.txt > salida.txt
else
./lineal.o $i < numeros10millones.txt >> salida.txt
fi
done

for i in ${n[@]}
do
./ABB.o $i < numeros10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./binaria.o $i < 10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./exponencial.o $i < 10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./fibonacci.o $i < 10millones.txt >> salida.txt
done