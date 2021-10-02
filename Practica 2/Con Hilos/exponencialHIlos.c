/*
* Titulo: Practica 2, algoritmo "Busqueda Binaria"
* Descripcion: Implementacion del algoritmo de busqueda exponencial con hilos
* Fecha: 27-sep-2021
* Version: 1.0
*/
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define min

//Diseño de la estructura

//Esqueleto de la funcion
void BusquedaExponencial(int *, int, int);
void *Busqueda(void *);

int numHilos = 11;
int l, h, num = 434, n = 500, aux, bandhilos = 0, auxhil = 0, posi_hilo = -1;
int *A;
int *rango_inf;
int *rango_sup;

int main()
{
	int i;

	/*//Verifica que se ingrese la longitud n de numeros
    if (argc != 2)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }
    //convierte la cadena a numero
    n = atoi(argv[1]);*/

	A = (int *)malloc(sizeof(int) * n);
	rango_inf = (int *)malloc(sizeof(int) * numHilos);
	rango_sup = (int *)malloc(sizeof(int) * numHilos);
	/*int x[] = { 322486, 14700764,   3128036,    3128036,    6337399,
                61396,  10393545,   2147445644, 1295390003, 450057883,
                187645041,  1980098116, 152503, 5000, 1493283650, 
                214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
    */
	//Metiendo numeros al arreglo
	for (i = 0; i < n; i++)
		A[i] = i;

	/*Generando el proceso con los hilos
	La idea basica es pasarle un rango del arreglo a cada uno de los arreglos
	asi el primero que lo encuentre sera una especie mas rapida
	*/
	BusquedaExponencial(A, n, num);
	printf("\n\n");
}

/*Funcion de busqueda eponencial
Recibe como parametros un arreglo, el tamanio del arreglo, y el numero a buscar
La siguiente funcion realiza de forma iterativa el algoritmo de busqueda exponencial
*/

void BusquedaExponencial(int *A, int n, int num)
{
	//Primero checamos si el primer elemento del arreglo es el que buscamos
	if (A[0] == num)
		printf("Número encontrado en la posicion 0");

	int pos = 1; //Declaramos una variable para acceder a la posicion del arreglo

	/*Se realiza un ciclo while donde el elemento a buscar debe de estar presente. Compara si la posicion es menor
	al tamanio del arreglo y si el numero que esta en el arreglo menor o igual al numero a buscar*/

	while (pos < n && A[pos] <= num)
		pos = pos * 2;

	/*Una vez encontrado el rango en donde esta el numero, se realiza una busqueda de forma binaria*/

	/*Declaramos los primeros valores de los rangos*/

	pthread_t *thread = malloc(numHilos * sizeof(pthread_t));
	//int low1 = pos/2;
	int high1 = min(pos, n - 1);
	int division = high1 / numHilos;
	int j = 0, h = 0;

	//Definimos los rangos para cada hilo
	while (h < high1)
	{

		if (j == 0)
		{
			l = pos / 2;
			h = l + division - 1;
		}

		else
		{
			aux = h;
			l = h + 1;
			h = aux + division;
		}
		rango_inf[j] = l;
		rango_sup[j] = h;
		j++;
	}
	
	for (int i = 1; i < numHilos; i++)
	{
		if (pthread_create(&thread[i], NULL, Busqueda, (void *)i) != 0)
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
		pthread_join(thread[i], NULL);
		posi_hilo++;
	}
}

void *Busqueda(void *id)
{

	int n_thread = (int)id;
	int pos, band = 0;
	int high = rango_sup[posi_hilo];
	int low = rango_inf[posi_hilo];

	printf("\n\tSoy el thread %d\tMe toco el rango de buesqueda %d - %d", n_thread, low, high);

	if (bandhilos == 1)
		printf("\n\tEl hilo %d ya ha encontrado el elemento", auxhil);

	else
	{
		if (high < n && low < n)
		{
			while (low <= high)
			{
				pos = low + (high - low) / 2;

				if (A[pos] == num)
				{ // Si encontramos el numero en la posicion del arreglo, regresamos la posicion
					printf("\n\tSoy el thread %d\t y encontre el numero %d en la posicion %d", n_thread, num, pos);
					band = 1;
					bandhilos = 1;
					auxhil = n_thread;
					break;
				}

				else if (A[pos] < num) //Comparamos si el numero en la posicion en el arrego es menor al numero, e incrementar el rango menor
					low = pos + 1;

				else
					high = pos - 1; //Si no se cumple lo anterior, se decrementa el rango mayor
			}
			if (band == 0)
				printf("\n\tSoy el thread %d\t y no encontre el numero %d", n_thread, num);
		}
	}
	printf("\n\tSoy el thread %d\t y me despido perros", n_thread);
}