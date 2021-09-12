#include<stdio.h>
#include<stdlib.h>

/*
TItulo: Practica 1, algoritmo "Ordenamiento por Seleccion"
Descripcion: Implementacion del algoritmo de seleccion
Fecha: 13/09/2021
Version 1.0
*/

#define TIPO int //tipo de dato que se ingresaran
#define FORMATO "%d" //formato de datos que se ingresaran
#define NUM_ELE 100000 //tamaño de elementos a analizar

void Seleccion(TIPO *, TIPO);

int main()
{
	/*Se declara un apuntador de tipo enetero del tamaño de numero de elemntos que este
	va a tener*/
	TIPO * A = (TIPO *)malloc(sizeof(TIPO) * NUM_ELE);
	TIPO i;

	//Se introducen los elemntos por medio de la terminal mediante el archivo txt
	for(i = 0; i<NUM_ELE; i++)
		scanf(FORMATO, &A[i]);

	//Se manda a llamar a la funcion Seleccion
	Seleccion(A,NUM_ELE);
}

/*
Version 1.0
La siguiente funcion realiza un ordenamiento por el metodo de seleccion
Recibe como parametros un arrego y el tamaño del arreglo
La funcion es de tipo void, por lo tanto no devuelve ningun valor
*/
void Seleccion(TIPO * A, TIPO n)
{
	/*Variables a utilizar*/
	TIPO k; //Servira para iterar el for y acceder al valor en una posicion del arreglo
	TIPO temp;//Almacenara el valor que se encuentre en la poscion del arreglo
	TIPO p;// Servira para almacenar la posicion del valor mas pequeño del arreglo por cada iteracion
	TIPO i;//Servira para recorrer el arreglo y realizar comparaciones con 
	
	/*Desarrollo del algoritmo*/
	
	for(k = 0; k<=n-2; k++) //Empieza el ciclo desde la primera posicion del arreglo hasta n-2
	{
		p = k; //Le asigna el valor de k a la variable p
		
		/*Se realiza un ciclo desde la k+1 hasta n-1, esto para encontrar el valor mas pequeño
		del arreglo*/
		for(i = k+1; i<=n-1; i++)
			if(A[i]<A[p])//Si el valor que esta en la posicion i es menor que el valor en la posicion p
				p = i;//Se asigna la posicion del elemento mas pequeño
		
		temp = A[p];//Guarda el valor del elemento mas pequeño en la variable p
		//Se hace un intercambio entre el valor pequeño con el valor que esta en la posicion K
		A[p] = A[k];
		A[k] = temp;
		
	}
}
