#include <iostream>
#include <string.h>
using namespace std;

void menu();
void crearInfo();

struct juegoT{
    int tipo;
    char palabra[20];
    char pista[100];
    char ini[6];
    char fin[6];
};

void llenarArchivo(FILE*);
void mostrar(FILE*);
void iniciaizarInicioFin(char[6]);
void cargarJuego(FILE*, juegoT[10],int*);
void imprimirArregloStruct(juegoT[10]);
void juego(juegoT[10],int*);
int puntajePalabra(juegoT, char*);
void llenarSalida(FILE* salida, char* palabra, int puntos);

int main(){
    menu();

    return 0;
}

void menu(){
    FILE* info=NULL;
    juegoT registros[10];
    int* tam=NULL;
    llenarArchivo(info);
    cargarJuego(info,registros,tam);
    juego(registros,tam);
}

void juego(juegoT registros[10], int* tam){
    FILE* salida=NULL;
    int puntos;
    char* palabra=new char[10];
    for(int i=0;i<10;i++){
        switch(registros[i].tipo){
            case 1:
                cout<<"adivina un: sustantivo";
                break;        
            case 2:
                cout<<"adivina un: verbo";
                break;
            case 3:
                cout<<"adivina un: adjetivo";
                break;
            }
        cout<<"pista: "<<registros[i].pista<<endl;
        cout<<"ingresa la palabra: ";
        cin>>palabra;
        puntos=puntajePalabra(registros[i],palabra);
        cout<<"puntos: "<<puntos;
        llenarSalida(salida,palabra,puntos);
    }
    cout<<"puntaje total: "<<puntos;
}

void llenarSalida(FILE* salida, char* palabra, int puntos){
    salida=fopen("salida.dat","a");
    if(salida==NULL){
        cout<<"error abriendo el coso";
        return;
    }
    fprintf(salida,"%s, %d\n",palabra,puntos);
    fclose(salida);

}

int puntajePalabra(juegoT, char*){

}


void cargarJuego(FILE* info, juegoT registros[10],int *tam){
    int iterador=0;
    info=fopen("tupu.dat","rb+");
    while (fread(&registros[iterador], sizeof(juegoT), 1, info)){
        iterador++;
        tam=&iterador;
    }
    fclose(info);
    cout<<"cantidad de elementos leidos: "<<*tam<<endl;
    imprimirArregloStruct(registros);
}

void imprimirArregloStruct(juegoT registros[10]){
    for(int i=0;i<10;i++){
        cout<<registros[i].palabra<<endl;
    }
}

void llenarArchivo(FILE* info){
    char palabras[10][20]={{"cantar"},{"reluciente"},{"parque"},{"pensar"},{"afortunado"},{"biblioteca"},{"comer"},{"valiente"},{"instrumento"},{"brincar"}};
    int tipos[10]={2,3,1,2,3,1,2,3,1,2};
    char pistas[10][100]={{"un coro lo hace"},{"algo que brilla mucho es..."},{"espacio verde"},{"proceso para desarrollar ideas"},{"persona con mucha suerte"},{"lugar donde hay libros"},{"se hace para vivir"},{"una persona sin miedo es..."},{"otro nombre de herramienta"},{"empujar el suelo"}};
    juegoT unidad;
    int cont,iterador=0;
    info=fopen("tupu.dat","wb");
    do{
        iniciaizarInicioFin(unidad.ini);
        iniciaizarInicioFin(unidad.fin);
        cont=0;
        unidad.tipo=tipos[iterador];
        strcpy(unidad.palabra,palabras[iterador]);
        strcpy(unidad.pista,pistas[iterador]);
        for(int j=0;j<5;j++){
            unidad.ini[j]=unidad.palabra[j];
        }
        for(unsigned int j=strlen(unidad.palabra)-5;j<strlen(unidad.palabra);j++){
            unidad.fin[cont]=unidad.palabra[j];
            cont++;
        }
        fwrite(&unidad,sizeof(juegoT),1,info);
        iterador++;
    }
    while(iterador!=10);
    fclose(info);
    // mostrar(info);
}

void mostrar(FILE* info){
    juegoT unidad;
    info=fopen("tupu.dat", "rb");
    while (fread(&unidad, sizeof(juegoT), 1,info)){
        cout<<unidad.tipo<<endl;
        cout<<unidad.palabra<<endl;
        cout<<unidad.pista<<endl;
        cout<<unidad.ini<<endl;
        cout<<unidad.fin<<endl;
    }
}

void iniciaizarInicioFin(char IniciooFin[6]){
    for(int i=0;i<6;i++){
        IniciooFin[i]='\0';
    }
}