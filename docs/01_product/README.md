# Sweet Crush — Desafío I (Informática II, 2026-2)

Implementación de un juego tipo match-3 (Sweet Crush) en C++, con el tablero almacenado como una secuencia compacta de bits (3 bits por ficha) en memoria dinámica gestionada manualmente, sin STL, sin `struct`/`class`/`template`, y sin sintaxis de ANSI C.

## Estructura del repositorio

```
docs/
  00_inbox/          Notas de trabajo, reuniones, decisiones en borrador
  01_product/        Descripción del juego, codificación de fichas,
                      esquema de tareas, algoritmos implementados,
                      informe de análisis
  02_Requirements/    Requisitos derivados del enunciado
  03_Architecture/    ADRs (Architecture Decision Records) — decisiones
                      de diseño con su contexto y justificación
  _Archive/          Documentos de versiones anteriores, conservados
                      como historial

software/
  include/           Cabeceras (.h) de cada módulo
  src/               Implementación (.cpp) de cada módulo
  main.cpp           Punto de entrada — menú y ciclo de juego
  CMakeLists.txt     Configuración de build
```

## Módulos del código (`software/`)

|Módulo|Responsabilidad|
|---|---|
|`bits`|Leer/escribir una ficha de 3 bits dentro del buffer compacto|
|`azar`|Generador aleatorio propio (LCG + rejection sampling)|
|`tablero`|Crear, poblar y liberar el tablero|
|`mostrar`|Visualización del tablero (vista de fichas + vista de bits)|
|`combinaciones`|Detección de combinaciones horizontales y verticales|
|`eliminacion`|Vaciar fichas marcadas y aplicar gravedad|
|`cascadas`|Orquesta el ciclo detectar→eliminar→gravedad→rellenar|
|`redimension`|Agregar/eliminar fila o columna, con la regla del 65%|
|`estado`|Contadores del estado del juego (dimensiones, eliminaciones, puntuación, etc.)|

Ningún módulo aparte de `bits` manipula bits directamente — todos pasan por `leerFicha()`/`escribirFicha()`.

## Cómo compilar y ejecutar

Requiere CMake 3.16+ y un compilador con soporte C++17.

```bash
cd software
mkdir -p build && cd build
cmake ..
cmake --build .
./Desafio_I
```

También se puede abrir `software/CMakeLists.txt` directamente en Qt Creator y ejecutar desde ahí (recomendado activar "Run in terminal" en las opciones de ejecución del proyecto, para que la entrada por consola funcione correctamente).

## Restricciones cumplidas

- Sin `struct`, `class`, `template`, ni objetos definidos por el estudiante.
- Sin STL.
- Sin sintaxis de ANSI C (`rand()`, `malloc()`, etc.).
- Memoria dinámica gestionada con `new`/`delete`, dimensionada exactamente según las dimensiones actuales del tablero — nunca sobredimensionada.

NOTA:  se adjunta link del video.


Link del video:    https://youtu.be/jp6VcSiAjJk