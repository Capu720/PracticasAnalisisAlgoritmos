#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include<unistd.h>

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*posicion en arreglo*/

/*
* Se define la estructura Nodo para la construccion del ABB
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
* Se define la estructura Informacion para pasar como parametro a los hilos
* La estructura tiene como elementos:
* - Variable "inf" de tipo int que sera el limite inferior del sub arreglo a analizar
* - Variable "sup" de tipo int que sera el limite superior del sub arreglo a analizar
*/
typedef struct Informacion
{
    int inf;
    int sup;
}info;

void *Hilo(void *datos);
void Insertar(apnodo *arbol, TIPO dato);
int Buscar(apnodo arbol, TIPO dato);

/*
 * Variables globales
 * - numeros es el apuntador para crear el arreglo dinamico que almacena los datos a buscar
 * - dato es el numero a buscar en el arreglo
 * - n es el numero de elementos a almacenar (tamano de problema)
 * - fg sirve como bandera para indicar que el elemento fue encontrado
 */
TIPO *A, dato, n, fg = 0;

int main(int argc, char* argv[])
{
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

    A = (int*)malloc(sizeof(int)*n); /*Reserva memoria para el arreglo*/
    //Elementos que se buscaran
    int x[] = { 322486, 14700764,   3128036,    3128036,    6337399,
                61396,  10393545,   2147445644, 1295390003, 450057883,
                187645041,  1980098116, 152503, 5000, 1493283650,
                214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};

    int xn = sizeof(x) / sizeof(x[0]);//Calcula cuantos numeros se van a buscar

	int i;
	
    for (i = 0; i < n; i++){/*Llena el arreglo*/
        scanf("%d",&A[i]);
    }

	/*Se crea un apuntador de tipo nodo para ser la raiz inicial del ABB*/
	apnodo arbol = NULL;    
	/*Se insertan los n numeros en el ABB*/
	for (i = 0; i < n; i++)
		Insertar(&arbol, A[i]);

    /*Se crea un arreglo de estructuras de tipo info para pasar a cada hilo*/
    info *datos = malloc(10 * sizeof(apnodo));
    /*Se crea un arreglo de 10 hilos*/
    pthread_t *thread;
    thread = malloc(10*sizeof(pthread_t));

    /*Se genera el intervalo inicial para el primer hilo*/
    int interv = n/10;
    int inicio = 0;
    int fin = interv - 1;

    /*Se realiza un ciclo para la creación de 10 hilos*/
    for(i = 0; i < 10; i++)
    {
        /*Se asignan el intevalo de busqueda en la estructura*/
        datos[i].inf = inicio;
        datos[i].sup = fin;
        /*Se finaliza el ciclo si la bandera es igual a 1*/
        if(fg == 1)
            break;

        /*Se crea el un hilo pasando como parametro la estructura y ligado a la funcion Hilo*/
        if (pthread_create (&thread[i], NULL, Hilo,(void*)&datos[i]) != 0 )
        {
            perror("El thread no  pudo crearse");
            exit(-1);
        }
        /*Se actualiza el rango de busqueda para el siguiente Hilo*/
        inicio = fin + 1;
        fin += interv;
    }

    /*Se espera a que termine cada Hilo*/
    for(i = 0; i < 10; i++) pthread_join (thread[i], NULL);

    /*Se libera la memoria*/
    free(A);
    return 0;
}

/*
 * Funcion: Busqueda binaria realizada por hilos
 * Descripcion: Cada hilo creado ejecuta esta funcion en la cual se implementa la busqueda e insercion en un rango determinado para cada hilo
 * En caso de que se ponga en alto la bandera fg, se finaliza el hilo y termina la funcion. Si el hilo que esta en la funcion encuentra el dato,
 * manda un mensaje indicando que encontro el dato, muestra su ID y finaliza el hilo.
 * Recibe:
 *  - Apuntador de tipo void
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void *Hilo(void* datos)
{
    info *data = (info*)datos;

    apnodo arbol = NULL;
    /*Se insertan los n numeros en el ABB*/
    if(fg == 1)
        pthread_exit(NULL);

    /*Inserta los datos dentro de su rango en el arbol*/
    for(int i = data->inf; i < data->sup; i++)
        Insertar(&arbol,A[i]);

    /*Realiza la busqueda en su arbol*/
    if(Buscar(arbol,dato))
    {
        printf("\nEl hilo con ID %lu encontro el dato: %d",pthread_self(),dato);
        fg = 1;
    }
    else
        printf("\nEl hilo con ID %lu no encontro el dato: %d",pthread_self(),dato);

    pthread_exit(NULL);
}

/*
 * Funcion: Realiza la insercion de un nodo al ABB
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
    if(*arbol == NULL)
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
        while(temp != NULL)
        {
            /*Se guarda la posicion actual del apuntador temporal antes de ser actualizado*/
            anterior = temp;

            /*Se compara el valor del nodo actual con el dato recibido*/
            if(dato < temp->dato)
                /*Si el dato recibido es menor que el del nodo actual
                 * se actualiza el apuntador temporal al apuntador izquierdo del nodo*/
                temp = temp->izq;
            else
                /*Si el dato recibido es mayor que el del nodo actual
                 * se actualiza el apuntador temporal al apuntador derecho del nodo*/
                temp = temp->der;
        }

        /*Se compara el dato de la posicion anterior con el dato recibido*/
        if(dato <= anterior->dato)
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
 * Funcion: Realiza la busqueda de un dato en el ABB
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
     *    	y el valor del nodo sea distinto al dato buscado*/
    while(arbol != NULL && arbol->dato != dato)
    {
        /*Se compara el valor del nodo actual con el dato recibido*/
        if(dato < arbol->dato)
            /*Si el dato recibido es menor que el del nodo actual
             * se actualiza el apuntador arbol al apuntador izquierdo del nodo*/
            arbol = arbol->izq;
        else
            /*Si el dato recibido es mayor que el del nodo actual
             * se actualiza el apuntador arbol al apuntador derecho del nodo*/
            arbol = arbol->der;
    }
    /*Se retorna el valor obtenido del condicional. Se retorna 1 si el arbol no
     *        es NULL y 1 en caso contrario*/
    return arbol != NULL;
}
