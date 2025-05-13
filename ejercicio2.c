/*
 * Inicio
 * 	Abrir el archivo de texto en modo "r"
 * 	Si el archivo no abre
 * 		Imprimir mensaje de error
 * 		Retornar a 1
 *
 * 	Definir las variables a utilizar
 * 	
 * 	Bucle para recorrer palabra por palabra dentro del archivo
 *
 * 		Leer palabra en el archivo
 *
 * 		Convertir la palabra a minisculas (usando "tolower")
 *
 * 		Eliminar los caracteres no alfanuméricos (utilizar "isalnum")
 *
 * 		Verificar si es una palabra palíndromo
 * 			Encontrar y contar la longitud de la palabra
 * 			Bucle i de 0 a i < len / 2 agregar i++
 * 				Si palabra[i] != palabra[len -1 - i]
 * 				Retornar a 0, sino es así
 * 				Retornar a 1
 *
 * 	Recolocar memoria de las arrays de las palabras palindromos
 * 	Reservar memoria con malloc para la copia
 *	Verificar si el palindromo encontrado es el más largo
 *	Cerrar el archivo
 *
 *	Si se encuentra el palindromo
 *		Imprimir 
 *	Sino
 *		Mostrar un mensaje de error
 *
 *	Liberar la memoria de la palabra 
 *Fin
 */

#include <stdio.h>
#include <stdlib.h> //librería para malloc, realloc 
#include <string.h> //librería para las funciones que incluyen cadenas
#include <ctype.h> //librería para usar tolower e isalnum

#define MAX_len 100 

//se convierten todas las palabras en formato de minúsculas
void convertir_minusculas(char *palabra) {
	for (int i = 0; palabra[i]; i++) {
		palabra[i] = tolower((unsigned char)palabra[i]); //se usa para que hacerlas pequeñas es decir minúsculas 
	}
}

//se eliminan todos los caracteres que no sean letras ni números de las palabras
void eliminar_caracteres(char *palabra) {
	int j = 0;
	char temp[MAX_len];
	for (int i = 0; palabra[i]; i++) {
		if (isalnum((unsigned char)palabra[i])) { //se verifica que sea un caracter alfanumérico
			temp[j++] = palabra[i];
		}
	}
	temp[j] = '\0';  //dejamos la cadena en 0 es decir limpia
	strcpy(palabra, temp);
}

//aquí comprobamos que hayan palabras que sean palíndromo
int es_palindromo(const char *palabra) { //const char se usa para no alterar, porque lo apunta el puntero
	int len = strlen(palabra);
	for (int i = 0; i < len / 2; i++) {
		if (palabra[i] != palabra[len - 1 - i]) {
			return 0; //si es un palíndromo
		}
	}
	return 1; //no es un palíndromo
}

int main() {
	FILE *archivo = fopen("texto.txt", "r"); //llamamos al archivo y lo abrimos
	if (!archivo) { //si es diferente al que llamamos
		perror("No se puede ingresar al archivo"); //mensaje de error y volver a empezar
		return 1;
	}

	char palabra[MAX_len];      
	char **palindromos = NULL;  //puntero dinámico para las palabras
	int total = 0;              //número de palindromos que podemos hallar
	int capacidad = 0;          //capacidad del arreglo palabra[]
	char *mas_largo = NULL;     //apuntamos al palindromo más largo que se encuentra

	//se lee cada palabra del archivo, por palabra
	while (fscanf(archivo, "%99s", palabra) == 1) { //leemos todo los caracteres dejando espacio al caracter nulo "\0"
		convertir_minusculas(palabra); //se convierte a minusculas
		eliminar_caracteres(palabra); //se eliminan los signos y simbolos

		//si dentro del arreglo ya está lleno, se amplia la capacidad
		if (strlen(palabra) > 0 && es_palindromo(palabra)) {
			if (total == capacidad) {
				capacidad = (capacidad == 0) ? 10 : capacidad * 2;
				char **tmp = realloc(palindromos, capacidad * sizeof(char *));
				if (!tmp) {
					perror("Error al reasingar la memoria");
					exit(1);
				}
			 	palindromos = tmp;
			}

			//se reserva la memoria para la nueva palabra y copiarla
			palindromos[total] = malloc(strlen(palabra) + 1);
			if (!palindromos[total]) {
				perror("Error al reservar memoria de la palabra");
				exit(1);
			}
			strcpy(palindromos[total], palabra);

			//actualizamos el palindromo que se encontro, y verificar si es el más largo
			if (!mas_largo || strlen(palindromos[total]) > strlen(mas_largo)) {
				mas_largo = palindromos[total];
			}

			total++; //si es el caso, se aumentan la cantidad guardados
		}
	}

	fclose(archivo); //cerramos el archivo

	//se imprime y mostramos los resultados, siempre y cuando total sea mayor que 0
	if (total > 0) {
		printf("El palíndromo más largo es: %s (longitud %lu)\n\n", mas_largo, strlen(mas_largo));
	} else {
		printf("No se encontró ninguna palabra palíndroma.\n");
	}

	//se libera toda la memoria reservada con anterioridad
	for (int i = 0; i < total; i++) {
		free(palindromos[i]); //liberamos las palabras
	}
	free(palindromos); //y el arreglo de punteros

	return 0;
}
