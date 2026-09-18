Usar el algomitmo de Bloder para dectar la ficha

Nota: Aqui se hace un cambio del contexto de 
uso de este algoritmo.

Operaciones para mover la ficha:

índice = fila × columnas + columna 
bit_inicial = índice × 3 
byte = bit_inicial / 8 
offset = bit_inicial % 8

## 1. Indexación directa (mapeo índice → bit)

No corresponde a un algoritmo de búsqueda o recorrido, sino a un cálculo aritmético de acceso directo en tiempo constante O(1). Dada una posición lógica del tablero (fila, columna), se calcula matemáticamente la ubicación exacta de sus 3 bits dentro del buffer compacto, sin necesidad de recorrer ni comparar nada:

```
índice        = fila × columnas + columna
bit_inicial   = índice × 3
byte          = bit_inicial / 8
offset        = bit_inicial % 8
```

Esta fórmula es la base de todas las operaciones sobre el tablero: localizar, leer y escribir cualquier ficha se reduce a evaluar estas cuatro expresiones y acceder directamente al byte correspondiente. Se usa en `leerFicha()` y `escribirFicha()` (módulo `bits.cpp`), y de forma indirecta en cualquier otro módulo que necesite ubicar una ficha específica.


