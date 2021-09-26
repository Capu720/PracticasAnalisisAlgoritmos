/*
* Titulo: Practica 2, algoritmo "Busqueda Lineal"
* Descripcion: Implementacion del algoritmo de busqueda lineal
* Fecha: 27-sep-2021
* Version: 1.0
*/
#include <stdio.h>
#include <stdlib.h>

/*
*Recibe: Un areglo, el tamanio y el elemento a buscar
*Regresa: int
*Errores: Ninguno
*/
int busquedaLineal(int arr[], int n, int x); /*Prototipo de la funcion*/

// Funcion principal
int main(int argc, char *argv[])
{
    int i;                                   //Variable iterador
    int n = atoi(argv[1]);                   /*Tomar el segundo argumento como tamanio del arreglo*/
    int *A = (int *)malloc(sizeof(int) * n); /*Reserva memoria para el arreglo*/
    //Elementos que se buscaran
    int x[] = {322486, 14700764, 3128036, 3128036, 6337399,
               61396, 10393545, 2147445644, 1295390003, 450057883,
               187645041, 1980098116, 152503, 5000, 1493283650,
               214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};

    int xn = sizeof(x) / sizeof(x[0]); //Calcula cuantos numeros se van a buscar

    for (i = 0; i < n; i++)
    { /*Llena el arreglo*/
        scanf("%d", &A[i]);
    }

    for (i = 0; i < xn; i++)
    {
        // Llamada a la funcion
        int result = busquedaLineal(A, n, x[i]);
        if (result == -1)
            printf("El elemento %d no esta en el arreglo\n", x[i]);
        else
            printf("El elemento %d esta en la posicion %d\n", x[i], result);
    }

    free(A); /*Libera la memoria*/
    return 0;
}

/*
*Recibe: Un areglo, el tamanio y el elemento a buscar
*Regresa: int
*Errores: Ninguno
*/
int busquedaLineal(int arr[], int n, int x)
{
    int i;                  //Declara el indice
    for (i = 0; i < n; i++) //Recorre el arreglo
        if (arr[i] == x)    //Compara el elemento buscado con el de la posicion i
            return i;       //Regresa la posicion donde se encuentra
    return -1;              //Regresa -1 si no lo encuentra
}