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
 * Titulo: Practica 1, algoritmo "Ordenamiento Mergesort"
 * Descripción: implementacion del algoritmo mergesort
 * Fecha: 13-sep-2021
 * Versión: 2
 * nota: revisar pagina 106 Algorithmics, the spirit of computing
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
 * Función:realiza el ordenamiento MergeSort
 * Descripcion: toma el arreglo y crea dos particiones de manera recursiva obteniendo la posicion de en medio. Las particiones son: del inicio a la posicion de en medio, de la posición de en medio hasta la posicion final.
 * Recibe: 
 *  - arreglo de numeros
 *  - la primera posicion
 *  - ultima posicion
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void MergeSort(TIPO numeros[], POSICION primero, POSICION final);
/**
 * Función:realiza la fusion o mezcla de manera ordenada (comparando los numeros de dos particiones de inicio al medio, medio al final)
 * Descripcion: va comparando el arreglo, tomando en cuenta las particiones, compara los valores de lado izquierdo con cada valor del lado derecho, hasta encontrar si es mayor o menor, se va guardando en una variable temporal en cada iteracion, para despues sobreescribir el arreglo original.
 * Recibe: 
 *  - arreglo de numeros
 *  - la primera posicion
 *  - posicion de en medio 
 *  - ultima posicion
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Merge(TIPO numeros[], POSICION primero, POSICION medio, POSICION final);
//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//*****************************************************************
//PROGRAMA PRINCIPAL
//*****************************************************************
/**
 * Función:principal, recibe una longitud del arreglo y diferentes numeros para crear  un arreglo, para despues llamar a la funcion Mergesort para ordenar dicho arreglo
 * Descripción: Obtiene el valor de n y los numeros ingresados desde un archivo de texto, convierte cada cadena en numeros, solicita memoria para la creacion del arreglo e ir guardando en el los datos ingresados, despues mandar a llamar a la función Mergesort, al final, con el arreglo ordenado, imprimir en un archivo.
 * Recibe: 
 *  - numero de argumentos
 *  - cadena de caracteres
 * Regresa:
 *  - en caso de error, el nombre del error o constante EXIT_FAILURE
 *  - en caso de exito, regresa la constante EXIT_SUCCESS
 * Errores: ninguno
*/
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
	if ((numeros = malloc(sizeof(TIPO) * n)) == NULL)
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
	MergeSort(numeros, 0, n - 1);
	//******************************************************************

	//******************************************************************
	//Evaluar los tiempos de ejecución
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	/*Se libera la memoria*/
	free(numeros);

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
	// printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
	// printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
	// printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
	// printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	// printf("\n");

	// //Mostrar los tiempos en formato exponecial
	// printf("\n");
	// printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
	// printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
	// printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
	// printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	// printf("\n");
	//******************************************************************

	//Terminar programa normalmente
	return EXIT_SUCCESS;
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************
void MergeSort(TIPO numeros[], POSICION inicio, POSICION final)
{
	POSICION medio;
	/*compara si la posicion inicial es menor a la final, si no es asi significa que es el caso base, es decir, un solo numero*/
	if (inicio < final)
	{
		/*se obtiene la posicion media del arreglo*/
		medio = (inicio + final) / 2;
		/*se llama de manera recursiva la funcion Mergesort del punto inicial al punto medio*/
		MergeSort(numeros, inicio, medio);
		/*se llama de manera recursiva la funcion Mergesort del punto medio al punto final*/
		MergeSort(numeros, medio + 1, final);
		/*se fusiona o mezcla ambas particiones, ordenando los numeros*/
		Merge(numeros, inicio, medio, final);
	}
}
void Merge(TIPO numeros[], POSICION inicio, POSICION medio, POSICION final)
{
	/*variables para las iteraciones*/
	POSICION l, i, j, k, f;

	/*rango del arreglo*/
	l = final - inicio + 1;
	i = inicio;
	j = medio + 1;
	/*se solicita memoria para el arreglo temporal con el que se hará las distintas operaciones, siendo de longitud l ya que es el minimo que se requiere*/
	TIPO *temporal = malloc(sizeof(TIPO) * l);
	/*se recorre el arreglo tomando en cuenta su rango*/
	for (k = 0; k < l; k++)
	{
		/*Se verifica que esté dentro del rango*/
		if (i <= medio && j <= final)
		{
			/*si el numero de la posicion i es menor al numero de la posicion que se encuentra de la parte media se guarda en el arreglo temporal y avaza a la siguiente posicion a partir de la posicion de inicio*/
			if (numeros[i] < numeros[j])
			{
				temporal[k] = numeros[i];
				i++;
			}
			/*en caso contrario, se guarda el numero de la posicion "a la derecha" del numero de en medio y avanza a apartir de esa posicion*/
			else
			{
				temporal[k] = numeros[j];
				j++;
			}
		}
		else
		{
			/*en caso que solo se compare con una sola partición, se verifica que si la particion es de lado izquierdo o derecho*/
			if (i <= medio)
			{
				temporal[k] = numeros[i];
				i++;
			}
			else
			{
				temporal[k] = numeros[j];
				j++;
			}
		}
	}
	/*Copia los elementos del arreglo temporal al arreglo de numeros*/
	for (f = inicio, k = 0; f <= final; f++, k++)
	{
		numeros[f] = temporal[k];
	}
	/*Se libera la memoria*/
	free(temporal);
}
