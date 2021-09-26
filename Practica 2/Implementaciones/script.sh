#!/bin/bash
gcc fibonacci.c -o fibonacci
gcc binaria.c -o binaria
gcc lineal.c -o lineal
gcc exponencial.c -o exponencial
#gcc arbol.c -o arbol   #porque beto aun no lo sube jsjsj
n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

for i in ${n[@]}
do
if [[ "$i" -eq "1000000" ]]
then
./fibonacci $i < 10millones.txt > salida.txt
else
./fibonacci $i < 10millones.txt >> salida.txt
./binaria $i < 10millones.txt >> salida.txt
./lineal $i < 10millones.txt >> salida.txt
./exponencial $i < 10millones.txt >> salida.txt
#./arbol $i < 10millones.txt >> salida.txt
fi
done
