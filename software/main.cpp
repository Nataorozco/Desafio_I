#include <iostream>
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time

using std::cout, std::cin, std::endl;
using std::rand, std::srand, std::time;

// constexpr: se evalúa en compilación, va directo a .rodata
static constexpr char SIMBOLO[8] = {
    ' ',   // 000  posición vacía
    '#',   // 001
    '&',   // 010
    '@',   // 011
    ')',   // 100
    '=',   // 101
    '%',   // 110
    'D'    // 111  sin significado
};

// [[nodiscard]]: avisa si llamas a leerFicha y tiras el resultado
[[nodiscard]] unsigned int leerFicha(const unsigned char* buf, int idx) {
    int bitPos  = idx * 3;
    int byteIdx = bitPos >> 3;
    int bitOff  = bitPos & 7;

    unsigned int chunk = (unsigned int)buf[byteIdx];
    if (bitOff > 5) {
        chunk |= ((unsigned int)buf[byteIdx + 1]) << 8;
    }
    return (chunk >> bitOff) & 0x07u;
}

void escribirFicha(unsigned char* buf, int idx, unsigned int valor) {
    int bitPos  = idx * 3;
    int byteIdx = bitPos >> 3;
    int bitOff  = bitPos & 7;

    valor &= 0x07u;

    buf[byteIdx] &= (unsigned char)~(0x07u << bitOff);
    if (bitOff > 5) {
        buf[byteIdx + 1] &= (unsigned char)~(0x07u >> (8 - bitOff));
    }

    buf[byteIdx] |= (unsigned char)((valor << bitOff) & 0xFF);
    if (bitOff > 5) {
        buf[byteIdx + 1] |= (unsigned char)(valor >> (8 - bitOff));
    }
}

void rellenarTablero(unsigned char* tablero, int filas, int columnas) {
    int celdas = filas * columnas;

    for (int i = 0; i < celdas; i++) {
        int f = i / columnas;
        int c = i % columnas;

        unsigned int v;
        do {
            v = 1u + (unsigned int)(rand() % 6);   // 1..6

            // ¿forma trío horizontal con las 2 de la izquierda?
            bool trioH = (c >= 2)
                         && leerFicha(tablero, i - 1) == v
                         && leerFicha(tablero, i - 2) == v;

            // ¿forma trío vertical con las 2 de arriba?
            bool trioV = (f >= 2)
                         && leerFicha(tablero, i - columnas)     == v
                         && leerFicha(tablero, i - 2 * columnas) == v;

            if (!trioH && !trioV) break;   // válido → salimos
        } while (true);

        escribirFicha(tablero, i, v);
    }
}

void imprimirTablero(const unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int idx = f * columnas + c;
            cout << SIMBOLO[leerFicha(tablero, idx)] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    srand((unsigned)time(nullptr));

    int filas = 0, columnas = 0;

    cout << "Filas: ";
    cin  >> filas;
    cout << "Columnas: ";
    cin  >> columnas;

    if (filas <= 0 || columnas <= 0) return 1;
    if (filas > 46340 || columnas > 46340) return 1;

    int celdas     = filas * columnas;
    int dimTablero = (celdas * 3 + 7) / 8;   // 3 bits por ficha

    unsigned char* tablero = new unsigned char[dimTablero]();

    rellenarTablero(tablero, filas, columnas);
    imprimirTablero(tablero, filas, columnas);

    delete[] tablero;
    return 0;
}

