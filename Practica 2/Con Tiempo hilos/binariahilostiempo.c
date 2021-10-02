//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************
/**
 * Titulo: Practica 2, algoritmo "Busqueda exponencial con hilos"
 * Descripción: implementacion del algoritmo de busqueda exponencial con hilos
 * Fecha: 27-sep-2021
 * Versión: 4
*/
//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "tiempo.h"
#define min
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************
/*estructura de los parametros que se le envia a la funcion de cada hilo*/
typedef struct
{
    int inicio;
    int fin;
    int buscar;

} parametros;
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
/*
*Recibe: posicion de inicio, posicion final y el elemento a buscar
*Regresa: int
*Errores: Ninguno
*/
int busquedaBinaria(int ini, int n, int x); /*Prototipo de la funcion*/

/*
 * Función: Busqueda exponencial realizada por hilos
 * Descripcion: Cada hilo creado ejecuta esta funcion en la cual se implementa la busqueda en un rango determinado para cada hilo
 * En caso de que se ponga en alto la bandera fg, se finaliza el hilo y termina la funcion. Si el hilo que esta en la funcion encuentra el dato,
 * manda un mensaje indicando que encontro el dato, muestra su ID, posicion y finaliza el hilo.
 * Recibe:
 *  - Apuntador de tipo void
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void *Hilo(void *datos);

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int numHilos = 2, fg = 0;
int *numeros;
//*****************************************************************
//PROGRAMA PRINCIPAL
//*****************************************************************
int main(int argc, char *argv[])
{
    //******************************************************************
    //Variables del main
    //******************************************************************
    double sumwtime, utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    int i, buscar, n;

    parametros param[numHilos];
    pthread_t thread[numHilos];

    //******************************************************************
    //Recepción y decodificación de argumentos
    //******************************************************************

    //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
    if (argc != 2)
    {
        printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
        exit(1);
    }
    //Tomar el segundo argumento como tamaño del algoritmo
    else
    {
        n = atoi(argv[1]);
    }

    numeros = (int *)malloc(sizeof(int) * n); /*Reserva memoria para el arreglo*/
    //Elementos que se buscaran
    int x[] = {322486, 14700764, 3128036, 3128036, 6337399,
               61396, 10393545, 2147445644, 1295390003, 450057883,
               187645041, 1980098116, 152503, 5000, 1493283650,
               214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};

    int xn = sizeof(x) / sizeof(x[0]); //Calcula cuantos numeros se van a buscar

    for (i = 0; i < n; i++)
    { /*Llena el arreglo*/
        scanf("%d", &numeros[i]);
    }

    for (int j = 0; j < xn; j++) //Cuenta el tiempo para cada busqueda
    {
        //DEclaramos los rangos de busqeuda
        int intervalo = n / numHilos;
        int inicio = 0;
        int fin = intervalo - 1;
        //******************************************************************
        //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
        //******************************************************************

        uswtime(&utime0, &stime0, &wtime0);
        //******************************************************************

        //******************************************************************
        //Algoritmo
        //******************************************************************

        //Se van creando los hilos y sus respectivos argumentos
        for (int i = 0; i < numHilos; i++)
        {
            param[i].fin = fin;
            param[i].inicio = inicio;
            param[i].buscar = x[j];

            /*Se crea el un hilo pasando como parametro la estructura y ligado a la funcion Hilo*/
            if (pthread_create(&thread[i], NULL, Hilo, (void *)&param[i]) != 0)
            {
                perror("El thread no  pudo crearse");
                exit(-1);
            }
            /*Se actualiza el rango de busqueda para el siguiente Hilo*/
            inicio = fin + 1;
            fin += intervalo;
        }

        //******************************************************************

        //******************************************************************
        //Evaluar los tiempos de ejecución
        //******************************************************************
        uswtime(&utime1, &stime1, &wtime1);

        /*Se espera a que termine cada Hilo*/
        for (int i = 0; i < numHilos; i++)
            pthread_join(thread[i], NULL);

        //Acumula el tiempo de ejecución del programa
        sumwtime += wtime1 - wtime0;
        fg = 0;
    }

    //Cálculo del tiempo promedio de ejecución del programa
    if (n == 1000000)
        printf("N\tTiempo promedio\n");
    printf("%d\t", n);
    printf("%.10e\n", (double)sumwtime / xn);

    //******************************************************************

    free(numeros); /*Libera la memoria*/
    //Terminar programa normalmente
    exit(0);
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************

/*
*Recibe: posicion de inicio, posicion final y el elemento a buscar
*Regresa: int
*Errores: Ninguno
*/

int busquedaBinaria(int l, int r, int x)
{
    while (l <= r)
    {
        int m = l + (r - l) / 2; //Dvide el arreglo a la mitad
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

void *Hilo(void *datos)
{
    parametros *param = (parametros *)datos;

    if (fg == 1)
        pthread_exit(NULL);

    int num = param->buscar;

    //Almacenamos el valor devuelto por la funcion de busqueda lineal
    int resu = busquedaBinaria(param->inicio, param->fin, param->buscar);

    //Si el resultado es diferente de -1, quiere decir que encontro el resultado
    if (resu != -1)
    {
        fg = 1;
    }

    pthread_exit(NULL);
}