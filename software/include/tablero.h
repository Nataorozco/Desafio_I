#ifndef TABLERO_H
#define TABLERO_H

unsigned char* crearTablero(int filas, int columnas);
void liberarTablero(unsigned char* tablero);
void poblarTablero(unsigned char* tablero, int filas, int columnas);

#endif // TABLERO_H
