---
tipo: vision
id: VA-001
status: Activa
naturaleza: Proyecto académico — juego de consola
---



### **Qué es:**

Un juego de consola en **C++ (desarrollado en el framework Qt, sin sintaxis ANSI C)** denominado **Sweet Crush**, que demuestra el dominio de la **programación estructurada**, **manipulación de bits (bitwise)**, **gestión dinámica de memoria mediante punteros** y **arquitectura modular multi-archivo (`.h` y `.cpp`)**, entregado como la evaluación del **Desafío I** de la asignatura **Informática II** en la Universidad de Antioquia. El sistema administra un tablero dinámico representado internamente por una secuencia continua y compacta de bits, donde cada posición ocupa exactamente **3 bits** sin alineación por bytes.

### **Qué no es:**

* **No es un proyecto de Programación Orientada a Objetos (POO):** Queda estrictamente prohibido el uso de `class`, `struct`, `template`, objetos definidos por el estudiante o librerías de la STL. El paradigma obligatorio es la **programación estructurada**.
* **No utiliza abstracciones de alto nivel:** Está prohibido el uso de objetos como `std::string` o estructuras dinámicas provistas por librerías estándar o externas.
* **No es un juego con interfaz gráfica (GUI):** Es una aplicación para terminal/consola que debe mostrar el tablero en pantalla tanto en **formato binario** como en **formato de fichas** tras cada jugada.
* **No utiliza almacenamiento de 1 byte o 1 entero por ficha:** Cada ficha se empaqueta en 3 bits dentro de un bloque continuo de memoria dinámica (`unsigned char*`), por lo que los bits de una misma ficha pueden quedar repartidos entre dos bytes consecutivos.
* **No permite reservas de memoria estáticas o sobredimensionadas:** La memoria asignada debe corresponder exactamente al tamaño actual del tablero y reajustarse dinámicamente al agregar o eliminar filas y columnas.
* **No usa motores externos (Unity, Unreal, SDL, SFML) ni requiere multijugador en red.**
* **No persigue rendimiento de producción; sí claridad algorítmica y rigor en bajo nivel:** Se evalúa la capacidad de análisis del estudiante, el uso de operadores a nivel de bits (`&`, `|`, `^`, `~`, `<<`, `>>`) y la gestión eficiente de memoria sin delegar lógica a código externo.

## Fuente

Enunciado oficial del Desafío I, Informática II, UdeA.
