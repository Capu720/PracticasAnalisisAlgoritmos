//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

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

//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************

/*Funcion de busqueda eponencial
Recibe como parametros un arreglo, el tamanio del arreglo, y el numero a buscar
La siguiente funcion realiza de forma iterativa el algoritmo de busqueda exponencial
Regresa como valor la posicion donde se encuentra el elemento, o un -1 si no lo encunetra
NO presenta errores
*/
int BusquedaExponencial(int *, int , int);/*Prototipo de la funcion*/

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
	int result = BusquedaExponencial(A,n,x[i]);
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
	printf("%.10e\t", sumwtime/xn);
	
	//******************************************************************

    free(A);/*Libera la memoria*/
	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************
/*Funcion de busqueda eponencial
Recibe como parametros un arreglo, el tamanio del arreglo, y el numero a buscar
La siguiente funcion realiza de forma iterativa el algoritmo de busqueda exponencial
Regresa como valor la posicion donde se encuentra el elemento, o un -1 si no lo encunetra
NO presenta errores
*/
int BusquedaExponencial(int *A, int n, int num)
{
	//Primero checamos si el primer elemento del arreglo es el que buscamos
	if(A[0] == num)
		return 0;
		
	int pos = 1; //Declaramos una variable para acceder a la posicion del arreglo
	
	/*Se realiza un ciclo while donde el elemento a buscar debe de estar presente. Compara si la posicion es menor
	  al tamanio del arreglo y si el numero que esta en el arreglo menor o igual al numero a buscar*/
	
	while(pos < n && A[pos] <= num)
		pos = pos * 2;
	
	/*Una vez encontrado el rango en donde esta el numero, se realiza una busqueda de forma binaria*/
	
	/*Declaramos los primeros valores de los rangos*/
	int low = pos/2;
	int high = min(pos, n-1);
	
	while(low <= high)
	{
		pos = low + (high-low)/2;
		
		if(A[pos] == num) // Si encontramos el numero en la posicion del arreglo, regresamos la posicion
			return pos;
			
		else if(A[pos] < num)//Comparamos si el numero en la posicion en el arrego es menor al numero, e incrementar el rango menor
			low = pos + 1;
		
		else
			high = pos - 1;//Si no se cumple lo anterior, se decrementa el rango mayor
	}
	
	return -1;//Si no esta regresa -1
	
}