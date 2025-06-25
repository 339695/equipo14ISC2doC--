#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

struct juegoT{
    int tipo;
    char palabra[20];
    char pista[100];            //struct para el funcionamiento del proyecto
    char ini[4];
    char fin[4];
};

void menu();
void crearInfo();
void llenarArchivo(FILE*);
void mostrar(FILE*);
void iniciaizarInicioFin(char[4]);
void cargarJuego(FILE*, juegoT[10],int*);
void imprimirArregloStruct(juegoT[10]);
void juego(juegoT[10]);                                                     //prototipos
int puntajePalabra(juegoT, char*);
void llenarSalida(FILE* salida, char* palabra, int puntos);
void iniciaizarPalabra(char palabra[100]);
void iniciaizarPista(char pista[100]);
bool esFin(juegoT registro, char* palabra);
bool esIni(juegoT registro, char* palabra);
void setColor(int);

int main(){
    menu();     //llamada a la funcion menu
    return 0;
}

void setColor(int color){               //declaracion de funcion setColor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);        //llama a funcion propia de windows.h
}   //fin de la funcion setColor

void menu(){            //declaracion de la funcion menu
    FILE* info=NULL;        
    juegoT registros[10];
    int* tam=NULL;
    llenarArchivo(info);        //llamada de la funcion llenarArchivo
    cargarJuego(info,registros,tam);    //llamada de la funcion cargarJuego
    juego(registros);       //llamada de la funcion juego 
}       //fin de la funcion menu

void juego(juegoT registros[10]){   //declaracion de la funcion juego 
    FILE* salida=NULL;
    int puntos=0, Pfinales;
    char* palabra=new char[10];
    for(int i=0;i<10;i++){      //for que recorrera los registros  
        switch(registros[i].tipo){      //switch segun la variable tipo del struct registros
            case 1:     
                setColor(7);    //llamada de la funcion setColor
                cout<<"adivina un: sustantivo"<<endl;
                break;        
            case 2:
                setColor(7);    //llamada de la funcion setColor
                cout<<"adivina un: verbo"<<endl;
                break;
            case 3:
                setColor(7);    //llamada de la funcion setColor
                cout<<"adivina un: adjetivo"<<endl;
                break;
            default:
                setColor(4);    //llamada de la funcion setColor
                cout<<"no se leyó el archivo"<<endl;
                break;
            }                                                           //imprime el tipo y la pista de la palabra
        setColor(7);    //llamada de la funcion setColor
        cout<<"pista: "<<registros[i].pista<<endl;
        cout<<"ingresa la palabra: ";                       
        cin>>palabra;                               //cin de la palabra
        puntos=puntajePalabra(registros[i],palabra);        //llamada de la funcion puntajePalabra
        setColor(2);    //llamada de la funcion setColor
        cout<<"puntos: "<<puntos<<endl;                     //impresion de los puntos ganados
        llenarSalida(salida,palabra,puntos);                //llamada de la funcion llenarSalida
        Pfinales+=puntos;           
    }
    setColor(10);   //llamada de la funcion setColor
    cout<<"puntaje total: "<<Pfinales;      //impresionde los puntos totales
}       //fin de la funcion juego

void llenarSalida(FILE* salida, char* palabra, int puntos){     //declaracion de la funcion llenarSalida
    salida=fopen("salida.dat","a");                     
    fprintf(salida,"%s, %d\n",palabra,puntos);      //guarda en el archivo salida.dat los valores que recibe como argumento
    fclose(salida);

}   //fin de la funcion llenar salida

int puntajePalabra(juegoT registro, char* palabra){     //declaracion de la funcion puntajePalabra
    if(strcmp(registro.palabra,palabra)==0){    //si las cadenas que recibe con iguales, retorna 10
        return 10;
    }
    else{
            if(esFin(registro,palabra)){    //si el valor de retorno de la funcion esFin es true:
                return 2;                   //retorna 2
            }
            else{
                if(esIni(registro,palabra)){    //si el valor de retorno de la funcion esIni es true: 
                    return 3;                   //retorna 3
                }
            }

        }
    return 0;               //si no se cumple ninguno, retorna 0
}   //fin de la funcion puntajePalabra

bool esFin(juegoT registro, char* palabra){ //declaracion de la funcioin esFin
    int cont=0;
    if(strlen(palabra)<3)return false;      //si la cadena que recibe es de menos de 3 caracteres, retorna false
    for(unsigned int i=strlen(palabra)-3;i<strlen(palabra);i++){    //recorre los ultimos 3 caracteres de la cadena   
            if(registro.fin[cont]!=palabra[i])return false;     //si es diferente a la variable fin, retorna false
            cont++;
    }
    return true;                //si son iguales, retorna true
}   //fin de la funcioni esFin

bool esIni(juegoT registro, char* palabra){     //declaracion de la funcion esIni
    if(strlen(palabra)<3)return false;              //si la cadena que recibe es menor a 3 caracteres, retorna false
    for(int i=0;i<3;i++){               //recorre las primeras 3 posiciones de la cadena 
        if(registro.ini[i]!=palabra[i])return false;        //si es diferente a la variable ini, retorna false
    }
    return true;            //si no, retorna true
}   //fin de la funcion esIni

void cargarJuego(FILE* info, juegoT registros[10],int *tam){    //declaracion de la funcion cargarJuego
    int tipo,contador=0;
    char palabra[20];
    char pista[100];        //define variables nuevas
    char ini[4];
    char fin[4];
    int elementos=0;
    info=fopen("info.dat","r");     //abre el archivo en read
    rewind(info);
    elementos=fscanf(info,"%d,%19[^,],%99[^,],%3[^,],%3[^,]\n",&tipo,palabra,pista,ini,fin);        //guarda en las variables los elementos del archivo
    while(elementos){       //recorre mientras que elementos exista
        if(elementos==-1)break;        //si elementos es igual a -1, se detiene 
        registros[contador].tipo=tipo;
        strcpy(registros[contador].palabra,palabra);
        strcpy(registros[contador].palabra,palabra);    //le asigna los valores que recibio del archivo a los registros 
        strcpy(registros[contador].pista,pista);
        strcpy(registros[contador].ini,ini);
        strcpy(registros[contador].fin,fin);
        elementos=fscanf(info,"%d,%19[^,],%99[^,],%3[^,],%3[^,]\n",&tipo,palabra,pista,ini,fin);    //le asigna a las variables la siguiente linea del archivo 
        contador++;
    }
    tam=&contador;
    setColor(8);    //llamada de la funcion setColor
    cout<<"cantidad de elementos leidos: "<<*tam<<endl;
    fclose(info);   //cierra el archivo
}   //fin de la funcion cargarJuego

void llenarArchivo(FILE* info){     //declaracion de la funcion llenarArchivo
    char palabras[10][20]={{"cantar"},{"reluciente"},{"parque"},{"pensar"},{"afortunado"},{"biblioteca"},{"comer"},{"valiente"},{"instrumento"},{"brincar"}};
    int tipos[10]={2,3,1,2,3,1,2,3,1,2};    //define las palabras, pistas y tipos que se van a insertar en el archivo info.dat
    char pistas[10][100]={{"un coro lo hace"},{"algo que brilla mucho es..."},{"espacio verde"},{"proceso para desarrollar ideas"},{"persona con mucha suerte"},{"lugar donde hay libros"},{"se hace para vivir"},{"una persona sin miedo es..."},{"otro nombre de herramienta"},{"empujar el suelo"}};
    juegoT registro;
    int cont=0;
    info=fopen("info.dat","w");     //abre el archivo en write 
    for(int iterador=0;iterador<10;iterador++){
        iniciaizarPalabra(registro.palabra);     //llamada de la funcion incializarPalabra
        iniciaizarPista(registro.pista);         //llamada de la funcion incializarPista
        iniciaizarInicioFin(registro.ini);       //llamada de la funcion incializarInicioFin
        iniciaizarInicioFin(registro.fin);       //llamada de la funcion incializarIniciofin
        registro.tipo=tipos[iterador];
        strcpy(registro.palabra,palabras[iterador]);    //le asiga a cada campo del una palabra, tipo y pista de las variables de arriba
        strcpy(registro.pista,pistas[iterador]);    
        for(int j=0;j<3;j++){
            registro.ini[j]=registro.palabra[j];                                            //guarda en ini los primeros 3 caracteres de la palabra
        }                                                                                
        for(unsigned int j=strlen(registro.palabra)-3;j<strlen(registro.palabra);j++){
            registro.fin[cont]=registro.palabra[j];                                         //y guarda en fin los ultimos 3 caracteres de la palabra
            cont++;
        }
        fprintf(info,"%d,%s,%s,%s,%s\n",registro.tipo,registro.palabra,registro.pista,registro.ini,registro.fin);   //los guarada en el archivo info.dat
        cont=0;
    }
    fclose(info);       //cierra el archivo
}   //fin de la funcion llenar achivos


void iniciaizarInicioFin(char IniciooFin[4]){   //declaracion de la funcion incializarInicioFin
    for(int i=0;i<4;i++){
        IniciooFin[i]='\0';         //llena los 4 espacios con \0
    }
}

void iniciaizarPalabra(char palabra[20]){       //declaracion de la funcion incializarPalabra
    for(int i=0;i<20;i++){
        palabra[i]='\0';            //llena los 20 espacios con \0
    }
}

void iniciaizarPista(char pista[100]){       //declaracion de la funcion incializarPista
    for(int i=0;i<100;i++){
        pista[i]='\0';              //llena los 100 espacios con \0
    }
}