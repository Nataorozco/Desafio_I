---
tipo: dominio
dominio: "Empaquetado de bits"
status: Delimitado
vision_origen: VA-001
---

# Dominio: Empaquetado de bits

## Qué es

Todo lo relativo a leer y escribir fichas de 3 bits en un buffer continuo `unsigned char*` sin alineación por byte, incluyendo el caso de fichas que cruzan fronteras entre bytes consecutivos.

## Qué no es

- No cubre el contenido semántico de las fichas (eso pertenece a `reglas-juego`).
- No cubre el redimensionamiento del buffer (eso pertenece a `memoria-y-estado`).
- No cubre cómo se imprimen (eso pertenece a `interaccion-terminal`).
