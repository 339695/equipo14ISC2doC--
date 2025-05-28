/*Proyecto final Programacion I
por: Equipo 14 ISC 2c
Ejercicio #4: Digito*/
#include <iostream>
using namespace std;
void ISBN(long long codigo,int A[]);
bool ISBNValido(int A[]);
int main(){
    long long codigo;
    FILE *archivo;
    archivo=fopen("ISBN.txt","a");
    if(archivo==NULL){
        cout<<"Error al abrir el archivo."<<endl;
        return 1;
    }
    fprintf(archivo,"%lld\t", codigo);
    int A[13];
    cout<<"Ingrese el codigo ISBN (13 digitos): ";
    cin>>codigo;
    ISBN(codigo, A);
    fclose(archivo);
    return 0;
}
void ISBN(long long codigo, int A[]){
    //cada digito se guarda en el arreglo
    FILE *archivo;
    archivo=fopen("ISBN.txt","a");
    for(int i=0;i<13;++i,codigo/=10){
        A[(13-1)-i]=codigo%10;
    }
    // mostrar el ISBN desglosado
    cout<<"ISBN descompuesto: ";
    for(int i=0;i<13;i++){
        cout<<A[i];
    }
    cout<<endl;
    if (ISBNValido(A)) {
        cout<<"El ISBN es valido"<<endl;
        fprintf(archivo,"ISBN valido: \n");
    } 
    else{
        cout<<"El ISBN no es valido"<<endl;
        fprintf(archivo,"ISBN no valido: \n");
    }
}
bool ISBNValido(int A[]){
    int suma=0;
    for(int i=0;i<12;i++){
        if((i+1)%2!=0){
            suma+=A[i];
        } 
        else{
            suma+=A[i]*3;
        }
    }
    int residuo=suma%10;
    int resultado=10-residuo;
    int verificador=resultado%10;
    return verificador==A[12];
}
