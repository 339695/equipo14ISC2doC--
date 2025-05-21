// Teclado 
// Pendiente: entradas y salidas desde archivos .txt
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    const int MAX_LEN = 1000; // tamaño maximo
    char entrada[MAX_LEN]; // cadena de entrada

    while (true) { 
        cout << "Ingresa una línea (Enter para salir): ";
        cin.getline(entrada, MAX_LEN);

        if (strlen(entrada) == 0) break; // fin si se presiona enter

        char resultado[MAX_LEN] = {};
        int longitud = 0;  
        int cursor = 0;    

        for (int i = 0; entrada[i] != '\0'; i++) { // ciclo que recorre la cadena 
            char c = entrada[i]; // caracter acutal

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
                    longitud--; 
                    resultado[longitud] = '\0'; 
                }
            } else {
                for (int j = longitud; j > cursor; j--) { // mover los caracteres a la derecha
                    resultado[j] = resultado[j - 1];
                }
                resultado[cursor] = c; // insertar el caracter
                cursor++;
                longitud++;
                resultado[longitud] = '\0'; 
            }
        }

        cout << "Resultado: " << resultado << endl;
    }

    return 0;
}
