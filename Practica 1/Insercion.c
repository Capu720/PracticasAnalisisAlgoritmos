/*
TItulo: Practica 1, algoritmo "Ordenamiento por Insercion"
Descripcion: Implementacion del algoritmo de insercion
Fecha: 13/09/2021
Version 1.0
*/

#include<stdio.h>
#include<stdlib.h>

#define TIPO int //tipo de dato que se ingresaran
#define FORMATO "%d" //formato de datos que se ingresaran

//Se declara el esqueleto de la funcion insercion
void Insercion(int *, int);

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
	/*Se declara un apuntador de tipo enetero del tamaño del numero de elemntos que este
	va a tener*/
	TIPO * A = (TIPO *)malloc(sizeof(TIPO) * n);
	TIPO i;

	//Se introducen los elemntos por medio de la terminal mediante el archivo txt
	for(i = 0; i<n; i++)
		scanf(FORMATO, &A[i]);

	//Se manda a llamar a la funcion Seleccion
	Insercion(A,n);
}

/*
Version 1.0
La siguiente funcion realiza un ordenamiento por el metodo de insercion
Recibe como parametros un arrego y el tamaño del arreglo
La funcion es de tipo void, por lo tanto no devuelve ningun valor
*/
void Insercion(TIPO * A, TIPO n)
{
	/*Variables a utilizar*/
	TIPO i; //Servira para iterar el for y acceder al valor en una posicion del arreglo
	TIPO temp;//Almacenara el valor que se encuentre en la poscion del arreglo
	TIPO j;// Servira para acceder
	
	/*Desarrollo del algoritmo*/
	
	for(i = 0; i<=n-1; i++) //Realiza un ciclo for desde i = 0 hasta el numero de elementos en el arreglo menos 1
	{
		j = i; //Se iguala el valor de j con el de i
		temp = A[i]; //Se le asigna el valor del arreglo en la posicion que valla la vaiable i a la varible temp
		
		while(j>0 && (temp<A[j-1]))//Realiza un ciclo while mientras j sea mayor a 0 y que el valor en temporal sea menor al valor del arreglo en la posicion j-1 
		{
			A[j] = A[j-1]; //Toma el valor que esta en la posicion j-1 y lo asigna al valor en la posicon j
			j--;//Se decremnta el valor de j
		}
		A[j] = temp;//Asigna el valor tomado 
	}
	
	//imprimiendo el arreglo ordenado
	for(i=0; i<n; i++)
		printf("%d\n", A[i]);
	
}


