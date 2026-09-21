---
tipo: informe-final
id: INF-002
fecha_entrega: 2026-09-20
autores:
  - Nataly Orozco
proyecto: Sweet Crush (Desafío I)
---
Este es el informe final del desafio, aclarando que ya se habia realizado un informe preliminar, en el inicio cuando me encontraba trabajando con mi compañero Elmer, pero el y yo decidimos separarnos y apartir de ahi adopte algunas de las partes que se habian propuesto en un inicio pero algunas otras las cambie, teniendo en cuenta que ya habiamos aclarado mucha parte de la mecanica del juego y nos habiamos plantedo la division del trabajo, para ser mas claros toda el analisis inicial esta en informe-analisis.


#  decisiones finales 

1. cambio de la ficha 000 que inicialmente Elmer y yo planteamos representarla como un espacio vacio, yo actualmente la reemplace por un punto, porque se me hace mas visual ver un punto ya que un espacio vacio no seria tan perceptible.
2. Inicialmente hablado con mi compañero usar rand() decido cambiarlo por LCG, porque de esta forma no se incumplia con los requisitos y se puede manejar una semilla fija.

# algoritmos implementados

1. Indexacion directa.
2. Ventana de 16 bits.
3. LCG + rejection sampling
4. Escaneo lineal por ranchas
5. Dos punteros (gravedad).
6. Iteracion hasta el punto fijo (cascadas).
7. Reasignacion con umbral.




# problemas de desarrollo enfrentados

1. Confusion inicial entre ANSI C  y clases de libreria: Como restricciones separadas
2. sesgo estadistico: En el generador aleatorio un LCG basico con % 6 no da distribucion uniforme real, se resolvio con rejection sampling que en palabras mas claras es genero un numero y si esta dentro del rango que necesito lo acepto, si esta fuera lo rechazo y genero otro.
3. Bug de rango en el generador: al inicio devolvia 0-5, pero 0 ya significaba posicion vacia y en la codificacion cualquier ficha que saliera como 0 quedaba invisible para la deteccion de combinaciones.
4. Buffer overflow en una prueva propia: esto se nota en el caso offset=7 con un buffer de solo 2 bytes cuando se necesitaban 3, el programa termino en stack smashing el compilador detecto memoria corrupta y forzo el cierre, es aqui donde se nota que la gestion de memoria sin la STL exige verificar muy bien.
5. Problemas de configuracion del CMake/Qt creator, algunos archivos nuevos no aparecian.
6. Cin  no funcionaba correctamente hasta no activar Run en la terminal en la seccion de Run settings del proyecto.
7. Verificacion visual no muy confiable: una combinacion quedo sin resolver por desalineacion de columnas,  se resolvio con una verificacion detectarCombinaciones().
8. Division de trabajo en equipo que luego cambio: el proyecto en un inicio se dividio por dominios con mi compañero, en la fase final se decidio el desarrollo de forma individual, lo que trajo como consecuencia asumir la responsabilidad de todos los modulos.



# evolucion del sistema

Evolucion en la genderacion aleatoria/ aleatoriedad: Durante la implementacion de la generacion de  fichas se analizo como obtener valores pseudoaleatorios que pudieran mapearse a las 6 fichas disponibles, Debido a que el rango de 256 valores no es divisible exacatamente entre 6, se incorporo rejection sampling para detectar los valores que generarian una distribucion sesgada.

En general este sistema de desafio fue evolucionando desde el diseño del tablero hasta la implementacion modular, que  integra el alamcenamiento de fichas, gestion dinamica de memoria y logica del juego.

Se puede  evidenciar que se resolvieron necesidades tecnicas. Tambien se implemento el almacenamiento de cada ficha en 3 bits, incluyendo los casos en los que una ficha cruza la frontera entre dos bytes, se incorporo la la creacion y el redimensionamiento dinamico del tablero, deteccion de combinacion y proceamiento de cascadas.



# evolucion de la solucion 


La solucion fue evolucionando de manera progresiva, comenzando con el diseño de la representacion del tableroy el alamcenamiento de las fichas, despues de esto se implementaron las funciones de la lectura y escritura de las fichas, teniendo en cuenta los casos en los que los bits atraviesan dos bytes.

Posterior a esto se incorporo la gestion  dinamica del tablero, esto permitio crear y redimensionar la memoria segun las dimensiones requeridas. sobre esta base de desarrollo la deteccion  la eliminacion y el procesamiento de cascadas.

Por ultimo se integran la generacion pseudoaleatoria visualizacion de fichas y el menu principal, esto nos da como resultado una soolucion modular donde cada componente cumple una funcion especifica.



NOTA: adjunto link del video-sustentacion  aqui y en el README.


link-video:   https://youtu.be/jp6VcSiAjJk