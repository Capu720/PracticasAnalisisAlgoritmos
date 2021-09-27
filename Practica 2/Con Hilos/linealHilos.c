#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_HILOS 4

int *A, n, x;

void * funHilo(void * arg);

int busquedaLineal(int arr[], int n, int x);

int main(int argc, char *argv[]){
    int register i;
    pthread_t hilos[NUM_HILOS];
    int n = atoi(argv[1]);
    A = malloc(sizeof(int) * n); /*Reserva memoria para el arreglo*/
    
    //Elementos que se buscaran
    int num[] = {322486, 14700764, 3128036, 3128036, 6337399,
               61396, 10393545, 2147445644, 1295390003, 450057883,
               187645041, 1980098116, 152503, 5000, 1493283650,
               214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
    int xn = sizeof(num) / sizeof(num[0]); //Calcula cuantos numeros se van a buscar
    
    for (i = 0; i < n; i++)
    { /*Llena el arreglo*/
        scanf("%d", &A[i]);
    }

    x = 0;

    for(i=0; i<NUM_HILOS; i++){
        pthread_create(&hilos[i], NULL, funHilo, NULL);
    }
    for(i=0; i<NUM_HILOS; i++){
        pthread_join(hilos[i], NULL);
    }

    return 0;
}

void * funHilo(void * arg){
    int i, tam, tamu, result;
    tam = n/NUM_HILOS;
    tamu = tam + n%NUM_HILOS;

    for (i = 0; i < n; i++){ //Recorre el arreglo
        if (A[i] == x)    //Compara el elemento buscado con el de la posicion i
            result = i;       //Regresa la posicion donde se encuentra
        else result = -1;
    }

    if (result == -1)
            printf("El elemento %d no esta en el arreglo\n", x);
        else
            printf("El elemento %d esta en la posicion %d\n", x, result);
    pthread_exit(NULL);
}

int busquedaLineal(int arr[], int n, int x){
    int i;                  //Declara el indice
    for (i = 0; i < n; i++) //Recorre el arreglo
        if (arr[i] == x)    //Compara el elemento buscado con el de la posicion i
            return i;       //Regresa la posicion donde se encuentra
    return -1;
}