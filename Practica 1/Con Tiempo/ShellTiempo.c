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

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*posicion en arreglo*/
#define BANDERA int  /*bandera de estado de algoritmo*/

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

/*
 * Función: Se realiza el ordenamiento de un arreglo por el metodo de algoritmo Shell
 * Descripcion: Se realiza el ordenamiento del arreglo de longitud "n" con el algoritmo Shell, el cual consiste en la creacion de sub-arreglos de tamaño k = n/2. Se realiza la comparacion de los elementos de cada sub-arreglo, si el sub arreglo con posicion mas cercano al valor n es menor que el elemento mas cercano al 0, se realiza un intercambio de valores. Una vez ordenado el sub-arreglo, se divide k entre 2 nuevamente. El proceso se realiza hasta que k <= 1.
 * Recibe:
 *  - Arreglo de tipo entero
 *  - Valor entero del tamaño del arreglo
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Shell(TIPO *numeros, TIPO n);

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

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n=atoi(argv[1]);
	}

	/*Solicita memoria al sistema con la funcion malloc*/
	TIPO *numeros;
	numeros = malloc(n * sizeof(TIPO));

	/*Lee y almacena los n numeros en el arreglo creado*/
	for(int i = 0; i < n; i++)
        scanf(FORMATO,&numeros[i]);
	
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	

    /*Se realiza llama a la funcion que realiza el algoritmo Shell*/
	Shell(numeros,n);

    //******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

    /*Se libera la memoria*/
    free(numeros);
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

void Shell(TIPO *numeros, TIPO n)
{
    /*Variable para iteraciones*/
	POSICION i;
    /*Variable para dimension de sub-arreglos*/
    POSICION k;
    /*Variable temporal para el intercambio de valores*/
    TIPO temporal;
    /*Variable bandera que indica si el subarreglo realizo un intercambio*/
    BANDERA b;

    /*Se realiza la division del arreglo en sub arreglos de n/2 de longitud*/
	k = (n/2);

    /*Se realiza un ciclo que su ultimo caso es el ordenamiento de arreglos
     de longitud 1*/
	while(k >= 1)
	{
        /*Se asigna el valor 1 a la bandera para forzar la entrada al while*/
		b = 1;
        /*Se ejecuta el while mientras que b sea diferente de 0
         indicando que el arreglo realizo un intercambio de valores,
         por lo cual requiere revisar si se mantiene ordenado*/
		while(b != 0)
		{
            /*Se asigna el valor 0 a b indicando que no se ha realizado un intercambio*/
			b = 0;
            /*Se hace un recorrido desde el valor k al valor n-1 con incrementos de una unidad*/
			for(i = k; i <= n - 1; i++)
			{
                /*Si compara si el valor del arreglo en la posicion i-k es mayor que
                 el valor en la posicion i, esto se debe a que los valores en la posicion i deben ser mayores a los que estan más cerca del 0*/
				if(numeros[i - k] > numeros[i])
				{
                    /*Si la condicion se cumple se debe realizar un intercambio de valores*/
					temporal = numeros[i];
					numeros[i] = numeros[i - k];
					numeros[i - k] = temporal;
                    /*Se incrementa en uno la bandera, indicando que re ha realizado un intercambio*/
					b = b + 1;
				}
			}
		}
		/*Al finalizar el analisis de los sub arreglos, se divide nuevamente entre 2, generando sub-arreglos de menor dimension en cada ciclo*/
		k = (k/2);
	}
}
