---
tipo: adr
id: ADR-002
status: Aceptado
fecha: 2026-09-18
dominio: Generación aleatoria
reemplaza:
superado_por:
requisitos_derivados:
  - REQ-generacion-inicial-uniforme
---

## Contexto


El enunciado exige generar las fichas iniciales de forma aleatoria

siguiendo una distribución uniforme, y a la vez prohíbe explícitamente

"sintaxis de ANSI C" (requisito mínimo #2). Al inicio del proyecto,

`rand()`/`srand()` de `<stdlib.h>` fueron descartadas por ser

precisamente eso: funciones heredadas de C, ANSI C puro.


Avanzado el desarrollo, el profesor autorizó verbalmente en clase el uso

de `rand()`, flexibilizando esa restricción. Mi compañero de equipo optó

por adoptar `rand()` a partir de esa autorización. Se evaluó si convenía

hacer lo mismo o mantener la solución ya implementada.

## Decisión

  
Se mantiene el generador propio: un **Generador Congruencial Lineal

(LCG)** con **rejection sampling** para eliminar el sesgo estadístico del

operador módulo, implementado en `azar.cpp`. No se migra a `rand()` pese

a la autorización posterior, por las siguientes razones:
  
1. **`rand() % 6` no resuelve el sesgo estadístico por sí solo.** El

problema de que el módulo introduce una distribución no uniforme

cuando el rango del generador no es múltiplo exacto del número de

categorías (6, en este caso) es independiente de qué generador

subyacente se use. Sustituir el LCG por `rand()` sin agregar rejection

sampling habría heredado el mismo defecto que ya se había corregido.

2. **El LCG demuestra manipulación de bits real**, que es el eje central

del desafío y el 30% de la calificación (uso de máscaras y

desplazamientos). Una llamada a `rand()` es una función de librería

que no aporta a ese criterio, independientemente de si su uso está

permitido.

3. **La solución no depende de una autorización verbal.** El LCG es

válido bajo la lectura más estricta posible del enunciado, sin

necesitar excepciones aclaradas en clase que podrían no quedar

documentadas de forma uniforme para todos los evaluadores en la

sustentación.

4. **Costo de cambio sin beneficio de cumplimiento.** El LCG ya estaba

implementado, probado (validación empírica con 60 000 muestras,

distribución entre 16.55 % y 16.84 % por ficha frente al 16.66 %

ideal) y documentado; migrar a `rand()` no mejora el cumplimiento del

enunciado ni la calidad de la solución, solo introduce una dependencia

de librería adicional.


## Alternativas consideradas

  
- **`rand()`/`srand()` (estándar de C):** descartada originalmente por

violar la restricción de "no ANSI C"; aunque la restricción se

flexibilizó después, se mantiene descartada por las razones 1 y 2

anteriores.

- **`std::mt19937` (`<random>`) o `QRandomGenerator` de Qt:** descartadas

por instanciar clases de librería, lo que viola el requisito #7 (no se

permite `struct`/`class`/`template` ni estructuras suministradas por

bibliotecas), restricción que en ningún momento fue flexibilizada.

## Consecuencias


- El proyecto no depende de ninguna librería externa para la generación

aleatoria, solo aritmética entera propia.

- La corrección del sesgo estadístico queda documentada y demostrada

empíricamente, en vez de asumida.

- La decisión es defendible bajo cualquier interpretación del enunciado,

incluida la más estricta, sin necesitar apoyarse en la autorización

verbal del profesor.

NOTA: **Rejection sampling** 

significa literalmente **“muestreo por rechazo”**. 

En el contexto del  Desafío, sirve para **evitar resultados que no se quieren aceptar** 

cuando se estan generando valores aleatorios.
