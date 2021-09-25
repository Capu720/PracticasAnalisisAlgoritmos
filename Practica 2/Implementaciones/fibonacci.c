#include <stdio.h>
#include <windows.h> //si se usa en windows
#include <stdlib.h>

#define TIPO int     /*tipo de datos que se ingresaran*/
#define FORMATO "%d" /*formato de datos que se ingresaran*/
#define POSICION int /*Significado del los nombres primero, medio y final*/

#define ESTA(pos)  (pos!=-1)
/**
 * Titulo: Practica 2, algoritmo "Busqueda de Fibonacci"
 * Descripción: implementacion del algoritmo de busqueda de Fibonacci
 * Fecha: 27-sep-2021
 * Versión: 1
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
    if (fibM1 && arr[inicio + 1] == buscar){
        return inicio + 1;
    }

    /*como no lo encontró, regresa -1 */
    return -1;
}

int main(int argc, char const *argv[])
{
    TIPO n,buscar, *numeros;
    POSICION i, pos;
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
    pos=fibMonaccianSearch(numeros,buscar,n);

    /*se verifica si se encontro el numero*/
    ESTA(pos) ? printf("Se encuentra en la posicion: %d\n",pos): printf("no se encuentra");
    /*se libera la memoria*/
    free(numeros);
    return EXIT_SUCCESS;
}
