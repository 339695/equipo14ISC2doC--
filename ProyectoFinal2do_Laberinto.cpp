#include <iostream>
#include <time.h> // Para numeros random
#include <string.h> // Para validaciones

using namespace std;

// Estructura usada para definir las filas y columnas
struct Posicion{
    int fila;
    int columna;
};

// Union usada para definir la suma
union Datos{
    int sumaTotal;
};

// Variables globales 
int reng, colu;
Posicion ultimaPos = {-1, -1}; // inicializar struct
int chacales = 0; // contador de chacales

// Prototipos
int** llenar();
void mostrar(int **mat);
int sumaDiagonal(int **mat);
int sumaColumna(int **mat);
void liberar(int **mat);
bool dimension();
void grabarArchivo(); // Grabar en el archivo
void imprimirArchivo(int **mat, int sumTot); // Imprimir en el archivo
bool** marcarCelda(int **mat);

// Main
int main(){
    int sumTot=0, sumTot2 = 0, sumFin=0;
    bool admitido; // Variable que guarda si es que se admitio la captura de datos

    srand(time(NULL)); // semilla del rand

    admitido = dimension(); // Pedir el tamaño al usuario
    
    int **mat = llenar(); // Llenar la matriz

    if(admitido){
        mostrar(mat); // Mostrar la matriz

        sumTot = sumaDiagonal(mat); // Sumar y buscar chacales (proceso general)
        sumTot2 = sumaColumna(mat); // Sumar y buscar chacales (proceso general)

        sumFin = sumTot + sumTot2;
        cout << "Suma total: " << sumFin<< endl;

        // Mostrar si es que se llego al limite de chacales
        if(ultimaPos.fila != -1 && ultimaPos.columna != -1){
            cout << "Ultima posicion antes de detenerse:" << endl;
            cout << "Renglon: " << ultimaPos.fila << "\tColumna: " << ultimaPos.columna << endl;
        }

        // Imprimir en el archivo
        imprimirArchivo(mat, sumFin);
    }
    

    liberar(mat); // Liberar la memoria

    return 0;
}

// Funcion para llenar la matriz dinamica
int **llenar(){
    int **aux = new int*[reng];
    for(int i=0; i<reng; ++i){
        (*(aux + i)) = new int[colu]; // Dinamicas con new
    }

    // Llenado de la matriz con numeros random con ayuda de un ciclo for
    for(int i=0; i<reng; i++){
        for(int j = 0; j < colu; j++){
            (*(*(aux + i) + j)) = rand() % 10; // numeros random
        }
    }

    return aux; // Retornar la matriz llena
}

// Mostrar contenido de la matriz
void mostrar(int **mat){
    bool **marcada = marcarCelda(mat);

    for(int i = 0; i < reng; i++){

        if(reng == 15) cout << "\t\t";
        else cout << "\t\t\t\t";
        for(int j = 0; j < colu; j++){
            if(marcada[i][j]){
                // Color de fondo azul y texto blanco
                cout << "\033[1;37;44m" << mat[i][j] << "\033[0m\t";
            }else{
                cout << mat[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;

    // Liberar memoria usada por la matriz marcada
    for(int i = 0; i < reng; i++) delete[] marcada[i];
    delete[] marcada;
    marcada = nullptr;
}

// Funcion para definir el tamaño de la matriz usada
bool dimension(){
    grabarArchivo();
    FILE *archivo; // Declarar el archivo
    

    // Abre el archivo en modo lectura
    archivo = fopen("archBase.txt", "r");

    // Verificar que el archivo se haya creado correctamente
    if(!archivo){
        cout << "Error de apertura" << endl;
        return -1;
    }

    // Lee la primera fila y almacena el valor en REN
    fscanf(archivo, "%d", &reng);

    // Lee la segunda fila y almacena el valor en TAM2
    fscanf(archivo, "%d", &colu);

    // Verificar que la matriz sea cuadrada
    if(reng != colu){
        cout << "Error, la matriz debe ser cuadrada (REN y COL deben ser iguales)" << endl;
        return false;
    }

    // Crear un limite de minimo y maximo
    if(reng < 5 || reng > 15 || colu < 5 || colu > 15){
        cout << "Error, valores fuera de rango (minimo 5, maximo 15)" << endl << endl;
        return false;
    }

    // Cierra el archivo
    fclose(archivo);

    return true;
}

int sumaDiagonal(int **mat){
    Datos sumTot; // Variable de tipo Datos para almacenar la suma total
    sumTot.sumaTotal = 0; // Inicializar en 0 el acomulador
    chacales = 0; // Reiniciar el contador de ceros

    // Sumar la diagonal principal y contar chacales
    for(int i=0; i<reng; ++i){
        if((*(*(mat + i) + i)) == 0) chacales++; // Aumentar el contador de chacales

        if(chacales == 3){
            ultimaPos.fila = i; // REN
            ultimaPos.columna = i; // COL
            break;
        }
        sumTot.sumaTotal += (*(*(mat + i) + i)); // Sumar en el acomulador
    }

    return sumTot.sumaTotal;
}

int sumaColumna(int **mat){
    Datos sumTot2;
    sumTot2.sumaTotal = 0; // Definir en 0 el acomulador

    if(chacales < 3){
        for(int i = colu-2; i>=0; i--){  // Recorre de abajo hacia arriba
            if((*(*(mat + i) + colu - 1)) == 0) chacales++; // Aumentar el contador de chacales
            else{
                if(chacales == 3){
                    ultimaPos.fila = i+1; // REN
                    ultimaPos.columna = colu - 1; // COL
                    break;
                }
                sumTot2.sumaTotal += *(*(mat + i) + colu - 1);  // Sumar
            }
        }
    }
    // Mostrar chacales
    cout << "Chacales encontrados: " << chacales << endl;

    return sumTot2.sumaTotal;
}

// Funcion para liberar la memoria dinamica
void liberar(int **mat){
    for(int i = 0; i < reng; i++){
        delete[] (*(mat +i));
    }
    delete[] mat;
    mat = nullptr;
}

// Funcion para grabar los renglones y columnas en el archivo
void grabarArchivo(){
    FILE *archivo;
    char entrada[3];
    int ren, col;

    archivo = fopen("archBase.txt", "w");
    if(archivo == NULL){
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    // Pedir renglones
    cout << "Numero de renglones (min 5, max 15): ";
    cin >> entrada;

    // Verificar que se ingrese solamente enteros y positivos
    for(int i=0; (*(entrada + i))!='\0'; i++){
        if(!isdigit((*(entrada + i)))){
            cout << "Entrada invalida, solo se permiten enteros positivos" << endl;
            fclose(archivo);
            return;
        }
    }
    ren = atoi(entrada); // Convertir a entero
    fprintf(archivo, "%d\n", ren); // grabar en el archivo

    // Pedir columnas
    cout << "Numero de columnas (min 5, max 15): ";
    cin >> entrada;

    // Verificar que se ingrese solamente enteros y positivos
    for(int i=0; (*(entrada + i))!='\0'; i++){
        if(!isdigit((*(entrada + i)))){
            cout << "Entrada invalida, solo se permiten enteros positivos" << endl;
            fclose(archivo);
            return;
        }
    }
    col = atoi(entrada); // Convertir a entero
    fprintf(archivo, "%d\n", col); // grabar en el archivo

    fclose(archivo); // cerrar archivo
}

// imprimir la salida en el archivo
void imprimirArchivo(int **mat, int sumTot){
    FILE *archivo;  //variable para manejar el archivo

    // Abrir archivo
	archivo = fopen("archBase.txt","w"); // Write para sobreescribir y reutilizar el mismo archivo 
    fprintf(archivo,"\nNumero de renglones: %d", reng);
    fprintf(archivo,"\nNumero de columnas: %d\n", colu);

    // Grabar la matriz en el archivo
    for(int i=0; i<reng; i++){
        for(int j=0; j<colu; j++){
            fprintf(archivo, "%d\t",(*(*(mat + i) + j)));
        }
        fprintf(archivo,"\n");
    }

    fprintf(archivo,"\nChacales encontrados: %d",chacales); // Grabar los chacales

    fprintf(archivo,"\nSuma total: %d",sumTot); // Grabar la suma final

    // Si es que se llego a un limite de chacales mostramos la posicion en donde se termino de sumar
    if(ultimaPos.fila != -1 && ultimaPos.columna != -1){
        fprintf(archivo,"\nUltima posicion antes de detenerse:\nRenglon: %d \t Columna: %d",ultimaPos.fila, ultimaPos.columna);
    }

	// Cerrar archivo 
	fclose(archivo);
}


// Funcion auxiliar para saber que posiciones marcar
bool** marcarCelda(int **mat){
    bool** marcada = new bool*[reng];
    for(int i = 0; i < reng; ++i) marcada[i] = new bool[colu](); // Inicializa en false

    int chacalesTemp = 0;

    // Recorrido por la diagonal principal
    for(int i = 0; i < reng; ++i){
        if(mat[i][i] == 0){
            chacalesTemp++;
            if(chacalesTemp == 3) break; // No marcar el tercer chacal
        }else{
            marcada[i][i] = true;
        }
    }

    // Recorrido por la ultima columna (excepto esquina inferior derecha)
    if(chacalesTemp < 3){
        for(int i = colu - 2; i >= 0; --i){
            if(mat[i][colu - 1] == 0){
                chacalesTemp++;
                if(chacalesTemp == 3) break; // No marcar el tercer chacal
            }else{
                marcada[i][colu - 1] = true;
            }
        }
    }

    return marcada;
}
