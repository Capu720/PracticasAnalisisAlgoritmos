#!/bin/bash
gcc lineal.c -o lineal
gcc ABB.c -o ABB 
gcc binaria.c -o binaria
gcc exponencial.c -o exponencial
gcc fibonacci.c -o fibonacci

n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

for i in ${n[@]}
do
if [[ "$i" -eq "1000000" ]]
then
./lineal $i < numeros10millones.txt > salida.txt
else
./lineal $i < numeros10millones.txt >> salida.txt
fi
done

echo "\n" >> salida.txt

for i in ${n[@]}
do
./ABB $i < numeros10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./binaria $i < 10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./exponencial $i < 10millones.txt >> salida.txt
done

for i in ${n[@]}
do
./fibonacci $i < 10millones.txt >> salida.txt
done