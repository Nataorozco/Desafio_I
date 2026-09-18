#include "combinaciones.h"
#include "bits.h"

static int contadorCombinaciones = 0;

bool* detectarCombinaciones(const unsigned char* tablero, int filas, int columnas) {
    contadorCombinaciones = 0;
    int total = filas * columnas;
    bool* marcas = new bool[total];
    for (int i = 0; i < total; i++) marcas[i] = false;

    for (int f = 0; f < filas; f++) {
        int racha = 1;
        for (int c = 1; c <= columnas; c++) {
            bool mismaFicha = false;
            if (c < columnas) {
                int idxActual = f * columnas + c;
                int idxAnterior = f * columnas + (c - 1);
                unsigned int fichaActual = leerFicha(tablero, idxActual);
                unsigned int fichaAnterior = leerFicha(tablero, idxAnterior);
                mismaFicha = (fichaActual == fichaAnterior) && (fichaActual != 0);
            }

            if (mismaFicha) {
                racha++;
            } else {
                if (racha >= 3) {
                    for (int k = c - racha; k < c; k++) {
                        marcas[f * columnas + k] = true;
                    }
                    contadorCombinaciones++;
                }
                racha = 1;
            }
        }
    }

    for (int c = 0; c < columnas; c++) {
        int racha = 1;
        for (int f = 1; f <= filas; f++) {
            bool mismaFicha = false;
            if (f < filas) {
                int idxActual = f * columnas + c;
                int idxAnterior = (f - 1) * columnas + c;
                unsigned int fichaActual = leerFicha(tablero, idxActual);
                unsigned int fichaAnterior = leerFicha(tablero, idxAnterior);
                mismaFicha = (fichaActual == fichaAnterior) && (fichaActual != 0);
            }

            if (mismaFicha) {
                racha++;
            } else {
                if (racha >= 3) {
                    for (int k = f - racha; k < f; k++) {
                        marcas[k * columnas + c] = true;
                    }
                    contadorCombinaciones++;
                }
                racha = 1;
            }
        }
    }

    return marcas;
}

int obtenerCombinacionesDetectadas() {
    return contadorCombinaciones;
}
