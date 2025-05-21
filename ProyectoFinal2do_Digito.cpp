#include <iostream>
#include <fstream>
using namespace std;

void ISBN(long long codigo, int A[]);
bool ISBNValido(int A[]);

int main() {
    freopen("entrada.txt", "r", stdin);      // Entrada desde archivo
    freopen("resultados.txt", "w", stdout);  // Salida a archivo de resultados

    ofstream isbns("isbns.txt");             // Otro archivo para guardar solo los ISBN

    long long codigo;
    int A[13];

    while (cin >> codigo) {  // Leer múltiples ISBNs desde archivo
        cout << "ISBN: " << codigo << endl;
        isbns << codigo << endl;
        ISBN(codigo, A);
        cout << "------------------" << endl;
    }

    isbns.close();
    return 0;
}

void ISBN(long long codigo, int A[]) {
    for (int i = 0; i < 13; ++i, codigo /= 10) {
        A[(13 - 1) - i] = codigo % 10;
    }

    for (int i = 0; i < 13; i++) {
        cout << A[i];
    }
    cout << endl;

    if (ISBNValido(A)) {
        cout << "El ISBN es valido" << endl;
    } else {
        cout << "El ISBN no es valido" << endl;
    }
}

bool ISBNValido(int A[]) {
    int suma = 0;

    for (int i = 0; i < 12; i++) {
        if ((i + 1) % 2 != 0) {
            suma += A[i];
        } else {
            suma += A[i] * 3;
        }
    }

    int residuo = suma % 10;
    int resultado = 10 - residuo;
    int verificador = (resultado == 10) ? 0 : resultado;

    return verificador == A[12];
}
