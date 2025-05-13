/* 
 * Inicio
 * 	Solicitar el tamaño de la matriz (n) por el usuario
 *      Si n no se encuentra entre el limite
 *      Retornar
 *
 *      Crear la matriz cuadrada para encontrar la longitud de 1s más larga
 *      Definir las variables para el recorrido de las diagonales
 *      	Recorrer la matriz fila por fila y columna por columna
 *
 *      Reservar la memoria para una matriz (n x n) 
 *
 *      Llenar la matriz cuadrada con un valor aleatorio entre 0 y 1 (#binarios)
 *     	Definir las variables para llenar la matriz
 *     		Bucle i de 0 a tamaño - 1 realizar
 *     			Bucle j de 0 a tamaño -1 realizar
 *     				matriz[i][j] --> *(*(matriz + 1) + j) # aleatorio 0 y 1
 *     				al usar: rand() % 2
 *      		
 *
 *      Mostrar la secuencia más larga de 1s, se imprime la matriz 
 *
 *      Liberar la memoria asignada para la matriz
 *
 * Fin
 */

#include <stdio.h>
#include <stdlib.h>  //Librería para malloc, rand y free
#include <time.h>   //Librería para el generador de semilla aleatorio

//Función para encontrar la secuencia más larga de 1s
void findLargestLine(int **matrix, int size, int *result) {
	int maxLarge = 0, contador = 0;

	for (int i = 0; i < size; i++) {    //recorremos las filas
		for (int j = 0; j < size; j++) {   //como también las columnas
			if (*(*(matrix + i) + j) == 1) {
				contador++;      //si es 1, se incrementa el conteo
				if (contador > maxLarge) 
					maxLarge = contador;  //en caso de ser necesario se actualiza el máximo
			} else {
				contador = 0; 
			}
		}
	}

	*result = maxLarge;   //guardamos el resultado final 
}

//Función para reserver la memoria dinámica para la matriz
void allocateMatrix(int ***matrix, int size) { 
	*matrix = (int **)malloc(size * sizeof(int *));  //se reserva el arreglo por filas
	for (int i = 0; i < size; i++) {
		(*matrix)[i] = (int *)malloc(size * sizeof(int)); //se reserva columnas por filas
	}
}

//Función para llenar la matriz con valores binarios
void fillMatrix(int **matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			*(*(matrix + i) + j) = rand() % 2; //rand asigna 0 o 1 aleatoriamente
		}
	}
}

//Función para imprimir la matriz cuadrada
void printMatrix(int **matrix, int size) {
	printf("Matriz generada (%dx%d):\n", size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", *(*(matrix + i) + j)); //se imprime cada elemento con la aritmética...
		}
		printf("\n");

	}
}

//Función para liberar la memoria de la matriz
void freeMatrix(int **matrix, int size) {
	for (int i = 0; i < size; i++) {
		free(matrix[i]); //liberamos las filas
	}
	free(matrix);  //se libera también el arreglo de la matriz
}

int main() {
	int size, largestLine;
	int **matrix = NULL;

	printf("Ingrese el tamaño de la matriz (nxn): "); //se le pide el usuario que agregue la dimensión de la matriz
	scanf("%d", &size);

	srand(time(NULL));  //para que la semilla sea aleatoria cada vez que la corramos

	allocateMatrix(&matrix, size); //llamamos la función para que reserve la memoria
	fillMatrix(matrix, size); //y para que llene la matriz
	
	printf("---Matriz generada---\n");
	printMatrix(matrix, size); //se imprime la matriz

	findLargestLine(matrix, size, &largestLine); //se llama la función para encontrar los 1s

	printf("El tamaño de la secuencia de 1s más grande es: %d\n", largestLine); //se muestra el resultado

	freeMatrix(matrix, size); //y se libera la memoria 

	return 0; //se retorna con éxito
}
