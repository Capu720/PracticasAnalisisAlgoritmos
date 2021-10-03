/*
* Titulo: Practica 2, algoritmo "Busqueda Exponencial"
* Descripcion: Implementacion del algoritmo de busqueda exponencial
* Fecha: 27-sep-2021
* Version: 1.0
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define min

//Esqueleto de la funcion
int BusquedaExponencial(int *, int, int);

int main(int argc, char const *argv[])
{
	int n, i, bandera, num;
	//Verifica que se ingrese la longitud n de numeros
	if (argc != 2)
	{
		printf("Ingrese n");
		exit(EXIT_FAILURE);
	}
	//convierte la cadena a numero
	n = atoi(argv[1]);

	int *A = (int *)malloc(sizeof(int) * n);
	int x[] = {	322486, 14700764, 3128036, 3128036, 6337399,
				61396, 10393545, 2147445644, 1295390003, 450057883,
				187645041, 1980098116, 152503, 5000, 1493283650,
				214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
	//Metiendo numeros al arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	//A[i] = i+1;

	for (i = 0; i < 21; i++)
	{
		num = x[i];
		bandera = BusquedaExponencial(A, n, num);

		if (bandera != -1)
			printf("\nNumero:%d\t encontrado en la posicion: %d", num, bandera);
		else
			printf("\nNumero:%d\t NO encontrado en el arreglo", num);
	}
	return 0;
}

/*
*Funcion de busqueda exponencial
*Descripcion:La siguiente funcion realiza de forma iterativa el algoritmo de busqueda exponencial,
*basicamente consiste en dos pasos, primero verifica si el numero se encuentra en la primera posicion
*del arreglo, si lo encuentra devuelve la posicion 0 del arreglo. En caso contrario, actualiza los rangos
*en potencia de dos hasta hallar un rango que este mas cerca del numero, despues realiza una busqueda
*binaria con los rangos del caso anterior en caso de encontrar el valor, devuelve la posicion donde 
*se encuentra el numero a buscar, en caso contrario regresa -1
* Recibe:
 *  - El arreglo, el tamanio del arreglo, y el numero a buscar
 * Regresa:
 *  - int
 * Errores: ninguno
*/

int BusquedaExponencial(int *A, int n, int num)
{
	//Primero checamos si el primer elemento del arreglo es el que buscamos
	if (A[0] == num)
		return 0;

	int pos = 1; //Declaramos una variable para acceder a la posicion del arreglo

	/*Se realiza un ciclo while donde el elemento a buscar debe de estar presente. Compara si la posicion es menor
	al tamanio del arreglo y si el numero que esta en el arreglo menor o igual al numero a buscar*/

	while (pos < n && A[pos] <= num)
		pos = pos * 2;

	/*Una vez encontrado el rango en donde esta el numero, se realiza una busqueda de forma binaria*/

	/*Declaramos los primeros valores de los rangos*/
	int low = pos / 2;
	int high = min(pos, n - 1);

	while (low <= high)
	{
		pos = low + (high - low) / 2;

		if (A[pos] == num) // Si encontramos el numero en la posicion del arreglo, regresamos la posicion
			return pos;

		else if (A[pos] < num) //Comparamos si el numero en la posicion en el arrego es menor al numero, e incrementar el rango menor
			low = pos + 1;

		else
			high = pos - 1; //Si no se cumple lo anterior, se decrementa el rango mayor
	}

	return -1; //Si no esta regresa -1
}
