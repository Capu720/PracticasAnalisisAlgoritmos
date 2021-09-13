/*
* Titulo: Practica 1, algoritmo "Ordenamiento de Burbuja Osptimiazion 1"
* Descripcion: Implementacion del algoritmo Burbuja con una primera optimizacion
* Fecha: 13-sep-2021
* Version: 1.0
*/
#include<stdio.h>
#include<stdlib.h>

void burbujaOpt1(int A[], int n);/*Protipo de la funcion*/
/*
*Recibe: Un areglo y el tamanio
*Regresa: void
*Errores: Ninguno
*/

/*Funcion principal*/
int main(int argc, char* argv[]){
    int i, n=atoi(argv[1]); /*Tomar el segundo argumento como tamaño del algoritmo*/
    int *A = (int*)malloc(sizeof(int)*n); /*Reserva memoria para el arreglo*/

    for (i = 0; i < n; i++){/*Llena el arreglo*/
        scanf("%d",&A[i]);
    }

    burbujaOpt1(A,n);/*Llamada a la funcion de ordenamiento*/

    for (i = 0; i < n; i++){/*Impresion de los elementos del arreglo*/
        printf("%d\n",A[i]);
    }

    free(A);/*Libera la memoria*/

    return 0;
}

/*Definicion de funciones*/
void burbujaOpt1(int A[], int n){/*recibe un arreglo y el tamanio de este*/
    int i, j, aux;/*declaracion de variables*/

    for(i=0; i<=n-2; i++){
        for(j=0; j<=n-2-i; j++){/*Optimizacion: Despues de cada iteracion el mayor queda ordenado, ya no se compara.*/
            if(A[j]>A[j+1]){/*Si el elemento actual es mayor que el siguiente los intercambia*/
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
            }
        }
    }
}