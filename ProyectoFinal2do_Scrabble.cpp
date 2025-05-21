//incluir funciones recursivas
//incluir enumeracion
//variables y funciones con nombre que tengan que ver
//conmentar D:

#include <iostream>
#include <string.h>
using namespace std;

char diccionario[10][10]={"manzana", "perro", "cielo", "felicidad", "rio", "espejo", "sol", "libro", "piedra", "flor"};

enum Orientacion {VERTICAL, HORIZONTAL};
bool colocarPalabra (char**, int, int, Orientacion, char*);
bool estaVacio (char**);
bool esPalabra(char*);
void imprimir(char**);
void inicializar(char**);
void orientacionSelect(Orientacion&);

int main(){
    int opc=0;
    Orientacion orient;
    char **tablero;
    char *palabra;
    tablero = new char*[9];
    palabra = new char[9];
    for(int i=0; i<9; i++){
        tablero[i]=new char[9];
    }
    inicializar(tablero);
    imprimir(tablero);
    do{
        cout<<"menu"<<endl;
        cout<<"1. colocar palabra nueva"<<endl;
        cout<<"3. salir"<<endl;
        cout<<"elige una opcion: ";
        cin>>opc;
        switch(opc){
        case 1:
            if(estaVacio(tablero) && esPalabra(palabra)){
                orientacionSelect(orient);
                colocarPalabra(tablero, 5, 5, orient, palabra);
            }
            else{
                cout<<"valores invalidos";
            }
            break;
        
        default:
            break;
        }
    }
    while(opc!=3);

    imprimir(tablero);
    estaVacio(tablero);
    return 0;
}

bool estaVacio(char **tablero){
    for(int i=0;i<9;i++){
        for(int j=0; j<9; j++){
            if(*(*(tablero+i)+j)!=' '){
                return false;
            }
        }
    }
    return true;
}

void imprimir(char **tablero){
    for(int i = 0; i < 9; i++){
        cout<<"|";
        for(int j = 0; j < 9; j++){
            cout<<tablero[i][j]<<"|";
        }
        cout<<endl;
    }

}

void inicializar(char **tablero){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            *(*(tablero+i)+j)=' ';
        }
    }
}

void orientacionSelect(Orientacion &orientacion){
    int o=0;
    bool val=false;
    cout<<"en que orientacion quieres colocar tu palabra(1 para vertical/ 0 para horizontal ): ";
    do{
        switch(o){
        case 1:
            orientacion=VERTICAL;
            val=true;
            break;
        case 0:
            orientacion=HORIZONTAL;
            val=true;
            break; 
        default:
            cout<<"valor fuera de limites";    
            break;
        }
    }while(val!=true);
    
}

bool esPalabra(char* palabra){
    for(int i=0; i<10; i++){
        if(strcmp(palabra,diccionario[i])==0){
            return true;
        }
        else{
            return false;
        }
    }
    return false; 
}

bool colocarPalabra (char** tablero, int filas, int columnas, Orientacion ori, char *palabra){
        
    return false;
}
