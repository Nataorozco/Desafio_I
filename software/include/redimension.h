#ifndef REDIMENSION_H
#define REDIMENSION_H

void agregarFila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion);
void eliminarFila(unsigned char** tablero, int* filas, int columnas, int* capacidadBytes, int posicion);

void agregarColumna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion);
void eliminarColumna(unsigned char** tablero, int filas, int* columnas, int* capacidadBytes, int posicion);

#endif // REDIMENSION_H
