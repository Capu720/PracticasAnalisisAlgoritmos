#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define min 

//Esqueleto de la funcion
int BusquedaExponencial(int *, int , int);

int main(int argc, char const *argv[])
{
	int n,i;
	/*Verifica que se ingrese la longitud n de numeros*/
    if (argc != 2)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }
    /*convierte la cadena a numero*/
    n = atoi(argv[1]);
    
    int *A = (int *)malloc(sizeof(int) * n);
    int num = 8;
    
    //Metiendo numeros al arreglo
    for(i = 0; i < n; i++)
    	scanf("%d", &A[i]);
    
    int bandera = BusquedaExponencial(A,n,num);
    
    if(bandera != -1)
    	printf("\nNumero encontrado en la posicion: %d", bandera);
    else
    	printf("\nNumero NO encontrado en el arreglo");
    
	return 0;	
}


/*Funcion de busqueda eponencial
Recibe como parametros un arreglo, el tamanio del arreglo, y el numero a buscar
La siguiente funcion realiza de forma iterativa el algoritmo de busqueda exponencial
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
	
	return -1;
	
}
