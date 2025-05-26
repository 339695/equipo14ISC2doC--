#include <iostream>
#include <time.h>

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
int REN, COL;
Posicion ultimaPos = {-1, -1}; // inicializar union
int chacales = 0; // contador de chacales

// Prototipos
int** llenar();
void mostrar(int **mat);
int suma(int **mat);
int suma2(int **mat);
void liberar(int **mat);
bool dimension();
void grabar(); // Grabar en el archivo
void imprimir(int **mat, int sumTot); // Imprimir en el archivo

// Main
int main(){
    int sumTot=0, sumTot2 = 0, sumFin=0;
    bool a; // Variable que guarda si es que se admitio la captura de datos

    srand(time(NULL)); // semilla del rand

    a=dimension(); // Pedir el tamaño al usuario
    
    int **mat = llenar(); // Llenar la matriz

    if(a){
        mostrar(mat); // Mostrar la matriz

        sumTot = suma(mat); // Sumar y buscar chacales (proceso general)
        sumTot2 = suma2(mat);

        sumFin = sumTot + sumTot2;
        cout << "Suma total: " << sumFin<< endl;

        // Mostrar si es que se llego al limite de chacales
        if(ultimaPos.fila != -1 && ultimaPos.columna != -1){
            cout << "Ultima posicion antes de detenerse:\n";
            cout << "Renglon: " << ultimaPos.fila << "\tColumna: " << ultimaPos.columna << endl;
        }

        // Imprimir en el archivo
        imprimir(mat, sumFin);
    }
    

    liberar(mat); // Liberar la memoria

    return 0;
}

// Funcion para llenar la matriz dinamica
int **llenar(){
    int **aux = new int*[REN];
    for(int i=0; i<REN; ++i){
        (*(aux + i)) = new int[COL]; // Dinamicas con new
    }

    // Llenado de la matriz con numeros random con ayuda de un ciclo for
    for(int i=0; i<REN; i++){
        for(int j = 0; j < COL; j++){
            (*(*(aux + i) + j)) = rand() % 10; // numeros random
        }
    }

    return aux; // Retornar la matriz llena
}

// Mostrar contenido de la matriz
void mostrar(int **mat){
    for(int i=0; i<REN; i++){
        for(int j=0; j<COL; j++){
            cout << (*(*(mat + i) + j)) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Funcion para definir el tamaño de la matriz usada
bool dimension(){
    grabar();
    FILE *archivo; // Declarar el archivo
    

    // Abre el archivo en modo lectura
    archivo = fopen("tam.txt", "r");

    // Verificar que el archivo se haya creado correctamente
    if(!archivo){
        cout << "Error de apertura" << endl;
        return -1;
    }

    // Lee la primera fila y almacena el valor en REN
    fscanf(archivo, "%d", &REN);

    // Lee la segunda fila y almacena el valor en TAM2
    fscanf(archivo, "%d", &COL);

    // Verificar que la matriz sea cuadrada
    if(REN != COL){
        cout << "Error, la matriz debe ser cuadrada (REN y COL deben ser iguales)" << endl;
        return false;
    }

    // Crear un limite de minimo y maximo
    if(REN < 5 || REN > 15 || COL < 5 || COL > 15){
        cout << "Error, valores fuera de rango (minimo 5, maximo 15)" << endl << endl;
        return false;
    }

    // Cierra el archivo
    fclose(archivo);

    return true;
}

int suma(int **mat){
    Datos sumTot; // Variable de tipo Datos para almacenar la suma total
    sumTot.sumaTotal = 0; // Inicializar en 0 el acomulador
    chacales = 0; // Reiniciar el contador de ceros

    // Sumar la diagonal principal y contar chacales
    for(int i=0; i<REN; ++i){
        if((*(*(mat + i) + i)) == 0){
            chacales++; // Aumentar el contador de chacales
        }
        if(chacales == 3){
            ultimaPos.fila = i; // REN
            ultimaPos.columna = i; // COL
            break;
        }
        sumTot.sumaTotal += (*(*(mat + i) + i)); // Sumar en el acomulador
    }

    return sumTot.sumaTotal;
}

int suma2(int **mat){
    Datos sumTot2;
    sumTot2.sumaTotal = 0; // Definir en 0 el acomulador

    if(chacales < 3){
        for(int i = COL-2; i>=0; i--){  // Recorre de abajo hacia arriba
            if((*(*(mat + i) + COL - 1)) == 0){
                chacales++; // Aumentar el contador de chacales
            }else{
                if(chacales == 3){
                    ultimaPos.fila = i+1; // REN
                    ultimaPos.columna = COL - 1; // COL
                    break;
                }
                sumTot2.sumaTotal += *(*(mat + i) + COL - 1);  // Sumar
            }
        }
    }
    // Mostrar chacales
    cout << "Chacales encontrados: " << chacales << endl;

    return sumTot2.sumaTotal;
}

// Funcion para liberar la memoria dinamica
void liberar(int **mat){
    for(int i = 0; i < REN; i++){
        delete[] (*(mat +i));
    }
    delete[] mat;
}

// Funcion para grabar los renglones y columnas en el archivo
void grabar(){
	FILE *archivo;  //variable para manejar el archivo
	int ren, col; 

    // Abrir archivo
	archivo = fopen("tam.txt","w");

	cout << "Numero de renglones: ";
	cin >> ren;
	fprintf(archivo,"%d\n",ren); // grabar en el archivo

    cout << "Numero de Columnas: ";
    cin >> col;
    fprintf(archivo,"%d\n",col);// grabar en el archivo

	// Cerrar archivo 
	fclose(archivo);
}

// imprimir la salida en el archivo
void imprimir(int **mat, int sumTot){
    FILE *archivo;  //variable para manejar el archivo

    // Abrir archivo
	archivo = fopen("tam.txt","w"); // Write para sobreescribir y reutilizar el mismo archivo 
    fprintf(archivo,"\nNumero de renglones: %d", REN);
    fprintf(archivo,"\nNumero de columnas: %d\n", COL);

    // Grabar la matriz en el archivo
    for(int i=0; i<REN; i++){
        for(int j=0; j<COL; j++){
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
