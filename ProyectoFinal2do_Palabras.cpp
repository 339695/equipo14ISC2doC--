#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

void menu();
void crearInfo();

struct juegoT{
    int tipo;
    char palabra[20];
    char pista[100];
    char ini[4];
    char fin[4];
};

void llenarArchivo(FILE*);
void mostrar(FILE*);
void iniciaizarInicioFin(char[4]);
void cargarJuego(FILE*, juegoT[10],int*);
void imprimirArregloStruct(juegoT[10]);
void juego(juegoT[10]);
int puntajePalabra(juegoT, char*);
void llenarSalida(FILE* salida, char* palabra, int puntos);
void iniciaizarPalabra(char palabra[100]);
void iniciaizarPista(char pista[100]);
bool esFin(juegoT registro, char* palabra);
bool esIni(juegoT registro, char* palabra);
void setColor(int);

int main(){
    menu();
    return 0;
}

void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void menu(){
    FILE* info=NULL;
    juegoT registros[10];
    int* tam=NULL;
    llenarArchivo(info);
    cargarJuego(info,registros,tam);
    juego(registros);
}

void juego(juegoT registros[10]){
    FILE* salida=NULL;
    int puntos=0, Pfinales;
    char* palabra=new char[10];
    for(int i=0;i<10;i++){
        switch(registros[i].tipo){
            case 1:
                setColor(7);
                cout<<"adivina un: sustantivo"<<endl;
                break;        
            case 2:
                setColor(7);
                cout<<"adivina un: verbo"<<endl;
                break;
            case 3:
                setColor(7);
                cout<<"adivina un: adjetivo"<<endl;
                break;
            default:
                setColor(4);
                cout<<"no se leyó el archivo"<<endl;
                break;
            }
        setColor(7);
        cout<<"pista: "<<registros[i].pista<<endl;
        cout<<"ingresa la palabra: ";
        cin>>palabra;
        puntos=puntajePalabra(registros[i],palabra);
        setColor(2);
        cout<<"puntos: "<<puntos<<endl;
        llenarSalida(salida,palabra,puntos);
        Pfinales+=puntos;
    }
    setColor(10);
    cout<<"puntaje total: "<<Pfinales;
}

void llenarSalida(FILE* salida, char* palabra, int puntos){
    salida=fopen("salida.dat","a");
    fprintf(salida,"%s, %d\n",palabra,puntos);
    fclose(salida);

}

int puntajePalabra(juegoT registro, char* palabra){
    if(strcmp(registro.palabra,palabra)==0){
        return 10;
    }
    else{
            if(esFin(registro,palabra)){
                return 2;
            }
            else{
                if(esIni(registro,palabra)){
                    return 3;
                }
            }

        }
    return 0;
}

bool esFin(juegoT registro, char* palabra){
    int cont=0;
    if(strlen(palabra)<3)return false;
    for(unsigned int i=strlen(palabra)-3;i<strlen(palabra);i++){
            if(registro.fin[cont]!=palabra[i])return false;
            cont++;
    }
    return true;
}

bool esIni(juegoT registro, char* palabra){
    if(strlen(palabra)<3)return false;
    for(int i=0;i<3;i++){
        if(registro.ini[i]!=palabra[i])return false;
    }
    return true;
}

void cargarJuego(FILE* info, juegoT registros[10],int *tam){
    int tipo,contador=0;
    char palabra[20];
    char pista[100];
    char ini[4];
    char fin[4];
    int elementos=0;
    info=fopen("info.dat","r");
    rewind(info);
    elementos=fscanf(info,"%d,%19[^,],%99[^,],%3[^,],%3[^,]\n",&tipo,palabra,pista,ini,fin);
    // cout<<elementos<<endl;
    while(elementos){
        if(elementos==-1)break;
        registros[contador].tipo=tipo;
        strcpy(registros[contador].palabra,palabra);
        strcpy(registros[contador].palabra,palabra);
        strcpy(registros[contador].pista,pista);
        strcpy(registros[contador].ini,ini);
        strcpy(registros[contador].fin,fin);
        // cout<<"a"<<endl;
        elementos=fscanf(info,"%d,%19[^,],%99[^,],%3[^,],%3[^,]\n",&tipo,palabra,pista,ini,fin);
        // cout<<elementos<<endl;
        contador++;
    }
    tam=&contador;
    setColor(8);
    cout<<"cantidad de elementos leidos: "<<*tam<<endl;
    fclose(info);
}

void llenarArchivo(FILE* info){
    char palabras[10][20]={{"cantar"},{"reluciente"},{"parque"},{"pensar"},{"afortunado"},{"biblioteca"},{"comer"},{"valiente"},{"instrumento"},{"brincar"}};
    int tipos[10]={2,3,1,2,3,1,2,3,1,2};
    char pistas[10][100]={{"un coro lo hace"},{"algo que brilla mucho es..."},{"espacio verde"},{"proceso para desarrollar ideas"},{"persona con mucha suerte"},{"lugar donde hay libros"},{"se hace para vivir"},{"una persona sin miedo es..."},{"otro nombre de herramienta"},{"empujar el suelo"}};
    juegoT registro;
    int cont=0;
    info=fopen("info.dat","w");
    for(int iterador=0;iterador<10;iterador++){
        iniciaizarPalabra(registro.palabra);
        iniciaizarPista(registro.pista);
        iniciaizarInicioFin(registro.ini);
        iniciaizarInicioFin(registro.fin);
        registro.tipo=tipos[iterador];
        strcpy(registro.palabra,palabras[iterador]);
        strcpy(registro.pista,pistas[iterador]);
        for(int j=0;j<3;j++){
            registro.ini[j]=registro.palabra[j];
        }
        for(unsigned int j=strlen(registro.palabra)-3;j<strlen(registro.palabra);j++){
            registro.fin[cont]=registro.palabra[j];
            cont++;
        }
        fprintf(info,"%d,%s,%s,%s,%s\n",registro.tipo,registro.palabra,registro.pista,registro.ini,registro.fin);
        cont=0;
    }
    fclose(info);
}


void iniciaizarInicioFin(char IniciooFin[4]){
    for(int i=0;i<4;i++){
        IniciooFin[i]='\0';
    }
}

void iniciaizarPalabra(char palabra[20]){
    for(int i=0;i<20;i++){
        palabra[i]='\0';
    }
}

void iniciaizarPista(char pista[100]){
    for(int i=0;i<100;i++){
        pista[i]='\0';
    }
}