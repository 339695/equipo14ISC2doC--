//incluir funciones recursivas
//incluir enumeracion
//variables y funciones con nombre que tengan que ver
//conmentar D:

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

char diccionario[10][10]={"manzana", "perro", "cielo", "felicidad", "rio", "espejo", "sol", "libro", "piedra", "flor"};

enum Orientacion {HORIZONTAL,VERTICAL};
bool conecta(char**, int, int, Orientacion, char*, int&);
bool colocarPalabra (char**, int, int, Orientacion, char*, int&);
bool estaVacio (char**);
bool esPalabra(char*);
void imprimir(char**);
void inicializar(char**);
void orientacionSelect(Orientacion&);
bool cabe(char*,int,int,Orientacion);
void menu();
void puntuacion(int);
bool valid(char*);
bool vacio=true;

int main(){
    cout<<"Scrabble es un juego donde se intenta obtener puntos mediante la construccion de palabras\nEl juego se desarrolla sobre un tablero de 9x9, el cual tiene casillas de premiacion(casillas marcadas con x)\n que multiplican el numero de puntos concedidos"<<endl;
    menu();
    return 0;
}

bool valid(int coso){
    if(coso==97||coso==98||coso==99){
        return true;
    }
    return false;
}

void menu(){
    int puntos=0;
    char opc;
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
        cout<<"a. colocar palabra nueva"<<endl;
        cout<<"b. imprimir"<<endl;
        cout<<"c. terminar intento"<<endl;
        cout<<"elige una opcion: ";
        cin>>opc;
        if(!valid(opc)){
            continue;
        }
        switch(opc){
        case 'a':
            cout<<"ingresa la palabra que quieres insertar: ";
            cin>>palabra;
            if(esPalabra(palabra)){
                orientacionSelect(orient);
                if(estaVacio(tablero)){
                    if(colocarPalabra(tablero, 4, 4, orient, palabra, puntos)){
                        cout<<"palabra insertada correctamente"<<endl;
                        vacio=false;
                    }
                    else{
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }
                    imprimir(tablero);
                }
                else{
                    cout<<"en que posicion de x quieres colocar tu palabra? ";
                    cin>>x;
                    cout<<"en que posicion de y quieres colocar tu palabra? ";
                    cin>>y;
                    if(colocarPalabra(tablero, y, x, orient, palabra, puntos)){
                        cout<<"palabra insertada correctamente"<<endl;
                    }
                    else{
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }
                    imprimir(tablero);
                }

            }
            else{
                cout<<"palabra no encontrada en el diccionario"<<endl;
                imprimir(tablero);
            }
            break;
        
        case 'b':
            imprimir(tablero);
            break;
        case 'c':
            cout<<"saliendo"<<endl;
            puntuacion(puntos);
            break;
        default:
            cout<<"valores invalidos"<<endl;
            opc=0;
            break;
        }
    }
    while(opc!='c');

    imprimir(tablero);
    estaVacio(tablero);
}

bool estaVacio(char **tablero){
    for(int i=0;i<9;i++){
        for(int j=0; j<9; j++){
            if(*(*(tablero+i)+j)!=' '&&*(*(tablero+i)+j)!='x'){
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
    int posicion=0;
    srand(time(NULL));
    for(int i=0; i<9; i++){
        posicion=rand()%9;
        for(int j=0; j<9; j++){
            if(j!=posicion){
                *(*(tablero+i)+j)=' ';
            }
            else{
                *(*(tablero+i)+j)='x';
            }
        }
    }
}

void orientacionSelect(Orientacion &orientacion){
    int o=0;
    bool val=false;
    do{
        cout<<"en que orientacion quieres colocar tu palabra(1 para vertical/ 0 para horizontal ): ";
        cin>>o;
        switch(o){
        case 0:
            orientacion=HORIZONTAL;
            val=true;
            break;
        case 1:
            orientacion=VERTICAL;
            val=true;
            break; 
        default:
            cout<<"valor fuera de limites"<<endl;    
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

bool colocarPalabra(char** tablero, int filas, int columnas, Orientacion ori, char *palabra, int &puntos){
    int cont=0;
    if(vacio){
        if(cabe(palabra,filas,columnas,ori)){    
            if(ori==0){
                for(unsigned int i=filas;i<=columnas+strlen(palabra)-1;i++){
                    tablero[filas][i]=palabra[cont];
                    cont++;
                }
                puntos++;
                return true;  
            }
            else{
                for(unsigned int i=columnas;i<=filas+strlen(palabra)-1;i++){
                    tablero[i][columnas]=palabra[cont];
                    cont++;
                }
                puntos++;
                return true;
            }
        }
        cout<<"no cabe la palabra en el tablero"<<endl;
        return false;
    }
    else{
        if(cabe(palabra,filas,columnas,ori)){    
            if(ori==0&&conecta(tablero,filas,columnas,ori,palabra, puntos)){
                for(unsigned int i=columnas;i<=columnas+strlen(palabra)-1;i++){
                    tablero[filas][i]=palabra[cont];
                    cont++;
                }
                puntos++;
                return true;  
            }
            else{
                if(conecta(tablero,filas,columnas,ori,palabra, puntos)){
                    for(unsigned int i=filas;i<=filas+strlen(palabra)-1;i++){
                        tablero[i][columnas]=palabra[cont];
                        cont++;
                    }
                }
                else{
                    cout<<"la palabra no conecta con otra palabra"<<endl;
                    return false;
                }
                puntos++;
                return true;

                }
            }
        cout<<"no cabe la palabra en el tablero"<<endl;
        return false;
    }

}

bool cabe(char* palabra,int fila, int columna, Orientacion ori){
    if(ori==1){
        if(fila+strlen(palabra)>9){
            return false;
        }
        else{
            return true;
        }
    }
    if(ori==0){
        if(columna+strlen(palabra)>9){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

bool conecta(char** tab, int f, int c, Orientacion o, char* palabra, int& puntos){
    int contC=0;
    bool control=false;
    if(o==0){
        for(unsigned int i=c;i<=c+strlen(palabra)-1;i++){
            if(tab[f][i]==palabra[contC]) control=true;
            else{
                if(tab[f][i]!=' '){
                    if(tab[f][i]=='x'){
                        puntos*=2;
                        control=true;
                    }
                    else{
                        return false;
                    }
                }
            }
            contC++;
        }
    }
    else{
        for(unsigned int i=f;i<=f+strlen(palabra)-1;i++){
            if(tab[i][c]==palabra[contC]) control=true;
            else{
                if(tab[i][c]!=' '){
                    if(tab[i][c]=='x'){
                        puntos*=2;
                        control=true;
                    }
                    else{
                        return false;
                    }

                }
            }
            contC++;
        }
    }
    return control;
}

void puntuacion(int puntos){
    char* nombre=new char[3], *nombreMost=new char[3];
    int puntosMost=0;
    cout<<"ingresa el nombre del jugador(solo 3 letras): ";
    cin>>nombre;
    FILE* puntuacion=fopen("puntuacion.txt","a");
    fprintf(puntuacion,"jugador: %s\tpuntuacion: %d\n",nombre,puntos);
    fclose(puntuacion);
    puntuacion=fopen("puntuacion.txt","r");
    while(fscanf(puntuacion,"jugador: %s\tpuntuacion: %d\n",nombreMost,&puntosMost)!=EOF){
        cout<<"nombre: "<<nombreMost<<"\tpuntuacion: "<<puntosMost<<endl;
    }
    fclose(puntuacion);
}