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
bool cabe(char*,int,int,Orientacion);
void menu();

int main(){
    menu();
    return 0;
}

void menu(){
    int opc=0;
    Orientacion orient;
    char **tablero;
    char *palabra;
    int x=0,y=0;
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
        cout<<"2. imprimir"<<endl;
        cout<<"3. salir"<<endl;
        cout<<"elige una opcion: ";
        cin>>opc;
        switch(opc){
        case 1:
            cout<<"ingresa la palabra que quieres insertar: ";
            cin>>palabra;
            if(esPalabra(palabra)){
                orientacionSelect(orient);
                if(estaVacio(tablero)){
                    if(colocarPalabra(tablero, 5, 5, orient, palabra)){
                        cout<<"palabra insertada correctamente"<<endl;
                    }
                    else{
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }
                    imprimir(tablero);
                }
                else{
                    cout<<"en que posición de x quieres colocar tu palabra? ";
                    cin>>x;
                    cout<<"en que posición de y quieres colocar tu palabra? ";
                    cin>>x;
                    if(colocarPalabra(tablero, y, x, orient, palabra)){
                        cout<<"palabra insertada correctamente"<<endl;
                    }
                    else{
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }
                }

            }
            else{
                cout<<"palabra no encontrada en el diccionario"<<endl;
            }
            break;
        
        case 2:
            imprimir(tablero);
            break;
        case 3:
            cout<<"saliendo"<<endl;
        default:
            cout<<"valores invalidos"<<endl;
            break;
        }
    }
    while(opc!=3);

    imprimir(tablero);
    estaVacio(tablero);
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
    cin>>o;
    do{
        switch(o){
        case 0:
            orientacion=VERTICAL;
            val=true;
            break;
        case 1:
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
    }
    return false; 
}

bool colocarPalabra(char** tablero, int filas, int columnas, Orientacion ori, char *palabra){
    if(cabe(palabra,filas,columnas,ori)){    
        if(ori==0){
            for(int i=0;i<9;i++){
                tablero[columnas][i]=palabra[i];
            }
            return true;
        }
        else{
            for(unsigned int i=columnas;i<=strlen(palabra);i++){
                tablero[i][filas]=palabra[i];
            }
            return true;
        }
    }
    cout<<"no cabe la palabra en el tablero"<<endl;
    return false;
}

bool cabe(char* palabra,int fila, int columna, Orientacion ori){
    if(ori==0){
        if(fila+strlen(palabra)>9){
            return false;
        }
        else{
            return true;
        }
    }
    if(ori==1){
        if(columna+strlen(palabra)>9){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}