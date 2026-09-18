#include "estado.h"
#include <iostream>
using namespace std;

static int estadoFilas = 0;
static int estadoColumnas = 0;
static int estadoEliminaciones = 0;
static int estadoFichasEliminadas = 0;
static int estadoCombinaciones = 0;
static int estadoCascadasActual = 0;
static int estadoPuntuacion = 0;

void inicializarEstado(int filas, int columnas) {
    estadoFilas = filas;
    estadoColumnas = columnas;
    estadoEliminaciones = 0;
    estadoFichasEliminadas = 0;
    estadoCombinaciones = 0;
    estadoCascadasActual = 0;
    estadoPuntuacion = 0;
}

void actualizarDimensiones(int filas, int columnas) {
    estadoFilas = filas;
    estadoColumnas = columnas;
}

void registrarEliminacionUsuario() {
    estadoEliminaciones++;
}

void registrarFichasEliminadas(int cantidad) {
    estadoFichasEliminadas += cantidad;
}

void registrarCombinaciones(int cantidad) {
    estadoCombinaciones += cantidad;
}

void registrarCascadas(int cantidad) {
    estadoCascadasActual = cantidad;
}

void sumarPuntuacion(int puntos) {
    estadoPuntuacion += puntos;
}

void mostrarEstado() {
    cout << "\n=== Estado del juego ===" << endl;
    cout << "Dimensiones: " << estadoFilas << "x" << estadoColumnas << endl;
    cout << "Eliminaciones realizadas por el usuario: " << estadoEliminaciones << endl;
    cout << "Fichas eliminadas (total): " << estadoFichasEliminadas << endl;
    cout << "Combinaciones detectadas: " << estadoCombinaciones << endl;
    cout << "Cascadas (ultima eliminacion): " << estadoCascadasActual << endl;
    cout << "Puntuacion: " << estadoPuntuacion << endl;
}
