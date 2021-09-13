#include<stdio.h>
#include<stdlib.h>

/*
 * Titulo: Practica 1, algoritmo "Ordenamiento por ABB"
 * Descripción: implementacion del algoritmo ABB
 * Fecha: 13-sep-2021
 * Versión: 1
*/

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*posicion en arreglo*/

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

/*Contador utilizado para la insercion de valores al arreglo en la funcion InOrden*/
POSICION k = 0;

int main(int argc, char* argv[])
{
	TIPO n;

	/*Verifica que se ingrese la longitud n de numeros*/
	if (argc!=2)
	{
		printf("\n Se debe de indicar el tamano de n");
		exit(1);
	}
	else
	{
        	/*convierte la cadena a numero*/
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

    	/*Se insertan los n numeros en el ABB*/
	for(int i = 0; i < n; i++)
		Insertar(&arbol,numeros[i]);

    	/*Se realiza un recorrido In Orden para almacenar los datos en el arreglo*/
	InOrden(arbol,numeros);

    	/*Se imprime el arreglo ordenado*/
	printf("Arreglo en orden: \n");
    	for(int i = 0; i < n; i++)
		printf("%d\n",numeros[i]);

    	/*Se libera la memoria*/
    	free(numeros);
	return 0;
}


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
