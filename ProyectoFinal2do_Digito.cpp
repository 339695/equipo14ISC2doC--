/*Proyecto final Programacion I
por: Equipo 14 ISC 2c
Ejercicio #4: Digito*/
#include <iostream>
#include <windows.h>
using namespace std;
void ISBN(long long codigo,int* isbn);
bool ISBNValido(int* isbn);
void setColor(int);

int main(){
    long long codigo;
    int* isbn=new int[13];
    FILE *archivo;
    archivo=fopen("ISBN.txt","r");  //abre el archivo en modo lectura
    if(archivo==NULL){      //valida que se pueda abrir el archivo
        setColor(4);
        cout<<"Error al abrir el archivo."<<endl;   
        return 1;
    }
    while(fscanf(archivo,"%lld",&codigo)!=EOF){   //guarda en variables lo que reciba de cada linea del archivo   
        ISBN(codigo, isbn);        //llama a la funcion isbns con los argumentos que acaba de recibir
    }
    fclose(archivo);    //cierra el archivo 
    delete(isbn);       //cierra la memoria dinamica
    return 0;           
}

void setColor(int color){               
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);    //funcion propia de windows.h para cambiar el color de la letra
}   


void ISBN(long long codigo, int* isbn){
    FILE *archivo;
    archivo=fopen("ISBN.txt","a");
    for(int i=0;i<13;i++,codigo/=10){
        isbn[(13-1)-i]=codigo%10;       //cada digito se guarda en el arreglo
    }
    setColor(7);
    cout<<"ISBN descompuesto: ";
    for(int i=0;i<13;i++){
        cout<<isbn[i];          // mostrar el ISBN desglosado
    }
    cout<<endl;
    if(ISBNValido(isbn)){   //si es ISBN es valido: 
        setColor(10);
        cout<<"El ISBN es valido"<<endl;       
    } 
    else{                   //si no es valido
        setColor(10);
        cout<<"El ISBN no es valido"<<endl; 
    }
    fclose(archivo);    //cierra el archivo
    setColor(7);
    cout<<"-----------------------------"<<endl;
}

bool ISBNValido(int* isbn){
    int suma=0;
    for(int i=0;i<12;i++){
        if((i+1)%2!=0){     //recorre posicion por posicionbuscando pares
            suma+=isbn[i];  //si es una posicion par en la variable suma 
        }                   //le suma el valor de la posicion actual del ISBN
        else{
            suma+=isbn[i]*3;//si es una posicion inpar a la variable suma 
        }                   //le suma 3 veces el valor de la posicion actual del ISBN
    }
    int residuo=suma%10;        
    int resultado=10-residuo;
    int verificador=resultado%10;
    return verificador==isbn[12];
}
