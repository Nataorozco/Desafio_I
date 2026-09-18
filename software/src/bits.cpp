#include "bits.h"

unsigned int leerFicha(const unsigned char* buf, int idx) {
    int bitInicial = idx * 3;
    int byteIdx = bitInicial / 8;
    int offset  = bitInicial % 8;

    // Combinamos byte actual + byte siguiente en un contenedor de 16 bits
    unsigned int chunk = (unsigned int)buf[byteIdx];
    if (offset > 5) {
        chunk |= ((unsigned int)buf[byteIdx + 1]) << 8;
    }

    return (chunk >> offset) & 0x07u;
}

void escribirFicha(unsigned char* buf, int idx, unsigned int valor) {
    int bitInicial = idx * 3;
    int byteIdx = bitInicial / 8;
    int offset  = bitInicial % 8;

    valor &= 0x07u;  // aseguramos que solo se usen 3 bits

    // Paso 1: limpiar e insertar en el primer byte
    unsigned char mask1 = (unsigned char)(0x07u << offset);
    buf[byteIdx] = (buf[byteIdx] & ~mask1) | (unsigned char)(valor << offset);

    // Paso 2: si la ficha cruza al siguiente byte, completar ahí
    if (offset > 5) {
        int bitsEnByte2 = offset - 5;  // 1 si offset=6, 2 si offset=7
        unsigned char mask2 = (unsigned char)(0x07u >> (3 - bitsEnByte2));
        buf[byteIdx + 1] = (buf[byteIdx + 1] & ~mask2)
                           | (unsigned char)(valor >> (8 - offset));
    }
}
