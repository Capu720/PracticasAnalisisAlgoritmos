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
typedef struct 
{
    int inicio;
    int fin;
    int buscar;

}parametros;

//Esqueletos de la funcion
int BusquedaExponencial(int, int, int);
void *Hilo(void *datos);

//Variables globales
int numHilos = 10, fg = 0;
int *numeros;

int main(int argc, char const *argv[])
{
	int i, buscar,n;

    parametros param[numHilos];
    pthread_t thread[numHilos];

	//Verifica que se ingrese la longitud n de numeros
    if (argc != 3)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }
    //convierte la cadena a numero
    n = atoi(argv[1]);
    buscar = atoi(argv[2]);

    //Se crea el arreglo para los numeros
	numeros = (int *)malloc(sizeof(int) * n);
	
	//Metiendo numeros al arreglo
	for (i = 0; i < n; i++)
		scanf("%d", &numeros[i]);

    //DEclaramos los rangos de busqeuda
    int intervalo = n/numHilos;
    int inicio = 0;
    int fin = intervalo-1;

    //Se van creando los hilos y sus respectivos argumentos
    for(i = 0; i<numHilos; i++)
    {
        param[i].fin = fin;
        param[i].inicio = inicio;
        param[i].buscar = buscar;
        //Preguntamos si se encontro
        

        /*Se crea el un hilo pasando como parametro la estructura y ligado a la funcion Hilo*/
        if (pthread_create (&thread[i], NULL, Hilo,(void*)&param[i]) != 0 )
        {
            perror("El thread no  pudo crearse");
            exit(-1);
        }
        /*Se actualiza el rango de busqueda para el siguiente Hilo*/
        inicio = fin + 1;
        fin += intervalo;  
        
    }

    for(i = 0; i<numHilos; i++)
        pthread_join(thread[i], NULL);
    
    printf("\n\n");
    free(numeros);
    return EXIT_SUCCESS;
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
 *  - La posicion final, el numero a buscar, y el inicio del rango
 * Regresa:
 *  - int
 * Errores: ninguno
*/

int BusquedaExponencial(int n, int num, int ini)
{
	int i;

    //Primero checamos si el primer elemento del arreglo es el que buscamos
	if(numeros[ini] == num)
        return ini;
    
        
	int pos = ini+1; //Declaramos una variable para acceder a la posicion del arreglo

	/*Se realiza un ciclo while donde el elemento a buscar debe de estar presente. Compara si la posicion es menor
	al tamanio del arreglo y si el numero que esta en el arreglo menor o igual al numero a buscar*/

	while (pos < n && numeros[pos] <= num)
		pos = pos * 2;

    /*Declaramos los primeros valores de los rangos*/
	int low = pos / 2;
	int high = min(pos, n);
	while (low <= high)
	{   
		pos = low + (high - low) / 2;
    
        if (numeros[pos] == num)// Si encontramos el numero en la posicion del arreglo, regresamos la posicion
            return pos;      
    
		else if (numeros[pos] < num) //Comparamos si el numero en la posicion en el arrego es menor al numero, e incrementar el rango menor
			low = pos + 1;

		else
			high = pos - 1; //Si no se cumple lo anterior, se decrementa el rango mayor
	}
    //Si no esta regresa -1
    return -1;

}

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

void *Hilo(void* datos){
    parametros *param = (parametros*)datos;

    if(fg == 1)
        pthread_exit(NULL);

    /*Se insertan los datos dentro de su rango*/
    //int tamanio = param->fin - param->inicio; 
    int num = param->buscar;

    //Almacenamos el valor devuelto por la funcion de busqueda exponencial
    int resu = BusquedaExponencial(param->fin, param->buscar, param->inicio);

    //Si el resultado es diferente de -1, quiere decir que encontro el resultado
    if(resu != -1)
    {
        printf("\nEl hilo con ID %lu encontro el dato: %d en la posicion %d",pthread_self(),num, resu);
        fg = 1;
    }
    else//Si no, quiere decir que el hilo no lo encontro en su arreglo
        printf("\nEl hilo con ID %lu no encontro el dato: %d",pthread_self(),num);

    pthread_exit(NULL);

}

