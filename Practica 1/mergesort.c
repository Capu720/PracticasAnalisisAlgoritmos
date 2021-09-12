#include <stdio.h>
#include <stdlib.h>
/**
 * Titulo: Practica 1, algoritmo "Ordenamiento Mergesort"
 * Descripción: implementacion del algoritmo mergesort
 * Fecha: 13-sep-2021
 * Versión: 1
 * nota: revisar pagina 106 Algorithmics, the spirit of computing
*/
#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/

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
    if ((numeros = malloc(sizeof(TIPO) * n)) == NULL)
        perror("No se pudo solicitar memoria para el arreglo");
    /*lee numero por numero de un archivo*/
    for (i = 0; i < n; i++)
        scanf(FORMATO, &numeros[i]);
    /*se llama a la función*/
    MergeSort(numeros, 0, n - 1);
    /*se imprime el arreglo ordenado*/
    for (j = 0; j < n; j++)
        printf("%d\n", numeros[j]);
    /*Se libera la memoria*/
    free(numeros);
    return EXIT_SUCCESS;
}
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