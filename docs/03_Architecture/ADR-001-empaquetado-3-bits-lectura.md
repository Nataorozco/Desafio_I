---
tipo: adr
id: ADR-001
status: Propuesto 
fecha: 2026-09-14
vision_origen: VA-001
dominio: "Empaquetado de bits"
reemplaza:
superado_por:
requisitos_derivados: [REQ-001]
rama: "adr/ADR-001-empaquetado-lectura"
---

# ADR-001 — Lectura de fichas de 3 bits que cruzan fronteras de byte

## Contexto

El buffer es una secuencia continua de bits donde cada ficha ocupa 3 bits consecutivos. Una ficha con `bitPos % 8 >= 6` ocupa bits en `buf[byteIdx]` y en `buf[byteIdx+1]`. Con `malloc`/`realloc` prohibidos y sin `struct` para encapsular, la operación debe ser una función libre que combine dos bytes con máscaras y desplazamientos.

## Decisión

`leerFicha(const unsigned char* buf, int idx)` carga 16 bits consecutivos desde `byteIdx`, desplaza `bitOff` posiciones y enmascara con `0x07`. Solo se carga el byte siguiente cuando `bitOff > 5`.

```cpp
unsigned int leerFicha(const unsigned char* buf, int idx) {
    long long bitPos = (long long)idx * 3;
    int byteIdx = (int)(bitPos >> 3);
    int bitOff  = (int)(bitPos & 7);

    unsigned int chunk = (unsigned int)buf[byteIdx];
    if (bitOff > 5) {
        chunk |= ((unsigned int)buf[byteIdx + 1]) << 8;
    }
    return (chunk >> bitOff) & 0x07u;
}



void escribirFicha(unsigned char* buf, int idx, unsigned int valor) {
    long long bitPos = (long long)idx * 3;
    int byteIdx = (int)(bitPos >> 3);
    int bitOff  = (int)(bitPos & 7);

    valor &= 0x07u;  // aseguramos solo 3 bits

    // Máscara para los bits que vamos a modificar
    unsigned int mask = 0x07u << bitOff;

    // Reconstruimos el chunk de 16 bits de la misma forma que en leerFicha
    unsigned int chunk = (unsigned int)buf[byteIdx];
    if (bitOff > 5) {
        chunk |= ((unsigned int)buf[byteIdx + 1]) << 8;
    }

    // Limpiamos los 3 bits objetivo y colocamos el nuevo valor
    chunk = (chunk & ~mask) | (valor << bitOff);

    // Escribimos de vuelta los bytes afectados
    buf[byteIdx] = (unsigned char)(chunk & 0xFF);
    if (bitOff > 5) {
        buf[byteIdx + 1] = (unsigned char)((chunk >> 8) & 0xFF);
    }
}



```

