/*
* Titulo: Practica 1, algoritmo "Ordenamiento de Burbuja Optimizacion 2"
* Descripcion: Implementacion del algoritmo Burbuja con una segunda optimizacion
* Fecha: 13-sep-2021
* Version: 1.0
*/
#include<stdio.h>
#include<stdlib.h>

void burbujaOpt2(int A[], int n);/*Prototipo de la funcion*/
/*
*Recibe: Un areglo y el tamanio
*Regresa: void
*Errores: Ninguno
*/

/*Funcion principal*/
int main(int argc, char* argv[]){
    int i, n=atoi(argv[1]); /*Tomar el segundo argumento como tamaño del algoritmo*/
    int *A = (int*)malloc(sizeof(int)*n); /*Reservacion de memoria para el arreglo*/

    for (i = 0; i < n; i++){/*Llena el arreglo*/
        scanf("%d",&A[i]);
    }

    burbujaOpt2(A,n);/*Llamada a la funcion de ordenamiento*/

    for (i = 0; i < n; i++){/*Impresion de los elementos del arreglo*/
        printf("%d\n",A[i]);
    }

    free(A);/*Libera la memoria*/

    return 0;
}

/*Definicion de funciones*/
void burbujaOpt2(int A[], int n){/*recibe un arreglo y el tamanio de este*/
    int i, j, aux, cambios;/*declaracion de variables*/

    cambios = 1;/*bandera*/
    i = 0;
    while(i <= n-1 && cambios != 0){/*Revisa si hubo cambios en el arreglo*/
        cambios = 0;/*Se coloca la bandera en sin cambios*/
        for(j=0; j<=n-2-i; j++){/*Optimizacion: Despues de cada iteracion el mayor queda ordenado, ya no se compara.*/
            if(A[j]>A[j+1]){/*Si el elemento actual es mayor que el siguiente los intercambia*/
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
                cambios = 1;/*Mientras entre a la condicion hay cambios*/
            }
        }
        i = i+1;
    }
}