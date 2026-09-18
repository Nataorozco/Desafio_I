#include <iostream>
#include "bits.h"
#include "azar.h"
#include "tablero.h"
#include "mostrar.h"
#include "combinaciones.h"
#include "eliminacion.h"
#include "cascadas.h"
#include "redimension.h"
#include "estado.h"

using namespace std;

int main() {
    int filas, columnas;

    cout << "=== Sweet Crush ===" << endl;
    cout << "Ingrese numero de filas: ";
    cin >> filas;
    cout << "Ingrese numero de columnas: ";
    cin >> columnas;

    unsigned char* tablero = crearTablero(filas, columnas);
    poblarTablero(tablero, filas, columnas);

    int capacidadBytes = (filas * columnas * 3 + 7) / 8;
    inicializarEstado(filas, columnas);

    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== Tablero actual (" << filas << "x" << columnas << ") ===" << endl;
        mostrarTableroFichas(tablero, filas, columnas);
        cout << "--- vista en bits ---" << endl;
        mostrarTableroBits(tablero, filas, columnas);

        cout << "\n== MENU ==" << endl;
        cout << "1. Eliminar ficha" << endl;
        cout << "2. Eliminar fila" << endl;
        cout << "3. Eliminar columna" << endl;
        cout << "4. Agregar fila" << endl;
        cout << "5. Agregar columna" << endl;
        cout << "6. Ver estado del juego" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int f, c;
            cout << "Fila (0-" << (filas - 1) << "): ";
            cin >> f;
            cout << "Columna (0-" << (columnas - 1) << "): ";
            cin >> c;

            if (f < 0 || f >= filas || c < 0 || c >= columnas) {
                cout << "Posicion invalida." << endl;
                continue;
            }

            int idx = f * columnas + c;
            escribirFicha(tablero, idx, 0);
            registrarEliminacionUsuario();
            compactarYRellenar(tablero, filas, columnas);

            int cascadas = procesarCascadas(tablero, filas, columnas);
            cout << "Cascadas generadas: " << cascadas << endl;

            mostrarEstado();

        } else if (opcion == 2) {
            int pos;
            cout << "Fila a eliminar (0-" << (filas - 1) << "): ";
            cin >> pos;
            if (pos < 0 || pos >= filas || filas <= 1) { cout << "Posicion invalida." << endl; continue; }

            eliminarFila(&tablero, &filas, columnas, &capacidadBytes, pos);
            actualizarDimensiones(filas, columnas);
            procesarCascadas(tablero, filas, columnas);

            mostrarEstado();

        } else if (opcion == 3) {
            int pos;
            cout << "Columna a eliminar (0-" << (columnas - 1) << "): ";
            cin >> pos;
            if (pos < 0 || pos >= columnas || columnas <= 1) { cout << "Posicion invalida." << endl; continue; }

            eliminarColumna(&tablero, filas, &columnas, &capacidadBytes, pos);
            actualizarDimensiones(filas, columnas);
            procesarCascadas(tablero, filas, columnas);

            mostrarEstado();

        } else if (opcion == 4) {
            int pos;
            cout << "Posicion donde insertar la fila (0-" << filas << "): ";
            cin >> pos;
            if (pos < 0 || pos > filas) { cout << "Posicion invalida." << endl; continue; }

            agregarFila(&tablero, &filas, columnas, &capacidadBytes, pos);
            actualizarDimensiones(filas, columnas);
            compactarYRellenar(tablero, filas, columnas);
            procesarCascadas(tablero, filas, columnas);

            mostrarEstado();

        } else if (opcion == 5) {
            int pos;
            cout << "Posicion donde insertar la columna (0-" << columnas << "): ";
            cin >> pos;
            if (pos < 0 || pos > columnas) { cout << "Posicion invalida." << endl; continue; }

            agregarColumna(&tablero, filas, &columnas, &capacidadBytes, pos);
            actualizarDimensiones(filas, columnas);
            compactarYRellenar(tablero, filas, columnas);
            procesarCascadas(tablero, filas, columnas);

            mostrarEstado();

        } else if (opcion == 6) {
            mostrarEstado();

        } else if (opcion != 0) {
            cout << "Opcion invalida." << endl;
        }
    }

    cout << "\n=== Resumen final ===" << endl;
    mostrarEstado();

    liberarTablero(tablero);
    return 0;
}
