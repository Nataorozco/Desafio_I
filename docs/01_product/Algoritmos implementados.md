
## 1. Indexación directa (mapeo índice → bit)

No corresponde a un algoritmo de búsqueda o recorrido, sino a un cálculo aritmético de acceso directo en tiempo constante O(1). Dada una posición lógica del tablero (fila, columna), se calcula matemáticamente la ubicación exacta de sus 3 bits dentro del buffer compacto, sin necesidad de recorrer ni comparar nada:

```
índice        = fila × columnas + columna
bit_inicial   = índice × 3
byte          = bit_inicial / 8
offset        = bit_inicial % 8
```

Esta fórmula es la base de todas las operaciones sobre el tablero: localizar, leer y escribir cualquier ficha se reduce a evaluar estas cuatro expresiones y acceder directamente al byte correspondiente. Se usa en `leerFicha()` y `escribirFicha()` (módulo `bits.cpp`), y de forma indirecta en cualquier otro módulo que necesite ubicar una ficha específica.

## 2. Combinación de bytes adyacentes (ventana de 16 bits)

Como cada ficha ocupa exactamente 3 bits y cada byte contiene 8, una ficha puede quedar completamente contenida en un solo byte o repartida entre dos bytes consecutivos. Para resolver ambos casos con una única fórmula, `leerFicha()` construye una ventana temporal de 16 bits combinando el byte actual con el siguiente:

```cpp
unsigned int chunk = (unsigned int)buf[byteIdx];
if (bitOff > 5) {
    chunk |= ((unsigned int)buf[byteIdx + 1]) << 8;
}
return (chunk >> bitOff) & 0x07u;
```

El byte siguiente solo se incorpora cuando el offset indica que la ficha cruza la frontera (`bitOff > 5`). Al desplazar la ventana `bitOff` posiciones y aplicar la máscara `0x07`, los tres bits de la ficha quedan alineados en el resultado sin necesidad de tratar por separado los tres escenarios posibles (ficha contenida en un byte, o repartida 2+1 o 1+2 bits entre dos bytes).

`escribirFicha()` aplica el mismo principio en sentido inverso: construye una máscara con `0x07 << offset`, la invierte con el operador `~` para apagar únicamente los bits objetivo sin alterar los de fichas vecinas que comparten el mismo byte, y luego inserta el valor nuevo con `<<` y `|`.

## 3. Generador Congruencial Lineal (LCG) con rejection sampling

El enunciado exige generación aleatoria con distribución uniforme, sin permitir sintaxis heredada de ANSI C (`rand()`/`srand()`) ni el uso de clases, lo que descarta tanto las funciones clásicas de `<stdlib.h>` como alternativas modernas basadas en clases (`std::mt19937`, `QRandomGenerator`). La solución implementada es un **Generador Congruencial Lineal (LCG)** propio:

```cpp
semilla = (1103515245u * semilla + 12345u) % 2147483648u;
```

Un LCG básico aplicado directamente con `% 6` introduce sesgo estadístico, ya que el rango de valores producido no es múltiplo exacto de 6, favoreciendo a algunas fichas sobre otras. Este problema se corrigió con la técnica de **rejection sampling** (muestreo por rechazo): se acota el valor generado a un rango de 256 posibilidades y se descartan los 4 valores que exceden el mayor múltiplo exacto de 6 dentro de ese rango (252), repitiendo la generación hasta obtener un valor válido. Con esto, cada una de las 6 fichas tiene probabilidad exactamente igual de salir, por diseño matemático y no por aproximación. La distribución resultante se validó empíricamente generando 60 000 valores, con cada ficha apareciendo entre 16.55 % y 16.84 % de las veces (valor ideal: 16.66 %).

## 4. Escaneo lineal por rachas (detección de combinaciones)

La detección de combinaciones horizontales y verticales no requiere un algoritmo de exploración de regiones conectadas (como _flood fill_), dado que el enunciado define una combinación como una línea recta de 3 o más fichas iguales, nunca una forma irregular. Se implementó un **escaneo lineal por rachas**: se recorre cada fila y cada columna comparando cada ficha con la anterior, extendiendo un contador de racha mientras coincidan, y marcando las posiciones correspondientes cuando la racha alcanza 3 o más. Las marcas se almacenan en un arreglo `bool*` reservado dinámicamente, independiente del tablero, lo que permite que una misma ficha quede marcada simultáneamente por una combinación horizontal y una vertical sin conflicto.

## 5. Compactación con dos punteros (gravedad)

La caída de fichas tras una eliminación se resolvió con el patrón clásico de **dos punteros** (_read/write_) aplicado columna por columna: un puntero de lectura recorre la columna de abajo hacia arriba buscando fichas no vacías, y un puntero de escritura avanza únicamente cuando encuentra una, compactando así todas las fichas hacia el fondo de la columna en una sola pasada, sin necesidad de estructuras auxiliares.

## 6. Iteración hasta punto fijo (cascadas)

El procesamiento de cascadas se implementó como una **iteración hasta punto fijo**: se repite el ciclo completo de detectar combinaciones, eliminarlas, aplicar gravedad y rellenar los espacios vacíos, hasta que una pasada no produzca ninguna combinación nueva. Este patrón garantiza que se resuelvan cascadas de cualquier profundidad sin necesidad de conocer de antemano cuántos niveles se van a generar.

## 7. Reasignación de memoria con umbral (redimensionamiento)

Para agregar o eliminar filas y columnas se implementó una **estrategia de reasignación condicionada por umbral**: agregar una posición siempre reserva memoria nueva del tamaño exacto necesario, mientras que eliminar solo reasigna cuando el uso resultante cae por debajo del 65 % de la capacidad actualmente reservada; en caso contrario, los datos se compactan dentro del mismo buffer sin liberar memoria. Esta estrategia es conceptualmente análoga al _growth factor_ que emplean internamente estructuras dinámicas como los contenedores de la STL para amortizar el costo de las reasignaciones, con la diferencia de que aquí se implementó manualmente y se aplica también al achicar la estructura, no solo al crecerla.