//incluir funciones recursivas
//incluir enumeracion
//variables y funciones con nombre que tengan que ver
//conmentar D:

#include <iostream>
using namespace std;
enum Orientacion {VERTICAL, HORIZONTAL};
bool colocarPalabra (char**, int, int, Orientacion, char*);
bool estaVacio (char**);
bool esPalabra(char*);
void imprimir(char**);

int main(){
    char **tablero;
    tablero = new char*[9];
    for(int i=0; i<9; i++){
        tablero[i]=new char[9];
    }
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            *(*(tablero+i)+j)=' ';
        }
    }
    imprimir(tablero);
    estaVacio(tablero);
    return 0;
}

bool estaVacio(char **tablero){
    for(int i=0;i<9;i++){
        for(int j=0; j<9; j++){
            if(*(*(tablero+i)+j)!=0){
                return false;
            }
        }
    }
    return true;
}

void imprimir(char **tablero){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout<<tablero[i][j]<<"a \t";
        }
        cout<<endl;
    }

}