#include <stdio.h>
#include <stdlib.h>

/*
 * Titulo: Practica 2, algoritmo "Busqueda en ABB"
 * Descripción: implementacion del algoritmo ABB
 * para la busqueda de elementos
 * Fecha: 23-sep-2021
 * Versión: 1
*/

#define TIPO int	 /*tipo de datos que se ingresaran*/
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
} nodo;

typedef nodo *apnodo; /*Apuntador a estructura nodo*/

void Insertar(apnodo *arbol, TIPO dato);
int Buscar(apnodo arbol, TIPO dato);

int main(int argc, char *argv[])
{
	TIPO n, dato;

	/*Verifica que se ingrese el tamano de n y el dato a buscar*/
	if (argc < 3)
	{
		printf("\n Se debe de indicar el tamano de n y el dato a buscar");
		exit(1);
	}
	else
	{
		/*convierte la cadenas a numeros*/
		n = atoi(argv[1]);
		dato = atoi(argv[2]);
	}

	/*Solicita memoria al sistema con la funcion malloc*/
	TIPO *numeros;
	numeros = malloc(n * sizeof(TIPO));

	/*Lee y almacena los n numeros en el arreglo creado*/
	for (int i = 0; i < n; i++)
		scanf(FORMATO, &numeros[i]);

	/*Se crea un apuntador de tipo nodo para ser la raiz inicial del ABB*/
	apnodo arbol = NULL;

	/*Se insertan los n numeros en el ABB*/
	for (int i = 0; i < n; i++)
		Insertar(&arbol, numeros[i]);

	/*Se realiza la funcion de busqueda en el ABB*/
	if (Buscar(arbol, dato))
		printf("\nSe encontro el dato: %d", dato);
	else
		printf("\nNo se encontro el dato: %d", dato);

	/*Se libera la memoria*/
	free(numeros);
	return 0;
}

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
