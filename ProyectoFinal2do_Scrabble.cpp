#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

char diccionario[10][10]={"manzana", "perro", "cielo", "felicidad", "rio", "espejo", "sol", "libro", "piedra", "flor"};     //diccionario palabras para scrabble

enum Orientacion {HORIZONTAL,VERTICAL};
bool conecta(char**, int, int, Orientacion, char*, int&);
bool colocarPalabra (char**, int, int, Orientacion, char*, int&);
bool estaVacio (char**);
bool esPalabra(char*);                                              //prototipos
void imprimir(char**);
void inicializar(char**);
void orientacionSelect(Orientacion&);
bool cabe(char*,int,int,Orientacion);
void menu();
void puntuacion(int);
bool valid(char*);
void setColor(int);
bool vacio=true;

int main(){
    cout<<"Scrabble es un juego donde se intenta obtener puntos mediante la construccion de palabras\nEl juego se desarrolla sobre un tablero de 9x9, el cual tiene casillas de premiacion(casillas marcadas con x)\n que multiplican el numero de puntos concedidos"<<endl;
    menu();     //llamada de la función menu
    return 0;
}

void setColor(int color){                    //declaracion de la funcion setColor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);    //funcion propia de la librería wondows.h 
}


bool valid(int opcion){               //declaracion de la funcion valid
    if(opcion==97||opcion==98||opcion==99){
        return true;
    }
    return false;
}

void menu(){            //declaración de la funcion menu
    int puntos=0;
    char opc;
    Orientacion orient;
    char **tablero;             //declaracion de variables
    char *palabra;
    int x=0,y=0;
    tablero = new char*[9];
    palabra = new char[9];          //inicializacion de matriz dinamina de 9x9 
    for(int i=0; i<9; i++){
        tablero[i]=new char[9];
    }
    inicializar(tablero);       //llamada a la funcion inicializar
    imprimir(tablero);          //llamada a la funcion imprimir
    do{                                                                 //inicio de do while
        setColor(13);               //llamada a la funcion setColor
        cout<<"\tmenu"<<endl;
        setColor(7);                //llamada a la funcion setColor
        cout<<"a. colocar palabra nueva"<<endl; 
        cout<<"b. imprimir"<<endl;                      
        cout<<"c. terminar intento"<<endl;          //menu
        cout<<"elige una opcion: ";
        cin>>opc;
        if(!valid(opc)){            //llamada a la funcion valid
            continue;
        }
        switch(opc){                                //inicio de switch
        case 'a':       //case a
            cout<<"ingresa la palabra que quieres insertar: ";
            cin>>palabra;
            if(esPalabra(palabra)){     //condicional con el retorno de llamada a la funcion esPalabra
                orientacionSelect(orient);  //llamada a la funcion orientacionSelect
                if(estaVacio(tablero)){     //condicional con el retorno de llamada a la funcion estaVacio
                    if(colocarPalabra(tablero, 4, 4, orient, palabra, puntos)){     //condicional con el retorno de la llamada a la funcion colocarPalabra
                        system("cls");         //limpiar pantalla
                        setColor(2);           //llamada a la funcion setColor
                        cout<<"palabra insertada correctamente"<<endl;
                        vacio=false;
                    }                                                               //fin condicional
                    else{                                                           //else
                        setColor(4);            //llamada a la funcion setColor
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }                                                               //fin else
                    imprimir(tablero);              //llamada a la funcion imprimir
                }                           //fin condicional
                else{                       //else
                    setColor(7);                //llamada a la funcion setColor
                    cout<<"en que posicion de x quieres colocar tu palabra? ";
                    cin>>x;
                    cout<<"en que posicion de y quieres colocar tu palabra? ";
                    cin>>y;
                    if(colocarPalabra(tablero, y, x, orient, palabra, puntos)){     //condicional con el retorno de llamada a la funcion colocarPalabra
                        system("cls");                      //limpiar pantalla
                        setColor(2);                        //llamada a la funcion setColor
                        cout<<"palabra insertada correctamente"<<endl;
                    }                                                               //fin condicional
                    else{                                                           //else  
                        setColor(4);                        //llamada a la funcion setColor
                        cout<<"la palabara no se pudo insertar"<<endl;
                    }                                                               //fin else
                    imprimir(tablero);
                }                       //else

            }                         //fin condicional         
            else{                     //else
                system("cls");  //limpiar pantalla
                setColor(4);    //llamada a la funcion setColor
                cout<<"palabra no encontrada en el diccionario"<<endl;
                imprimir(tablero);  //llamada a la funcion imprimir
            }                        //fin else
            break;  //fin case a
        
        case 'b':   //case b
            imprimir(tablero); //llamada a la funcion imprimir
            break;  //fin case b
        case 'c':   //case c
            setColor(4);    //llamada a la funcion setColor
            cout<<"saliendo"<<endl;
            puntuacion(puntos); //llamada a la funcion puntuacion
            break;  //fin case c
        default:    //case default
            setColor(4);    //llamada a la funcion setColor
            cout<<"valores invalidos"<<endl;
            opc=0;
            break;  //fin case default 
        }                                          //fin de switch
    }
    while(opc!='c');                                                    //fin de do while
}                       //fin funcion 

bool estaVacio(char **tablero){     //declaracion de la funcion estaVacio
    for(int i=0;i<9;i++){
        for(int j=0; j<9; j++){
            if(*(*(tablero+i)+j)!=' '&&*(*(tablero+i)+j)!='x'){
                return false;                                       //recorrer la matriz dinamica buscando un valor diferente a ' ' o 'x'
            }                                                       //si lo encuentra retorna false
        }                                                           
    }
    return true;                                                    //si no se retorno false en ningun punto, retorna true
}                                   //fin de la funcion estaVacio

void imprimir(char **tablero){      //declaracion de la funcion imprimir
    cout<<"  ";
    for(int i=0;i<9;i++){
        setColor(14);          //llamada a la funcion setColor
        cout<<i<<" ";           //imprime numeros del 0 al 8 separados por un espacio
    }
    cout<<endl;
    for(int i = 0; i < 9; i++){
        setColor(14);           //llamada a la funcion setColor
        cout<<i;                //imprime numeros del 0 al 8
        setColor(8);          //llamada a la funcion setColor
        cout<<"|";            //imprime la separacion inicial del tablero
        for(int j = 0; j < 9; j++){
            setColor(8);    //llamada a la funcion setColor
            cout<<tablero[i][j]<<"|";      //imprime el resto de separaciones
        }
        cout<<endl;     //imprime un salyo de linea
    }

}

void inicializar(char **tablero){       //declaracion de la funcion inicializar
    int posicion=0;         
    srand(time(NULL));              //se define el tiempo de randomizado
    for(int i=0; i<9; i++){     //inicio de for
        posicion=rand()%9;          //se define el rango de valores que puede tomar el randomizado
        for(int j=0; j<9; j++){         //inicio de for
            if(j!=posicion){               //si la posicion actual es diferente al valor randomizado:   
                *(*(tablero+i)+j)=' ';          //se le da el valor de ' ',
            }                              //sin condicional
            else{                          //else
                *(*(tablero+i)+j)='x';          //si no, se le da el valor de 'x'
            }                              //fin else
        }                               //fin de for
    }                           //fin de for
}                                   //fin de la funcion inicializar

void orientacionSelect(Orientacion &orientacion){   //declaracion de la funcion orientacionSelect
    int o=0;            //declaracion de variables
    bool val=false;
    do{     //inicio do while
        setColor(7);        //llamada a la funcion setColor
        cout<<"en que orientacion quieres colocar tu palabra(1 para vertical/ 0 para horizontal ): ";
        cin>>o;
        switch(o){  //inicio switch
            case 0:     //inicio case 0
                orientacion=HORIZONTAL;         //a orientacion se le da el valor de la enumeracion HORIZONTAL 
                val=true;
                break;  //fin case 0
            case 1:     //inicio case 1
                orientacion=VERTICAL;           //a orientacion se le da el valor de la enumeracion VERTICAL
                val=true;
                break; //fin case 1
            default:    //inicio case default
                setColor(4);    //llamada a la funcion setColor
                cout<<"valor fuera de limites"<<endl;    
                break;  //fin case default
        }
    }while(val!=true);  //fin do while
    
}   //fin de funcion orientacionSelect

bool esPalabra(char* palabra){  //declaracion de la funcion esPalabra
    for(int i=0; i<10; i++){    //inicio de for
        if(strcmp(palabra,diccionario[i])==0){      //busca que la palabra que rice como argumento sea alguna del diccionario
            return true;                            //retorna true
        }                                           //fin de condicional
    }                           //fin de for
    return false;       
}       //fin de funcion esPalabra

bool colocarPalabra(char** tablero, int filas, int columnas, Orientacion ori, char *palabra, int &puntos){  //declaracion de la funcion colocarPalabra
    int cont=0;
    if(estaVacio(tablero)){                  //condicional con el valor de retorno de estaVacio
        if(cabe(palabra,filas,columnas,ori)){    //condicional con el valor de retorno de cabe
            if(ori==0){                                 //condicional con la orientacion
                for(unsigned int i=filas;i<=columnas+strlen(palabra)-1;i++){    
                    tablero[filas][i]=palabra[cont];                                    //se coloca la palabra en horizontal
                    cont++;
                }
                puntos++;                                                               //se suma 1 a los puntos
                return true;  
            }                                           //fin condicional
            else{                                       //else
                for(unsigned int i=columnas;i<=filas+strlen(palabra)-1;i++){
                    tablero[i][columnas]=palabra[cont];                                 //se coloca la palabra en vertical
                    cont++;
                }
                puntos++;                                                               // se suma 1 a los puntos
                return true;
            }                                           //fin else
        }                                         //fin condicional
        setColor(4);    //llamada a la funcion setColor
        cout<<"no cabe la palabra en el tablero"<<endl;
        return false;
    }                                      //fin condicional
    else{                                  //else
        if(cabe(palabra,filas,columnas,ori)){   //condicional con el valor de retorno de cabe
            if(ori==0&&conecta(tablero,filas,columnas,ori,palabra, puntos)){    //condicional con la orientacion y el valor de retorno de la funcion conecta
                for(unsigned int i=columnas;i<=columnas+strlen(palabra)-1;i++){
                    tablero[filas][i]=palabra[cont];                                   //coloca la palabra en horizontal
                    cont++;
                }
                puntos++;                                                               //se suma 1 a los puntos
                return true;  
            }                                       //fin condicional
            else{                                  //else
                if(conecta(tablero,filas,columnas,ori,palabra, puntos)){        //condicional con el valor de retorno de la funcion conecta
                    for(unsigned int i=filas;i<=filas+strlen(palabra)-1;i++){            
                        tablero[i][columnas]=palabra[cont];                           //coloca la palabra en vertical
                        cont++;
                    }
                    puntos++;                                                           //se suma 1 a los puntos
                }                                                               //fin condicional
                else{                                                           //else
                    setColor(4);    //llamada a la funcion setColor
                    cout<<"la palabra no conecta con otra palabra"<<endl;
                    return false;
                }                                                               //fin else
                return true;

            }                                      //fin else
        }                                   //fin condicional
        setColor(4);    //llamada a la funcion setColor
        cout<<"no cabe la palabra en el tablero"<<endl;
        return false;
    }                                   //fin else

}       //fin de la funcion colocarPalabra

bool cabe(char* palabra,int fila, int columna, Orientacion ori){    //declaracion de la funcion cabe
    if(ori==1){                         //condicional con el valor de la orientacion
        if(fila+strlen(palabra)>9){         //si la posicion seleccionada mas el tamaño de la palabra es mayor a 9: 
            return false;                   //retorna false
        }                               //fin condicional
        else{                           //else
            return true;
        }                               //fin else
    }                                   //fin condicional
    if(ori==0){                             //condicional con el valor de la orientacion
        if(columna+strlen(palabra)>9){         //si la posicion seleccionada mas el tamaño de la palabra es mayor a 9
            return false;                      //retorna false
        }                                 //fin condicional
        else{                             //else
            return true;
        }                                 //fin else
    }                                   //fin condicional
    return false;
}                   //fin de la funcion cabe

bool conecta(char** tab, int f, int c, Orientacion o, char* palabra, int& puntos){      //declaracion de la funcion conecta
    int contC=0;
    bool control=false;
    if(o==0){                                                   //condicional con el valor de la orientacion
        for(unsigned int i=c;i<=c+strlen(palabra)-1;i++){   //recorre sobre las columnas, desde la posicion dada hasta la posicion mas el tamaño de la palabra
            if(tab[f][i]==palabra[contC]) control=true;           //si en algun punto con iguales, control es igual a true 
            else{
                if(tab[f][i]!=' '){
                    if(tab[f][i]=='x'){
                        puntos*=2;                                //si no, se valida que el lugar donde se debería escribir la palabra, esté vacio, o tenga una x
                    }
                    else{
                        return false;                           //si no lo está, se retorna false
                    }
                }
            }
            contC++;
        }
    }
    else{                                                   //si la orientacion es 1
        for(unsigned int i=f;i<=f+strlen(palabra)-1;i++){       //recorre sobre las filas, desde la posicion dada, hasta la posicion mas el tamaño de la palabra
            if(tab[i][c]==palabra[contC]) control=true;         //si conecta en algun punto, control es true
            else{
                if(tab[i][c]!=' '){                             //si no, valida que el espacio donde se debe escribir esté vacio
                    if(tab[i][c]=='x'){
                        puntos*=2;
                    }
                    else{
                        return false;                           //si no lo está retorna false
                    }

                }
            }
            contC++;
        }
    }
    return control;                             //si nunca retorno false, retorna true
}

void puntuacion(int puntos){                                //declaracion de la funcion puntuacion
    char* nombre=new char[3], *nombreMost=new char[3];
    int puntosMost=0;
    setColor(7);    //llamada a la funcion setColor
    cout<<"ingresa el nombre del jugador(solo 3 letras): ";
    cin>>nombre;                                                //ingresa el nombre que se va a insertar en el archivo de puntuacion
    FILE* puntuacion=fopen("puntuacion.txt","a");                       //abre el archivo puntuacion como append
    fprintf(puntuacion,"jugador: %s\tpuntuacion: %d\n",nombre,puntos);      //escribe en el archivo el nombre y la puntuacion
    fclose(puntuacion);                                                     //cierra el archivo
    puntuacion=fopen("puntuacion.txt","r");                             //abre el archivo como read
    while(fscanf(puntuacion,"jugador: %s\tpuntuacion: %d\n",nombreMost,&puntosMost)!=EOF){  //guarda en variables los valores que encuentra del archivo 
        setColor(11);   //llamada a la funcion setColor 
        cout<<"nombre: "<<nombreMost<<"\tpuntuacion: "<<puntosMost<<endl;       //imprime los nombres y las puntuaciones
    }
    fclose(puntuacion);     //cierra el archivo
}