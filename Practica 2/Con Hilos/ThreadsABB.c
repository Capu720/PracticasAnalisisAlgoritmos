#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include<unistd.h>

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*posicion en arreglo*/

typedef struct Nodo
{
    int dato;
    struct Nodo *izq, *der;
}nodo;

typedef nodo *apnodo; /*Apuntador a estructura nodo*/

typedef struct Informacion
{
    int inf;
    int sup;
}info;

void *Hilo(void *datos);
void Insertar(apnodo *arbol, TIPO dato);
int Buscar(apnodo arbol, TIPO dato);

TIPO *numeros, dato, n, fg = 0;

int main(int argc, char* argv[])
{
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
    numeros = malloc(n * sizeof(TIPO));

    /*Lee y almacena los n numeros en el arreglo creado*/
    for(int i = 0; i < n; i++)
        scanf(FORMATO,&numeros[i]);

    /*Se crea un apuntador de tipo nodo para ser la raiz inicial del ABB*/
    info *datos = malloc(10 * sizeof(apnodo));
    pthread_t *thread;

    thread = malloc(10*sizeof(pthread_t));

    int interv = n/10;
    int inicio = 0;
    int fin = interv - 1;

    for(int i = 0; i < 10; i++)
    {
        datos[i].inf = inicio;
        datos[i].sup = fin;
        if(fg == 1)
            break;

        if (pthread_create (&thread[i], NULL, Hilo,(void*)&datos[i]) != 0 )
        {
            perror("El thread no  pudo crearse");
            exit(-1);
        }
        inicio = fin + 1;
        fin += interv;
    }

    for(int i = 0; i < 10; i++) pthread_join (thread[i], NULL);

    /*Se libera la memoria*/
    free(numeros);
    return 0;
}

void *Hilo(void* datos)
{
    info *data = (info*)datos;

    apnodo arbol = NULL;
    /*Se insertan los n numeros en el ABB*/
    if(fg == 1)
        pthread_exit(NULL);


    for(int i = data->inf; i < data->sup; i++)
        Insertar(&arbol,numeros[i]);

    if(Buscar(arbol,dato))
    {
        printf("\nEl hilo con ID %lu encontro el dato: %d",pthread_self(),dato);
        fg = 1;
    }
    else
        printf("\nEl hilo con ID %lu no encontro el dato: %d",pthread_self(),dato);

    pthread_exit(NULL);
}

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
