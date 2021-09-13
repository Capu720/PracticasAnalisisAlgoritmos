//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************
/**
 * Titulo: Practica 1, algoritmo "Ordenamiento QuickSort"
 * Descripción: implementacion del algoritmo QuickSort
 * Fecha: 13-sep-2021
 * Versión: 1
*/
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
#define TIPO int	 /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
/**
 * Función:realiza la función de quick sort
 * Descripcion: obteniendo el pivote, y a partir de este, dividir el arreglo en dos particiones de manera recursiva hasta el caso base (1)
 * Recibe: 
 *  - arreglo de numeros
 *  - la primera posicion
 *  - ultima posicion
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void QuickSort(TIPO numeros[], POSICION inicio, POSICION final);
/**
 * Función:realiza la función de obtener el pivote
 * Descripcion: en un ciclo infinito, toma el pivote como la posicion inicial, a partir de aqui va comparando de izquierda a derecha, y de derecha a izquierda los numeros mas grandes o pequeños que el numero pivote. Al recorrer la parte del arreglo, y encuentra que un numero no concuerda con la posicion que sea mayor o menor, lo intercambia con uno que si sea, es decir, reacomodar los elementos a ordenar de modo que todas las
 claves “pequeñas” precedan a las claves “grandes”
 * Recibe: 
 *  - arreglo de numeros
 *  - la primera posicion
 *  - ultima posicion
 * Regresa:
 *  - la posición nueva del pivote
 * Errores: ninguno
*/
POSICION Pivot(TIPO numeros[], POSICION inicio, POSICION final);
/**
 * Función:realiza la función intercambiar posiciones
 * Descripcion: algoritmo swap, teniendo variable A y B, A lo guarda en una variable temporal, B se guarda en la posición donde esta A y despues lo que se guardó en la variable temporal (A) se guarda donde estaba la variable B
 * Recibe: 
 *  - arreglo de numeros
 *  - la primera variable
 *  - la segunda variable
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Intercambiar(TIPO numeros[], POSICION incio, POSICION final);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//*****************************************************************
//PROGRAMA PRINCIPAL
//*****************************************************************
int main(int argc, char *argv[])
{
	//******************************************************************
	//Variables del main
	//******************************************************************
	double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
	TIPO n, *numeros;
	int i, j;

	//******************************************************************
	//Recepción y decodificación de argumentos
	//******************************************************************

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
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
	/*Solicita memoria con la funcion malloc, en caso de fracaso, regresará error*/
	if ((numeros = malloc(sizeof(int) * n)) == NULL)
		perror("No se pudo solicitar memoria para el arreglo");
	/*lee numero por numero de un archivo*/
	for (i = 0; i < n; i++)
		scanf(FORMATO, &numeros[i]);
	//******************************************************************
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************

	//******************************************************************
	//Algoritmo
	//******************************************************************
	/*se llama a la función*/
	QuickSort(numeros, 0, n - 1);
	//******************************************************************

	//******************************************************************
	//Evaluar los tiempos de ejecución
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	/*se imprime el arreglo ordenado*/
	for (i = 0; i < n; i++)
		printf("%d\n", numeros[i]);
	/*Se libera la memoria*/
	free(numeros);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente
	return EXIT_SUCCESS;
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************
void QuickSort(TIPO numeros[], POSICION inicio, POSICION final)
{
	POSICION pivote;
	/*compara que el numero este en el rango*/
	if (inicio < final)
	{
		/*obtiene el pivote*/
		pivote = Pivot(numeros, inicio, final);
		/*realiza quicksort del inicio al pivote, sin usar el pivote*/
		QuickSort(numeros, inicio, pivote - 1);
		/*realiza quicksort del pivote a la posicion final, sin usar el pivote*/
		QuickSort(numeros, pivote + 1, final);
	}
}

POSICION Pivot(TIPO numeros[], POSICION inicio, POSICION final)
{
	POSICION pivote, i, j, k;
	/*toma el pivote como el primer elemento*/
	pivote = numeros[inicio];
	/*guarda la siguiente posición*/
	i = inicio + 1;
	/*guarda la ultima posición*/
	j = final;

	do
	{
		/*busca que numero no es menor que el pivote para poder ser intercambiado*/
		while (numeros[i] <= pivote && i < final)
			i++;
		/*busca que numero no es mayor que el pivote para poder ser intercambiado*/
		while (numeros[j] > pivote)
			j--;

		/*si la posicipon de la izquierda es menor a la derecha, se intercambian sus valores*/
		if (i < j)
		{
			Intercambiar(numeros, i, j);
		}
		/*en caso contrario, se intercambia el inicio con el valor de la derecha y se retorna la posición del nuevo pivote*/
		else
		{
			Intercambiar(numeros, inicio, j);
			return j;
		}
	} while (1);
}

void Intercambiar(TIPO numeros[], POSICION inicio, POSICION final)
{
	/*se guarda en una variable temporal*/
	TIPO temporal;
	temporal = numeros[final];
	/*realiza el cambio con la otra variable*/
	numeros[final] = numeros[inicio];
	/*la variable guardada en temporal, se coloca en la posicion antigua de la otra variable*/
	numeros[inicio] = temporal;
}
