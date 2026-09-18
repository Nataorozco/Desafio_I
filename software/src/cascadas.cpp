#include "cascadas.h"
#include "bits.h"
#include "azar.h"
#include "combinaciones.h"
#include "eliminacion.h"
#include "estado.h"

void compactarYRellenar(unsigned char* tablero, int filas, int columnas) {
    aplicarGravedad(tablero, filas, columnas);
    int total = filas * columnas;
    for (int idx = 0; idx < total; idx++) {
        if (leerFicha(tablero, idx) == 0) {
            escribirFicha(tablero, idx, siguienteAleatorio());
        }
    }
}

static bool hayAlgunaMarca(const bool* marcas, int total) {
    for (int i = 0; i < total; i++) {
        if (marcas[i]) return true;
    }
    return false;
}

int procesarCascadas(unsigned char* tablero, int filas, int columnas) {
    int total = filas * columnas;
    int contadorCascadas = 0;

    while (true) {
        bool* marcas = detectarCombinaciones(tablero, filas, columnas);

        if (!hayAlgunaMarca(marcas, total)) {
            delete[] marcas;
            break;
        }

        int fichasEliminadas = contarMarcadas(marcas, total);
        int combos = obtenerCombinacionesDetectadas();
        int multiplicador = contadorCascadas + 1;

        eliminarMarcadas(tablero, marcas, filas, columnas);
        delete[] marcas;

        compactarYRellenar(tablero, filas, columnas);

        registrarFichasEliminadas(fichasEliminadas);
        registrarCombinaciones(combos);
        sumarPuntuacion(fichasEliminadas * 10 * multiplicador);

        contadorCascadas++;
    }

    registrarCascadas(contadorCascadas);
    return contadorCascadas;
}
