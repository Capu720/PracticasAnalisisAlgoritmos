#include <stdio.h>
#include <stdlib.h>
/**
 * Titulo: Practica 1, algoritmo "Ordenamiento QuickSort"
 * Descripción: implementacion del algoritmo QuickSort
 * Fecha: 13-sep-2021
 * Versión: 1
*/
#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/

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

int main(int argc, char const *argv[])
{
    TIPO n, *numeros;
    int i, j;
    /*Verifica que se ingrese la longitud n de numeros*/
    if (argc != 2)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }
    /*convierte la cadena a numero*/
    n = atoi(argv[1]);

    /*Solicita memoria con la funcion malloc, en caso de fracaso, regresará error*/
    if ((numeros = malloc(sizeof(int) * n)) == NULL)
        perror("No se pudo solicitar memoria para el arreglo");
    /*lee numero por numero de un archivo*/
    for (i = 0; i < n; i++)
        scanf(FORMATO, &numeros[i]);
/*se llama a la función*/
    QuickSort(numeros, 0, n-1);
    /*se imprime el arreglo ordenado*/
    for (i = 0; i < n; i++)
        printf("%d\n", numeros[i]);
    /*Se libera la memoria*/
    free(numeros);
    return EXIT_SUCCESS;
}

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
    POSICION pivote, i, j,k;
    /*toma el pivote como el primer elemento*/
    pivote = numeros[inicio];
    /*guarda la siguiente posición*/
    i = inicio + 1;
    /*guarda la ultima posición*/
    j = final;

    do{
        /*busca que numero no es menor que el pivote para poder ser intercambiado*/
        while (numeros[i] <= pivote && i < final)
            i++;
        /*busca que numero no es mayor que el pivote para poder ser intercambiado*/
        while (numeros[j] > pivote)
            j--;

        /*si la posicion de la izquierda es menor a la derecha, se intercambian sus valores*/
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
    }while(1);
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