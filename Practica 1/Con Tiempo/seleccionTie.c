//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
#define TIPO int //tipo de dato que se ingresaran
#define FORMATO "%d" //formato de datos que se ingresaran
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void Seleccion(TIPO *, TIPO);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops
    /*Se declara un apuntador de tipo enetero del tamaño de numero de elemntos que este
	va a tener*/
	
	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	
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
	
	TIPO * A = (TIPO *)malloc(sizeof(TIPO) * n);
	//Se llena el arreglo
	for(i = 0; i<n; i++)
		scanf(FORMATO, &A[i]);

	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	//Se manda a llamar a la funcion Seleccion
	Seleccion(A,n);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
	/*Se imprime el caso de pruba*/
	if(n==100)
		printf("N\tReal\t user\t sys(E/S)\t CPU/wall\n");
    printf("%d\t", n);
	printf("%.10e\t",  wtime1 - wtime0);
	printf("%.10e\t",  utime1 - utime0);
	printf("%.10e\t",  stime1 - stime0);
	printf("%.10f %%\t\n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	
	//Cálculo del tiempo de ejecución del programa
	// printf("\n");
	// printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	// printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	// printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	// printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	// printf("\n");
	
	// //Mostrar los tiempos en formato exponecial
	// printf("\n");
	// printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	// printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	// printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	// printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	// printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
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
}
