#include<stdio.h>
#include<stdlib.h>

/*
 * Titulo: Practica 1, algoritmo "Ordenamiento por ABB"
 * Descripción: implementacion del algoritmo ABB
 * Fecha: 13-sep-2021
 * Versión: 1
*/

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*posicion en arreglo*/
#define BANDERA int  /*bandera de estado de algoritmo*/

/*
 * Función: Se realiza el ordenamiento de un arreglo por el metodo de algoritmo Shell
 * Descripcion: Se realiza el ordenamiento del arreglo de longitud "n" con el algoritmo Shell, el cual consiste en la creacion de sub-arreglos de tamaño k = n/2. Se realiza la comparacion de los elementos de cada sub-arreglo, si el sub arreglo con posicion mas cercano al valor n es menor que el elemento mas cercano al 0, se realiza un intercambio de valores. Una vez ordenado el sub-arreglo, se divide k entre 2 nuevamente. El proceso se realiza hasta que k <= 1.
 * Recibe:
 *  - Arreglo de tipo entero
 *  - Valor entero del tamaño del arreglo
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Shell(TIPO *numeros, TIPO n);

int main(int argc, char* argv[])
{
	TIPO n;
	
    /*Verifica que se ingrese la longitud n de numeros*/
	if (argc!=2) 
	{
		printf("\n Se debe de indicar el tamano de algoritmo");
		exit(1);
	} 
	else
	{
        /*convierte la cadena a numero*/
		n=atoi(argv[1]);
	}

	/*Solicita memoria al sistema con la funcion malloc*/
	TIPO *numeros;
	numeros = malloc(n * sizeof(TIPO));
		
	/*Lee y almacena los n numeros en el arreglo creado*/
	for(int i = 0; i < n; i++)
        scanf(FORMATO,&numeros[i]);

    /*Se realiza llama a la funcion que realiza el algoritmo Shell*/
	Shell(numeros,n);

    /*Se imprime el arreglo ordenado*/
	printf("Arreglo en orden: \n");
    for(int i = 0; i < n; i++)
		printf("%d\n",numeros[i]);

    /*Se libera la memoria*/
    free(numeros);

	return 0;
}

void Shell(TIPO *numeros, TIPO n)
{
    /*Variable para iteraciones*/
	POSICION i;
    /*Variable para dimension de sub-arreglos*/
    POSICION k;
    /*Variable temporal para el intercambio de valores*/
    TIPO temporal;
    /*Variable bandera que indica si el subarreglo realizo un intercambio*/
    BANDERA b;

    /*Se realiza la division del arreglo en sub arreglos de n/2 de longitud*/
	k = (n/2);

    /*Se realiza un ciclo que su ultimo caso es el ordenamiento de arreglos
     de longitud 1*/
	while(k >= 1)
	{
        /*Se asigna el valor 1 a la bandera para forzar la entrada al while*/
		b = 1;
        /*Se ejecuta el while mientras que b sea diferente de 0
         indicando que el arreglo realizo un intercambio de valores,
         por lo cual requiere revisar si se mantiene ordenado*/
		while(b != 0)
		{
            /*Se asigna el valor 0 a b indicando que no se ha realizado un intercambio*/
			b = 0;
            /*Se hace un recorrido desde el valor k al valor n-1 con incrementos de una unidad*/
			for(i = k; i <= n - 1; i++)
			{
                /*Si compara si el valor del arreglo en la posicion i-k es mayor que
                 el valor en la posicion i, esto se debe a que los valores en la posicion i deben ser mayores a los que estan más cerca del 0*/
				if(numeros[i - k] > numeros[i])
				{
                    /*Si la condicion se cumple se debe realizar un intercambio de valores*/
					temporal = numeros[i];
					numeros[i] = numeros[i - k];
					numeros[i - k] = temporal;
                    /*Se incrementa en uno la bandera, indicando que re ha realizado un intercambio*/
					b = b + 1;
				}
			}
		}
		/*Al finalizar el analisis de los sub arreglos, se divide nuevamente entre 2, generando sub-arreglos de menor dimension en cada ciclo*/
		k = (k/2);
	}
}
