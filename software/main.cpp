#include <iostream>
#include "bits.h"
#include "azar.h"
#include "tablero.h"
#include "mostrar.h"

using namespace std;

int main() {
    int filas, columnas;

    cout << "Ingrese numero de filas: ";
    cin >> filas;
    cout << "Ingrese numero de columnas: ";
    cin >> columnas;

    unsigned char* tablero = crearTablero(filas, columnas);
    poblarTablero(tablero, filas, columnas);

    cout << "\n=== Vista de fichas ===" << endl;
    mostrarTableroFichas(tablero, filas, columnas);

    cout << "\n=== Vista de bits ===" << endl;
    mostrarTableroBits(tablero, filas, columnas);

    liberarTablero(tablero);
    return 0;
}
