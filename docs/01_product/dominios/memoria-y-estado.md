---
tipo: dominio
dominio: "Memoria y estado"
status: Delimitado
vision_origen: VA-001
---

# Dominio: Memoria y estado

## Qué es

Gestión dinámica del buffer del tablero: asignación exacta, liberación, redimensionamiento, y la representación del estado global del juego sin `struct` ni `class` (variables globales).

## Qué no es

- No cubre el algoritmo de empaquetado de 3 bits (eso pertenece a `empaquetado-bits`).
- No cubre reglas de juego ni renderizado.
