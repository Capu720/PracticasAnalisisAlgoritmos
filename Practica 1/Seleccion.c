/*
TItulo: Practica 1, algoritmo "Ordenamiento por Seleccion"
Descripcion: Implementacion del algoritmo de seleccion
Fecha: 13/09/2021
Version 1.0
*/

#include<stdio.h>
#include<stdlib.h>

#define TIPO int //tipo de dato que se ingresaran
#define FORMATO "%d" //formato de datos que se ingresaran

//se hace el esqueleto de la funcion seleccion
void Seleccion(TIPO *, TIPO);

int main(int argc, char* argv[])
{
	int n;
	//recibiendo el tamanio
	if (argc != 2)
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
		exit(1);
	}
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n = atoi(argv[1]);
	}
	
	/*Se declara un apuntador de tipo enetero del tamaño de numero de elemntos que este
	va a tener*/
	TIPO * A = (TIPO *)malloc(sizeof(TIPO) * n);
	TIPO i;

	//Se introducen los elemntos por medio de la terminal mediante el archivo txt
	for(i = 0; i<n; i++)
		scanf(FORMATO, &A[i]);

	//Se manda a llamar a la funcion Seleccion
	Seleccion(A,n);
}

/*
Version 1.0
La siguiente funcion realiza un ordenamiento por el metodo de seleccion
Busca l minimo elemento entre una posicion k y el final del areglo e intercambia el minimo con el elemento en la 
posicion k
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
		
		temp = A[p];//Guarda el valor del elemento mas pequeño en la variable temp
		//Se hace un intercambio entre el valor pequeño con el valor que esta en la posicion K
		A[p] = A[k];
		A[k] = temp;
		
	}
	
	//imprimiendo el arreglo ordenado
	for(i=0; i<n; i++)
		printf("%d\n", A[i]);
}
