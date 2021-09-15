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
void Insercion(TIPO *, TIPO);
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
	Insercion(A,n);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	printf("\n");
	/*Se imprime el caso de pruba*/
	if(n==100)
		printf("\tReal\t user\t sys(E/S)\t CPU/wall\n");
    printf("n = %d\t", n);
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
}
