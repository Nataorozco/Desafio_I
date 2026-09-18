#include "redimension.h"
#include "bits.h"

static int calcularBytesNecesarios(int filas, int columnas) {
    int totalBits = filas * columnas * 3;
    return (totalBits + 7) / 8;
}

void agregarFila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    int nuevoFilas = *filas + 1;
    int nuevoBytes = calcularBytesNecesarios(nuevoFilas, columnas);

    unsigned char* nuevo = new unsigned char[nuevoBytes];
    for (int i = 0; i < nuevoBytes; i++) nuevo[i] = 0;

    for (int f = 0; f < nuevoFilas; f++) {
        for (int c = 0; c < columnas; c++) {
            int idxNuevo = f * columnas + c;
            if (f < posicion) {
                int idxViejo = f * columnas + c;
                escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
            } else if (f > posicion) {
                int idxViejo = (f - 1) * columnas + c;
                escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
            }
            // f == posicion: fila nueva, queda vacia (0), ya inicializada
        }
    }

    delete[] *tablero;
    *tablero = nuevo;
    *filas = nuevoFilas;
    *capacidadBytes = nuevoBytes;
}

void eliminarFila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion) {
    int nuevoFilas = *filas - 1;
    int bytesNecesarios = calcularBytesNecesarios(nuevoFilas, columnas);
    int totalViejo = (*filas) * columnas;

    double uso = (double)bytesNecesarios / (double)(*capacidadBytes);

    if (uso < 0.65) {
        // Uso cae debajo del 65%: reasignamos a un buffer del tamano exacto
        unsigned char* nuevo = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) nuevo[i] = 0;

        int idxNuevo = 0;
        for (int idxViejo = 0; idxViejo < totalViejo; idxViejo++) {
            if ((idxViejo / columnas) == posicion) continue;
            escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
            idxNuevo++;
        }

        delete[] *tablero;
        *tablero = nuevo;
        *capacidadBytes = bytesNecesarios;
    } else {
        // Uso sigue >= 65%: compactamos DENTRO del mismo buffer, sin reasignar
        int idxNuevo = 0;
        for (int idxViejo = 0; idxViejo < totalViejo; idxViejo++) {
            if ((idxViejo / columnas) == posicion) continue;
            unsigned int valor = leerFicha(*tablero, idxViejo);
            escribirFicha(*tablero, idxNuevo, valor);
            idxNuevo++;
        }
        // Limpiamos el resto (bits que ya no representan fichas validas)
        for (int idx = idxNuevo; idx < totalViejo; idx++) {
            escribirFicha(*tablero, idx, 0);
        }
    }

    *filas = nuevoFilas;
}

void agregarColumna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    int viejoColumnas = *columnas;
    int nuevoColumnas = viejoColumnas + 1;
    int nuevoBytes = calcularBytesNecesarios(filas, nuevoColumnas);

    unsigned char* nuevo = new unsigned char[nuevoBytes];
    for (int i = 0; i < nuevoBytes; i++) nuevo[i] = 0;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < nuevoColumnas; c++) {
            int idxNuevo = f * nuevoColumnas + c;
            if (c < posicion) {
                int idxViejo = f * viejoColumnas + c;
                escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
            } else if (c > posicion) {
                int idxViejo = f * viejoColumnas + (c - 1);
                escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
            }
            // c == posicion: columna nueva, queda vacia (0)
        }
    }

    delete[] *tablero;
    *tablero = nuevo;
    *columnas = nuevoColumnas;
    *capacidadBytes = nuevoBytes;
}

void eliminarColumna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion) {
    int viejoColumnas = *columnas;
    int nuevoColumnas = viejoColumnas - 1;
    int bytesNecesarios = calcularBytesNecesarios(filas, nuevoColumnas);

    double uso = (double)bytesNecesarios / (double)(*capacidadBytes);

    if (uso < 0.65) {
        unsigned char* nuevo = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) nuevo[i] = 0;

        int idxNuevo = 0;
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < viejoColumnas; c++) {
                if (c == posicion) continue;
                int idxViejo = f * viejoColumnas + c;
                escribirFicha(nuevo, idxNuevo, leerFicha(*tablero, idxViejo));
                idxNuevo++;
            }
        }

        delete[] *tablero;
        *tablero = nuevo;
        *capacidadBytes = bytesNecesarios;
    } else {
        int idxNuevo = 0;
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < viejoColumnas; c++) {
                if (c == posicion) continue;
                int idxViejo = f * viejoColumnas + c;
                unsigned int valor = leerFicha(*tablero, idxViejo);
                escribirFicha(*tablero, idxNuevo, valor);
                idxNuevo++;
            }
        }
        int totalViejo = filas * viejoColumnas;
        for (int idx = idxNuevo; idx < totalViejo; idx++) {
            escribirFicha(*tablero, idx, 0);
        }
    }

    *columnas = nuevoColumnas;
}
