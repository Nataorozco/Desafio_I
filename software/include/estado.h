#ifndef ESTADO_H
#define ESTADO_H

void inicializarEstado(int filas, int columnas);
void actualizarDimensiones(int filas, int columnas);
void registrarEliminacionUsuario();
void registrarFichasEliminadas(int cantidad);
void registrarCombinaciones(int cantidad);
void registrarCascadas(int cantidad);
void sumarPuntuacion(int puntos);
void mostrarEstado();

#endif // ESTADO_H
