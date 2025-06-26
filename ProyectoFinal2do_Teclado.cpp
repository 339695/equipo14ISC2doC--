#include <iostream>
#include <cstring>
using namespace std;

typedef FILE* file;

const int MAX_LEN = 1000; // tamaño maximo

// estructura para almacenar línea original y línea procesada
struct RegistroLinea {
    char* original;   // linea original
    char* procesado;  // linea despues de simular las teclas
};

union Longitud{
	int longitud;
};



RegistroLinea procesarLinea(char* lineaOriginal); // prototipo
void procesarArchivo(file entrada, file salida); // prototipo

int main() {
    file arEntrada = fopen("entrada.txt", "r"); // abrir archivo para la lectura
    file arSalida = fopen("salida.txt", "w");   // abrir archivo para escribir el resultado

    if (!arEntrada || !arSalida) { // verificar si los archivos se abrieron correctamente 
        cout << "Error al abrir los archivos" << endl;
        return 1;
    }

    procesarArchivo(arEntrada, arSalida); // llamar funcion

    fclose(arEntrada); // cerrar los archivos
    fclose(arSalida);

    return 0;
}

void procesarArchivo(file entrada, file salida) {
    char* buffer = new char[MAX_LEN]; // buffer dinamico para leer cada linea

    while (fgets(buffer, MAX_LEN, entrada)) { 
        buffer[strcspn(buffer, "\n")] = '\0'; // elimina el salto de linea si es que hay

        RegistroLinea registro = procesarLinea(buffer); // procesar linea con estructura

        cout << registro.procesado << endl; // mostrar en consola (solo resultado final)

        fprintf(salida, "%s\n", registro.procesado); // escribir en el archivo del resultado

        delete[] registro.original; // liberar memoria de la linea original
        delete[] registro.procesado; // liberar memoria del resultado
    }

    delete[] buffer; // liberar memoria del buffer
}

RegistroLinea procesarLinea(char* lineaOriginal) {
    // Copiar línea original a memoria dinamica
    char* original = new char[strlen(lineaOriginal) + 1]; 
    strcpy(original, lineaOriginal); // copiar cadena original

    char* resultado = new char[MAX_LEN]; // definir vector resultado
    resultado[0] = '\0';

    Longitud longi;  // longitud del texto actual  
    longi.longitud = 0;
    int cursor = 0;    // posicion actual del cursor

    for (int i = 0; lineaOriginal[i] != '\0'; i++) { // ciclo que recorre la cadena 
        char c = lineaOriginal[i]; // caracter actual

        if (c == '-') { // simulacion de la tecla "-" 
            cursor = 0;
        } else if (c == '+') { // simulacion de la tecla "+"
            cursor = longi.longitud;
        } else if (c == '*') { // simulacion de la tecla "*"
            if (cursor < longi.longitud) cursor++; // cursor a la derecha
        } else if (c == '3') { // simulacion de la tecla "3" suprimir
            if (cursor < longi.longitud) {
                for (int j = cursor; j < longi.longitud - 1; j++) { // mover los caracteres a la izquierda
                    resultado[j] = resultado[j + 1]; 
                }
                longi.longitud--; // disminuir la longitud
                resultado[longi.longitud] = '\0'; // asignar el ultimo valor como nulo
            }
        } else {
            for (int j = longi.longitud; j > cursor; j--) { // mover los caracteres a la derecha
                resultado[j] = resultado[j - 1];
            }
            resultado[cursor] = c; // insertar el caracter
            cursor++;
            longi.longitud++; // aumentar la longitud
            resultado[longi.longitud] = '\0'; // ultimo valor nulo
        }
    }

    RegistroLinea reg; // crear estructura
    reg.original = original; // asignar linea original
    reg.procesado = resultado; // asignar resultado procesado

    return reg; // retornar la estructura
}

