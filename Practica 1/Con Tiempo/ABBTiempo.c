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

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

/*
* Se define la estructura Nodo para la construcción del ABB
* La estructura tiene como elementos:
* - Variable "dato" de tipo int que almacena el valor numerico del nodo
* - Apuntador a estructura Nodo "izq" que indica si el nodo tiene ramificación a la izquierda
* - Apuntador a estructura Nodo "der" que indica si el nodo tiene ramificación a la derecha
*/

typedef struct Nodo
{
    int dato;
    struct Nodo *izq, *der;
}nodo;

typedef nodo *apnodo; /*Apuntador a estructura nodo*/

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

/*
 * Función: Realiza la insercion de un valor entero a la estructura del Arbol Binario de Busqueda de manera recursiva
 * Descripcion: Se realiza la insercion de un nodo al ABB, si la raiz actual es igual a NULL se agrega un nuevo nodo con el valor recibido por la funcion. Si la raiz no es NULL se compara el valor del nodo raiz con el valor recibido por la funcion, si el valor recibido es menor o igual que el valor del nodo raiz, se invoca a la misma misma funcion pasando como parametro un apuntador al nodo izquierdo de la raiz; en caso contrario se llama a la misma funcion pasando como parametro un apuntador al nodo derecho de la raiz. El algoritmo se ejecuta de manera recursiva hasta lograr la insercion.
 * Recibe:
 *  - Apuntador a apnodo
 *  - Valor entero a insertar
 * Regresa:
 *  - void
 * Errores: ninguno
*/

void Insertar(apnodo *arbol, TIPO dato);

/*
 * Función: Realiza un recorrido InOrden del ABB para almacenar los datos ordenados en un arreglo
 * Descripcion: Realiza de manera recursiva para cada nodo en el ABB los siguientes pasos:
 *  - Atraviesa el sub-arbol izquierdo
 *  - Almacena el valor del nodo actual y aumenta la variable global k
 *  - Atraviesa el sub-arbol derecho
 * Recibe:
 *  - Apuntador a apnodo
 *  - Arreglo de tipo entero
 * Regresa:
 *  - void
 * Errores: ninguno
*/

void InOrden(apnodo arbol, TIPO *numeros);

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

/*Contador utilizado para la insercion de valores al arreglo en la funcion InOrden*/
POSICION k = 0;

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

    /*Se crea un apuntador de tipo nodo para ser la raiz inicial del ABB*/
    apnodo arbol = NULL;

	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	/*Se insertan los n numeros en el ABB*/
	for(int i = 0; i < n; i++)
		Insertar(&arbol,numeros[i]);

    /*Se realiza un recorrido In Orden para almacenar los datos en el arreglo*/
	InOrden(arbol,numeros);
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

void Insertar(apnodo *arbol, TIPO dato)
{
	/*Se verifica si el apuntador a nodo es igual a NULL*/
    	if(*arbol == NULL)
    	{
        	/*Al ser NULL se reserva memoria para la creacion de un nuevo nodo*/
        	*arbol = malloc(sizeof(apnodo));
        	/*Se asigna el valor recibido en la funcion como valor del nodo*/
        	(*arbol)->dato = dato;
        	/*El apuntador izquierdo y derecho del nodo apuntan a NULL*/
        	(*arbol)->izq = NULL;
        	(*arbol)->der = NULL;
    	}
    	else
    	{
        	/*Al ser un nodo no NULL se compara si el valor recibido en la funcion
         	es menor o mayor que el valor del nodo actual*/
        	if (dato <= (*arbol)->dato)
		{
            	/*Si el valor recibido es menor o igual que el valor del nodo actual
             	se invoca a la misma funcion enviando como parametro el apuntador izquierdo del nodo actual*/
            	Insertar(&(*arbol)->izq, dato);
        	}
		else
		{
        	/*Si el valor recibido es mayor que el valor del nodo actual
             	se invoca a la misma funcion enviando como parametro el apuntador derecho del nodo actual*/
            	Insertar(&(*arbol)->der, dato);
        	}
    	}
}

void InOrden(apnodo arbol, TIPO *numeros)
{
    	/*Se verifica si el apuntador a nodo es diferente de NULL*/
    	if (arbol != NULL)
    	{
        	/*Se invoca a la misma funcion pasando como parametro el nodo izquierdo del nodo actual*/
        	InOrden(arbol->izq, numeros);
        	/*Se guarda el valor del nodo actual en la posicion k del arreglo recibido*/
        	numeros[k] = arbol->dato;
        	/*Se incrementa la variable global k para avanzar la posicion en el arreglo*/
	        k++;
        	/*Se invoca a la misma funcion pasando como parametro el nodo derecho del nodo actual*/
        	InOrden(arbol->der, numeros);
    	}
}
