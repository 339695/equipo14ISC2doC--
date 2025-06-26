/*Proyecto final Programacion I
por: Equipo 14 ISC 2c
Ejercicio #4: Milenio*/
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;
void pedimo(char*,char*);
void comparamo(char*,char*);
void setColor(int);

int main() {
    char *cadena1=new char[100],*cadena2=new char[100];     //define dos variables dinamicas
    int cantidad;
    setColor(7);
    cout<<"Cuantas veces quieres comparar? \n";
    cin>>cantidad;
    cin.ignore();
    while(cantidad--){
        pedimo(cadena1,cadena2);        
        comparamo(cadena1,cadena2);
    }
    delete(cadena1);    //cierra la variable dinamica cadena1
    delete(cadena2);    //cierra la variable dinamica cadena2
    return 0;
}

void setColor(int color){               
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);    //funcion propia de windows.h para cambiar el color de la letra
}   

void pedimo(char *cadena1,char *cadena2){
    setColor(13);
    cout<<"dame la cadena 1 : \n";
    cin.getline(cadena1, 100);      //cin de una cadena de caracteres con espacios
    setColor(13);
    cout<<"dame la cadena 2 : \n";
    cin.getline(cadena2, 100);      //cin de una cadena de caracteres con espacios
}
void comparamo(char *cadena1,char *cadena2){
    FILE *outputs;
    outputs=fopen("output.txt","a");    //abre el archivo de tipo append 
    int iteradorCadena=0,control=0;
    for(unsigned int i=0;i<strlen(cadena1);i++){
        if(cadena2[iteradorCadena]==cadena1[i]){    //valida caracter por caracter, si el caracter de la cadena1 en la posicion i   
            iteradorCadena++; control++;            //es igual a la cadena 2 en la posicion del iterador, si es así aumenta en 1 
        }                                           //la variable control y la variable iterador.   

    }
    fprintf(outputs,"%s\t%s\n",cadena1,cadena2);    //imprimir en el archivo las cadenas separadas por una tabulacion
    if(control==strlen(cadena2)){ //valida si la variable control tiene el valor del tamaño de la segunda 
        setColor(10);
        cout<<"YES"<<endl;          
        fprintf(outputs,"YES\n");
    }
    else{                          //si no lo tiene:
        setColor(4);
        cout<<"NO"<<endl;
        fprintf(outputs,"NO\n");
    }
    fclose(outputs);    //cierra el archivo 
}

