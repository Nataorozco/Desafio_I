#ifndef ELIMINACION_H
#define ELIMINACION_H

void eliminarMarcadas(unsigned char* tablero, const bool* marcas, int filas, int columnas);
void aplicarGravedad(unsigned char* tablero, int filas, int columnas);
int contarMarcadas(const bool* marcas, int total);

#endif // ELIMINACION_H
