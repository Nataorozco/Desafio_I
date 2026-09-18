#include "azar.h"

static unsigned int semilla = 123456789u;

unsigned int siguienteAleatorio() {
    unsigned int valor;
    const unsigned int limite = 256u - (256u % 6u);

    do {
        semilla = (1103515245u * semilla + 12345u) % 2147483648u;
        valor = (semilla / 65536u) % 256u;
    } while (valor >= limite);

    return (valor % 6u) + 1u;  // ahora entrega 1-6, dejando 0 exclusivo para "vacio"
}
