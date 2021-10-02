/*
* Titulo: Practica 2, algoritmo "Busqueda binaria"
* Descripcion: Implementacion del algoritmo de busqueda binaria con hilos
* Fecha: 27-sep-2021
* Version: 1.0
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Diseño de la estructura
typedef struct 
{
    int inicio;
    int fin;
    int buscar;

}parametros;

//Esqueleto de las funciones
int busquedaBinaria(int ini, int n, int x); /*Prototipo de la funcion*/
void *Hilo(void *datos);

//Variables globales
int numHilos = 10, fg = 0;
int *numeros;
int n, x, pos;

int main(int argc, char *argv[]){

    int i,buscar;
    pthread_t thread[numHilos];
    parametros param[numHilos];

    //Verifica que se ingrese la longitud n de numeros
    if (argc != 3)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }

    //Convierte la cadena a numero
    n = atoi(argv[1]);
    buscar = atoi(argv[2]);
    
    numeros = malloc(sizeof(int) * n); /*Reserva memoria para el arreglo*/
    
    for (i = 0; i < n; i++)
    { /*Llena el arreglo*/
        scanf("%d", &numeros[i]);
    }

    //Declaramos los rangos de busqueda
    int intervalo = n/numHilos;
    int inicio = 0;
    int fin = intervalo-1;

    //Se va creando hilos y sus respectivos argumentos
    for(i = 0; i<numHilos; i++)
    {
        param[i].fin = fin;
        param[i].inicio = inicio;
        param[i].buscar = buscar;

        /*Se crea el un hilo pasando como parametro la estructura y ligado a la funcion Hilo*/
        if (pthread_create (&thread[i], NULL, Hilo,(void*)&param[i]) != 0 )
        {
            perror("El thread no  pudo crearse");
            exit(-1);
        }
        /*Se actualiza el rango de busqueda para el siguiente Hilo*/
        inicio = fin + 1;
        fin += intervalo;  
    }

    for(i = 0; i<numHilos; i++)
        pthread_join(thread[i], NULL);

    printf("\n\n");
    free(numeros);
    return EXIT_SUCCESS;
}

/*
*Recibe: posicion de inicio, posicion final y el elemento a buscar
*Regresa: int
*Errores: Ninguno
*/

int busquedaBinaria(int l, int r, int x){
    while (l <= r) {
        int m = l + (r - l) / 2;//Dvide el arreglo a la mitad
        // Revisa si x esta en la mitad
        if (numeros[m] == x)
            return m;
        // Si x es mayor, se va por la derecha
        if (numeros[m] < x)
            l = m + 1;
        // Si x es menor, se va por la izquierda
        else
            r = m - 1;
    }
    // Si el elemento no se encuentra regresa -1
    return -1;
}

/*
 * Función: Busqueda binaria realizada por hilos
 * Descripcion: Cada hilo creado ejecuta esta funcion en la cual se implementa la busqueda en un rango determinado para cada hilo
 * En caso de que se ponga en alto la bandera fg, se finaliza el hilo y termina la funcion. Si el hilo que esta en la funcion encuentra el dato,
 * manda un mensaje indicando que encontro el dato, muestra su ID, posicion y finaliza el hilo.
 * Recibe:
 *  - Apuntador de tipo void
 * Regresa:
 *  - void
 * Errores: ninguno
*/

void *Hilo(void* datos){
    parametros *param = (parametros*)datos;

    if(fg == 1)
        pthread_exit(NULL);

    int num = param->buscar;

    //Almacenamos el valor devuelto por la funcion de busqueda lineal
    int resu = busquedaBinaria(param->inicio, param->fin, param->buscar);

    //Si el resultado es diferente de -1, quiere decir que encontro el resultado
    if(resu != -1)
    {
        printf("\nEl hilo con ID %lu encontro el dato: %d en la posicion %d",pthread_self(),num, resu);
        fg = 1;
    }
    else//Si no, quiere decir que el hilo no lo encontro en su arreglo
        printf("\nEl hilo con ID %lu no encontro el dato: %d",pthread_self(),num);

    pthread_exit(NULL);

}