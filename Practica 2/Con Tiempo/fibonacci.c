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
 * Titulo: Practica 2, algoritmo "Busqueda de Fibonacci"
 * Descripción: implementacion del algoritmo de busqueda de Fibonacci
 * Fecha: 27-sep-2021
 * Versión: 2
*/
//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/

#define ESTA(pos) (pos != -1)/*verifica si existe la posicion*/
#define min
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
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
POSICION fibMonaccianSearch(TIPO arr[], TIPO buscar, TIPO n);

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double sumwtime, utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n=atoi(argv[1]);
	}

    int *A = (int*)malloc(sizeof(int)*n); /*Reserva memoria para el arreglo*/
    //Elementos que se buscaran
    int x[] = { 322486, 14700764,   3128036,    3128036,    6337399,
                61396,  10393545,   2147445644, 1295390003, 450057883,
                187645041,  1980098116, 152503, 5000, 1493283650, 
                214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};

    int xn = sizeof(x) / sizeof(x[0]);//Calcula cuantos numeros se van a buscar

    for (i = 0; i < n; i++){/*Llena el arreglo*/
        scanf("%d",&A[i]);
    }
	
    for (i = 0; i < xn; i++){//Cuenta el tiempo para cada busqueda
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	fibMonaccianSearch(A,x[i],n);
	//******************************************************************

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	
	//Acumula el tiempo de ejecución del programa
	sumwtime += wtime1 - wtime0;
    }

    //Cálculo del tiempo promedio de ejecución del programa
	if(n==1000000)
		printf("N\tTiempo promedio\n");
    printf("%d\t", n);
	printf("%.10e\n", (double)sumwtime/xn);
	
	//******************************************************************

    free(A);/*Libera la memoria*/
	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
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
POSICION fibMonaccianSearch(TIPO arr[], TIPO buscar, TIPO n)
{
    POSICION i;
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
        else
            return i;
    }

    /* compara el ultimo numero con buscar */
    if (fibM1 && arr[inicio + 1] == buscar)
    {
        return inicio + 1;
    }

    /*como no lo encontró, regresa -1 */
    return -1;
}