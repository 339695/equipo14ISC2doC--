/*Proyecto final Programacion I
por: Equipo 14 ISC 2c
Ejercicio #4: Milenio*/
#include <iostream>
#include <string.h>
using namespace std;
char cadena1[100],cadena2[100];
void pedimo(char[],char[]);
void comparamo(char[],char[]);

int main() {
    int t;
    cin>>t;
    cin.ignore();
    while(t--){
        pedimo(cadena1,cadena2);
        comparamo(cadena1,cadena2);
    }
    return 0;
}

void pedimo(char cadena1[],char cadena2[]){
    cout<<"dame la cadena 1 we: \n";
    cin.getline(cadena1, 100);
    cout<<"dame la cadena 2 we: \n";
    cin.getline(cadena2, 100);
}
void comparamo(char cadena1[],char cadena2[]){
    int j=0,c=0;
    for(int i=0;i<strlen(cadena1);i++){
        if(cadena2[j]==cadena1[i]){
            j++; c++;
        }

    }
    if(c==strlen(cadena2))cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
 
}
