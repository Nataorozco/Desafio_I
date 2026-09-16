#include "azar.h"

static unsigned int semilla = 123456789u;

unsigned int siguienteAleatorio() {
    semilla = (1103515245u * semilla + 12345u) % 2147483648u;
    return (semilla / 65536u) % 6u;
}
