#include "mostrar.h"
#include "bits.h"
#include <iostream>
using namespace std;

char fichaAChar(unsigned int valor) {
    switch (valor) {
        case 0: return '.';
        case 1: return '#';
        case 2: return '&';
        case 3: return '@';
        case 4: return ')';
        case 5: return '=';
        case 6: return '%';
        default: return '?';
    }
}

void mostrarTableroFichas(const unsigned char* tablero, int filas, int columnas) {
    for (int idx = 0; idx < filas * columnas; idx++) {
        unsigned int ficha = leerFicha(tablero, idx);
        cout << fichaAChar(ficha) << " ";
        if ((idx + 1) % columnas == 0) cout << endl;
    }
}

void mostrarTableroBits(const unsigned char* tablero, int filas, int columnas) {
    for (int idx = 0; idx < filas * columnas; idx++) {
        unsigned int ficha = leerFicha(tablero, idx);
        for (int b = 2; b >= 0; b--) {
            cout << ((ficha >> b) & 1);
        }
        cout << " ";
        if ((idx + 1) % columnas == 0) cout << endl;
    }
}
