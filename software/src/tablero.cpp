#include "tablero.h"
#include "bits.h"
#include "azar.h"

unsigned char* crearTablero(int filas, int columnas) {
    int totalFichas = filas * columnas;
    int totalBits = totalFichas * 3;
    int totalBytes = (totalBits + 7) / 8;

    unsigned char* tablero = new unsigned char[totalBytes];

    for (int i = 0; i < totalBytes; i++) {
        tablero[i] = 0;
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero) {
    delete[] tablero;
}

void poblarTablero(unsigned char* tablero, int filas, int columnas) {
    int totalFichas = filas * columnas;
    for (int idx = 0; idx < totalFichas; idx++) {
        unsigned int ficha = siguienteAleatorio();
        escribirFicha(tablero, idx, ficha);
    }
}
