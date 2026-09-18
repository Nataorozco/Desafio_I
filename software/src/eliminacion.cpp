#include "eliminacion.h"
#include "bits.h"

void eliminarMarcadas(unsigned char* tablero, const bool* marcas, int filas, int columnas) {
    int total = filas * columnas;
    for (int idx = 0; idx < total; idx++) {
        if (marcas[idx]) {
            escribirFicha(tablero, idx, 0);
        }
    }
}

void aplicarGravedad(unsigned char* tablero, int filas, int columnas) {
    for (int c = 0; c < columnas; c++) {
        int write = filas - 1;

        for (int read = filas - 1; read >= 0; read--) {
            int idxRead = read * columnas + c;
            unsigned int valor = leerFicha(tablero, idxRead);

            if (valor != 0) {
                if (read != write) {
                    int idxWrite = write * columnas + c;
                    escribirFicha(tablero, idxWrite, valor);
                    escribirFicha(tablero, idxRead, 0);
                }
                write--;
            }
        }

        for (int r = 0; r <= write; r++) {
            escribirFicha(tablero, r * columnas + c, 0);
        }
    }
}

int contarMarcadas(const bool* marcas, int total) {
    int contador = 0;
    for (int i = 0; i < total; i++) {
        if (marcas[i]) contador++;
    }
    return contador;
}
