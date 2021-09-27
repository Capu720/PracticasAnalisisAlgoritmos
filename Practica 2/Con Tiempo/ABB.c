//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************
/*
 * Titulo: Practica 2, algoritmo "Busqueda en ABB"
 * Descripción: implementacion del algoritmo ABB
 * para la busqueda de elementos
 * Fecha: 23-sep-2021
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
#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/

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
} nodo;

typedef nodo *apnodo; /*Apuntador a estructura nodo*/
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

void Insertar(apnodo *arbol, TIPO dato);
int Buscar(apnodo arbol, TIPO dato);

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
	double sumwtime, utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
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

    int *A = (int*)malloc(sizeof(int)*n); /*Reserva memoria para el arreglo*/
    //Elementos que se buscaran
    int x[] = { 322486, 14700764,   3128036,    3128036,    6337399,
                61396,  10393545,   2147445644, 1295390003, 450057883,
                187645041,  1980098116, 152503, 5000, 1493283650,
                214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};

    int xn = sizeof(x) / sizeof(x[0]);//Calcula cuantos numeros se van a buscar

    for (i = 0; i < n; i++){/*Llena el arreglo*/
        scanf("%d",&A[i]);
    }

	/*Se crea un apuntador de tipo nodo para ser la raiz inicial del ABB*/
	apnodo arbol = NULL;    
	/*Se insertan los n numeros en el ABB*/
	for (int i = 0; i < n; i++)
		Insertar(&arbol, numeros[i]);

    for (i = 0; i < xn; i++){//Cuenta el tiempo para cada busqueda
	//******************************************************************
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************

	//******************************************************************
	//Algoritmo
	//******************************************************************
	/*Se realiza la funcion de busqueda en el ABB*/
	if (Buscar(arbol, dato))
		printf("\nSe encontro el dato: %d", x[i]);
	else
		printf("\nNo se encontro el dato: %d", x[i]);
	//******************************************************************

	//******************************************************************
	//Evaluar los tiempos de ejecución
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	//Acumula el tiempo de ejecución del programa
	sumwtime += wtime1 - wtime0;
    }

    //Cálculo del tiempo promedio de ejecución del programa
	if(n==1000000)
		printf("N\tTiempo promedio\n");
    printf("%d\t", n);
	printf("%.10e\n", (double)sumwtime/xn);

	//******************************************************************

    free(A);/*Libera la memoria*/
	//Terminar programa normalmente
	exit (0);
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************
/*
 * Función: Realiza la insercion de un nodo al ABB
 * Descripcion: Se realiza la insercion de un nodo al ABB, si la raiz actual es igual a NULL se agrega un nuevo nodo con el valor recibido por la funcion. Si la raiz no es NULL se crea un apuntador temporal a nodo al que se le asigna el apuntador del arbol recibido como paramtero. Una vez creado el nodo temporal se compara el valor del nodo con el valor recibido por la funcion, si el valor recibido es menor o igual que el valor del nodo, se actualiza el apuntador temporal con el nodo izquierdo del mismo; en caso contrario se actualiza con el apuntador al nodo derecho del temporal. El algoritmo se ejecutara mientras que el nodo temporal no sea NULL. Al momento en el que el temporal sea NULL y salga del ciclo, se compara si en el nodo con la ultima posicion previa al NULL tiene un valor menor o mayor que el dato a insertar, si el numero del nodo es menor al dato recibido, se asigna el nodo con el apuntador izquierdo; si es mayor se asigna en el derecho
 * Recibe:
 *  - Apuntador a apnodo
 *  - Valor entero a insertar
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Insertar(apnodo *arbol, TIPO dato)
{
	/*Se crea un nuevo nodo con el dato recibido*/
	apnodo n = malloc(sizeof(apnodo));
	n->dato = dato;
	n->izq = NULL;
	n->der = NULL;

	/*Se verifica si el apuntador a nodo es igual a NULL*/
	if (*arbol == NULL)
	{
		/*Al ser NULL se asigna el nuevo nodo al arbol recibido*/
		*arbol = n;
	}
	else
	{
		/*Se crea un nodo temporal para realizar el recorrido del arbol*/
		apnodo temp = *arbol;
		/*Se crea un nodo que almacena la ultima posicion del apuntador temporal
		 * antes de actualizar su posicion*/
		apnodo anterior = NULL;

		/*Se ejecuta un ciclo mientras que el apuntador temporal sea diferente de NULL*/
		while (temp != NULL)
		{
			/*Se guarda la posicion actual del apuntador temporal antes de ser actualizado*/
			anterior = temp;

			/*Se compara el valor del nodo actual con el dato recibido*/
			if (dato < temp->dato)
				/*Si el dato recibido es menor que el del nodo actual
				 * se actualiza el apuntador temporal al apuntador izquierdo del nodo*/
				temp = temp->izq;
			else
				/*Si el dato recibido es mayor que el del nodo actual
				 * se actualiza el apuntador temporal al apuntador derecho del nodo*/
				temp = temp->der;
		}

		/*Se compara el dato de la posicion anterior con el dato recibido*/
		if (dato <= anterior->dato)
			/*Si el dato recibido es menor o igual que el del nodo actual
			 * se asigna el nuevo nodo en la posicion izquierda de la raiz actual*/
			anterior->izq = n;
		else
			/*Si el dato recibido es mayor que el del nodo actual
			 * se asigna el nuevo nodo en la posicion derecha de la raiz actual*/
			anterior->der = n;
	}
}

/*
 * Función: Realiza la busqueda de un dato en el ABB
 * Descripcion: Realiza la busqueda de un elemento den el ABB de manera similar a la funcion de insercion.
 * Se realiza un ciclo que se ejecuta mientras que el apuntador del arbol sea distinto de NULL y mientras el valor del nodo sea distinto del dato buscado. Dentro del ciclo se realiza la comparacion del dato recibido y el dato del nodo actual. En caso de que el valor buscado sea menor quel del nodo actual, se actualiza con el nodo izquiero y si es mayor con  el nodo derecho. Al salir del ciclo se retorna el valor obtenido al revisar si el arbol es diferente a NULL. Si el arbol es diferente de NULL se retorna 1, en caso contrario se retorna 0.
 * Recibe:
 *  - Apuntador a apnodo
 *  - Arreglo de tipo entero
 * Regresa:
 *  - 1 si el elemento se encontro
 *  - 0 si el elemento no se encontro
 * Errores: ninguno
*/
int Buscar(apnodo arbol, TIPO dato)
{
	/*Se ejecuta un ciclo mientras que el apuntador arbol sea diferente de NULL
    y el valor del nodo sea distinto al dato buscado*/
	while (arbol != NULL && arbol->dato != dato)
	{
		/*Se compara el valor del nodo actual con el dato recibido*/
		if (dato < arbol->dato)
			/*Si el dato recibido es menor que el del nodo actual
            * se actualiza el apuntador arbol al apuntador izquierdo del nodo*/
			arbol = arbol->izq;
		else
			/*Si el dato recibido es mayor que el del nodo actual
                * se actualiza el apuntador arbol al apuntador derecho del nodo*/
			arbol = arbol->der;
	}
	/*Se retorna el valor obtenido del condicional. Se retorna 1 si el arbol no
    es NULL y 1 en caso contrario*/
	return arbol != NULL;
}
