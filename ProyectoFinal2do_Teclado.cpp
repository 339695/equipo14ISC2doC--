#include <iostream>
#include <cstring>
using namespace std;
typedef FILE* file;

void procesarLineas(file entrada, file salida);

int main() {
    file arEntrada = fopen("entrada.txt","r"); // abrir archivo para la lectura
    file arSalida = fopen("salida.txt", "w"); // abrir archivo para escribir el resultado
    
    if(!arEntrada || !arSalida){ // verificar si los archivos se abrieron correctamente 
    	cout<<"Error al abrir los archivos"<<endl;
    	return 1;
	}

   procesarLineas(arEntrada, arSalida); // llamar funcion
   
   fclose(arEntrada); // cerrar los archivos
   fclose(arSalida);

    return 0;
}

void procesarLineas(file entrada, file salida){
	const int MAX_LEN = 1000; // tamañoo maximo
    char entradaLinea[MAX_LEN]; // vector de entrada

    while (fgets(entradaLinea, MAX_LEN, entrada)) { 
        entradaLinea[strcspn(entradaLinea, "\n")]='\0'; // elimina el salto de linea si es que hay

		
		
        char resultado[MAX_LEN] = {}; // definir vector resultado
        int longitud = 0;  
        int cursor = 0;    

        for (int i = 0; entradaLinea[i] != '\0'; i++) { // ciclo que recorre la cadena 
            char c = entradaLinea[i]; // caracter acutal

            if (c == '-') { // simulacion de la tecla "-" 
                cursor = 0;
            } else if (c == '+') { // simulacion de la tecla "+"
                cursor = longitud;
            } else if (c == '*') { // simulacion de la tecla "*"
                if (cursor < longitud) cursor++; // cursor a la derecha
            } else if (c == '3') { // simulacion de la tecla "3" suprimir
                if (cursor < longitud) {
                  for (int j = cursor; j < longitud - 1; j++) { // mover los caracteres izquierda
                        resultado[j] = resultado[j + 1]; 
                    }
                    longitud--; // disminuir la longitud
                    resultado[longitud] = '\0'; // asignar el ultimo valor como nulo
                }
            } else {
                for (int j = longitud; j > cursor; j--) { // mover los caracteres a la derecha
                    resultado[j] = resultado[j - 1];
                }
                resultado[cursor] = c; // insertar el caracter
                cursor++;
                longitud++; // aumentar la longitud
                resultado[longitud] = '\0'; //ultimo valor nulo
            }
        }

        printf("%s\n", resultado); // mostrar en consola
        fprintf(salida, "%s\n", resultado); // escribir en el archivo del resultado
    }
}
