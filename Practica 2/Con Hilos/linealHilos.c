#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_HILOS 4

int *A, n, x, pos;

void * busquedaLineal(void * arg);

int main(int argc, char *argv[]){
    int indices[NUM_HILOS];
    int i;
    pthread_t hilos[NUM_HILOS];
    n = atoi(argv[1]);
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
    pos=-1;

    for(i=0; i<NUM_HILOS; i++){
        indices[i]=i;
        pthread_create(&hilos[i], NULL, busquedaLineal, (void*)&indices[i]);
    }
    for(i=0; i<NUM_HILOS; i++){
        pthread_join(hilos[i], NULL);
        if (pos == -1)
            printf("El elemento %d no esta en el arreglo\n", x);
        else
            printf("El elemento %d esta en la posicion %d\n", x, pos);
    }

    return 0;
}

void *busquedaLineal(void * arg){
    int i;
    //printf("%d %d %d ", n, x, pos);
    if(pos != -1)
        pthread_exit(NULL);

    for (i = 0; i < n; i++){//Recorre el arreglo
        if (A[i] == x){     //Compara el elemento buscado con el de la posicion i
            pos = i;        //Regresa la posicion donde se encuentra
            pthread_exit(NULL);
        }          
    }
    pos = -1;
    pthread_exit(NULL);
}
