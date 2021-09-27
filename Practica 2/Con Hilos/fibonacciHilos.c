#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/
#define TAM 6

#define ESTA(pos) (pos != -1)/*verifica si existe la posicion*/
#define min(x,y)   ((x<=y) ? x:y)

/*estructura de los parametros que se le envia a la funcion de cada hilo*/
typedef struct 
{
      TIPO* arr;
      TIPO buscar;
      TIPO n;
      TIPO* pos;
}parametros;

/**
 * Titulo: Practica 2, algoritmo "Busqueda de Fibonacci"
 * Descripción: implementacion del algoritmo de busqueda de Fibonacci
 * Fecha: 27-sep-2021
 * Versión: 3
*/
/**
 * Función:realiza la busqueda de Fibonacci
 * Descripcion: parecido a la busqueda binaria, busqueda de fibonacci, va comparando con porciones en terminos de la serie de fibonacci.
 * Recibe: 
 *  - arreglo de numeros
 *  - el numero a buscar
 *  - longitud del arreglo
 * Regresa:
 *  - posicion del numero encontrado (o no)
 * Errores: ninguno
*/
void* fibMonaccianSearch(void* args);

int main(int argc, char const *argv[])
{
    
    TIPO n, buscar, *numeros,pos;
    POSICION i;


    parametros param[TAM];
    pthread_t hilo[TAM];
    
    /*Verifica que se ingrese la longitud n de numeros*/
    if (argc != 3)
    {
        printf("Falto escribir el valor de n y el numero a busar");
        exit(EXIT_FAILURE);
    }
    /*convierte la cadena a numero*/
    n = atoi(argv[1]);
    buscar = atoi(argv[2]);
    /*Solicita memoria con la funcion malloc, en caso de fracaso, regresará error*/
    if ((numeros = malloc(sizeof(TIPO) * n)) == NULL)
        perror("No se pudo solicitar memoria para el arreglo");
    /*lee numero por numero de un archivo*/
    for (i = 0; i < n; i++)
        scanf(FORMATO, &numeros[i]);

    /*se llama a la función*/

    
    pos=-1;
    /*se crea cada hilo con los argumentos que se muestran a continuacion, se usó arreglo de estructuras, ya que se le manda el apuntador*/
    for ( i = 0; i < TAM; i++)
    {
        param[i].arr=&numeros[i*n/TAM]; // va creciendo de n/tam cada indice
        param[i].buscar=buscar;//se le manda el numero a buscar
        param[i].pos=&pos;//se manda el apuntador de la posicion
        param[i].n=(i+1)*(n/TAM);  // va creciendo de n/tam cada indice
        pthread_create(&hilo[i], NULL, fibMonaccianSearch, (void*)&param[i]);
    }
    
    for ( i = 0; i < TAM; i++)
    {
    
    pthread_join(hilo[i], NULL);//se espera a que termine cada hilo
    }

    /*se verifica si se encontro el numero*/
    ESTA(*(param->pos)) ? printf("Se encuentra en la posicion: %d\n", *(param->pos)) : printf("no se encuentra");
    /*se libera la memoria*/
    free(numeros);
    return EXIT_SUCCESS;
}
/**
 * Función:realiza la busqueda de Fibonacci
 * Descripcion: parecido a la busqueda binaria, busqueda de fibonacci, va comparando con porciones en terminos de la serie de fibonacci.
 * Recibe: 
 *  - arreglo de numeros
 *  - el numero a buscar
 *  - longitud del arreglo
 * Regresa:
 *  - posicion del numero encontrado (o no)
 * Errores: ninguno
*/
//POSICION fibMonaccianSearch(TIPO arr[], TIPO buscar, TIPO n);
void* fibMonaccianSearch(void* args)
{
    POSICION i;
    TIPO *arr,buscar,n;
    parametros *param=(parametros*)args;

    if(ESTA(*(param->pos)))
        pthread_exit(NULL);
    arr=(TIPO*)param->arr;
    buscar=(TIPO)param->buscar;
    n=(TIPO)param->n;
    /* printf("\n n %d",n);
    printf("\n arr[0] %d\n",arr[0]);
     printf("\n pos %d\n",*(param->pos)); */
    
    /* Inicializar variables (Los primeros numeros de la serie de Fibonacci  0 1 1 )*/
    //Fm = F[m-1]+F[m-2]   e.g.    F[5] = F[3]+F[2]  ya que   0 1 1 "2 3 5" 8 13
    POSICION fibM2 = 0;            // numero (m-2) fibonacci (anterior del anterior)
    POSICION fibM1 = 1;            // numero (m-1) fibonacci (anterior)
    POSICION fibM = fibM2 + fibM1; // numero m Fibonacci
    //por lo tanto queda asi:  fibM = fibM1 + fibM2       1 = 1 + 0

    /* fibM guarda el numero mas pequeño de fibonacci mas grande o igual que n */
    /*va creando la serie de Fibonacci hasta encontrar dicho numero 1 1 2 3 5.... >=n*/
    while (fibM < n)
    {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    POSICION inicio = -1; /*marca el inicio donde se iterará con la serie de fibonacci*/
    /*Busca la posicion */
 
    while (fibM > 1)
    {
        // busca el alcance, hasta donde cubre, fibM2 (F[n-2])
        i = min(inicio + fibM2, n - 1);
        /* si le numero a buscar, es mayor al numero del arreglo en la posicion i, recorre la posicion de la serie de fibonacci y ahora inicio es la posicion i, es decir, se descarta las posiciones antes de ese i*/
        if (arr[i] < buscar)
        {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            inicio = i;
        }

        /* si buscar es menor, se recorre dos posiciones  */
        else if (arr[i] > buscar)
        {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }

        /* si lo encuentra, regresa la posicion */
        else{
           *(param->pos)=i;
            pthread_exit(NULL);
        }
    }

    /* compara el ultimo numero con buscar */
    if (fibM1 && arr[inicio + 1] == buscar)
    {
        *(param->pos)= inicio + 1;
        pthread_exit(NULL);
    }

    /*como no lo encontró, regresa -1 */
    *(param->pos)= -1;
    pthread_exit(NULL);
}
