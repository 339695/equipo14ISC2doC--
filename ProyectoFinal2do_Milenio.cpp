/*Proyecto final Programacion I
por: Equipo 14 ISC 2c
Ejercicio #4: Milenio*/
#include <iostream>
#include <string.h>
using namespace std;
char cadena1[100],cadena2[100];
void pedimo(char[],char[]);
void comparamo(char[],char[]);
void resolver();

int main() {
    int t;
    cout<<"Cuantas veces quieres comparar? \n";
    cin>>t;
    cin.ignore();
    while(t--){
        pedimo(cadena1,cadena2);
        comparamo(cadena1,cadena2);
    }
    return 0;
}

void pedimo(char cadena1[],char cadena2[]){
    cout<<"dame la cadena 1 : \n";
    cin.getline(cadena1, 100);
    cout<<"dame la cadena 2 : \n";
    cin.getline(cadena2, 100);
}
void comparamo(char cadena1[],char cadena2[]){
    FILE *outputs;
    outputs=fopen("output.txt","a");
    int j=0,c=0;
    for(int i=0;i<strlen(cadena1);i++){
        if(cadena2[j]==cadena1[i]){
            j++; c++;
        }

    }
    //imprimir las cadenas separadas por una tabulacion
    fprintf(outputs,"%s\t%s\n",cadena1,cadena2);
    if(c==strlen(cadena2)){
        cout<<"YES"<<endl;
        fprintf(outputs,"YES\n");
    }
    else{
        cout<<"NO"<<endl;
        fprintf(outputs,"NO\n");
    }
    fclose(outputs);
}

