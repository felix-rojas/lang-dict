# Filtrador XML de entradas y búsqueda de datos de diccionario

## Respecto al archivo .7z

El archivo comprimido es una pequeña fracción del archivo final. Este lo mantengo en el repositorio dado que no cambiará y es pequeño en comparación a su descomprimido de 300 MB aprox.

## Pasos

1. Descomprima ../res/wiktionaryXfr2010.7z
2. Corra run.sh `./run.sh` 
    1. Compila.
    2. Corre usando los parámetros default en main.
    3. Crea el archivo de definiciones `dict.tsv` y sus palabras `words.txt`

Una vez que haya usado `./run.sh`, escriba `./a [numero de entradas a procesar] [palabra a buscar]`

Ejemplo:

`./a 1000 voler`

Este es un pequeño proyecto para parsear un dump xml de un diccionario en francés provisto por L’Université Toulouse - Jean Jaurès (UT2J) y creado por Franck Sajous sajous@univ-tlse2.fr. 
http://redac.univ-tlse2.fr/lexiques/wiktionaryx.html para descargar.

El programa filtra todas las entradas y adquiere las definiciones de cada una de las palabras conforme las va leyendo del archivo XML.

## Documentación Doxygen

En caso de así desearlo, puede generar la documentación completa de las clases y métodos utilizando el archivo Doxyfile. Utilice `doxygen Doxyfile` para generar una página HTML interactiva con la documentación.

En caso de no desearlo, adjunto un resumen de las funciones y sus tiempos asintóticos en el pdf ./analysis.pdf.

## Videos

Entrega 1: https://youtu.be/ADbiQ10RV3s
Entrega 2: https://youtu.be/6tDQzDSQUdM

## SICT0302B: Toma decisiones

> Selecciona y usa una estructura lineal adecuada al problema

Utilizo una hash table de strings para poder almacenar todos los datos "sin tener que organizarlos". 

> Selecciona un algoritmo de ordenamiento adecuado al problema

La función que me permite "ordenar" es a través de un hash simple del string para generar una llave numérica de acceso. Dado que son palabras, la comparación de cadenas y el hash de las mismas es dependiente de su longitud.

Sacrifico el ordenamiento por un acceso O(n) donde n es el tamaño de la cadena a buscar.

> Usa un árbol adecuado para resolver un problema

## SICT0301B: Evalúa los componentes

> Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa

- Al correr el script test_run.sh se compila el programa para revisar leaks de memoria usando Valgrind.
- En cada uno de los pasos para generar el diccionario se genera una flag para mostrar que se pudo realizar el proceso. 
- Se hacen pruebas de definiciones existentes y no existentes una vez que está cargado el archivo
- Al final de la ejecución se muestran los fallos de las pruebas 

> Hace un análisis de complejidad correcto y completo para todo el programa y sus componentes

- Generé un resumen de la documentación en analysis.pdf.

## SICT0303B: Implementa acciones científicas

> Implementa mecanismos para consultar información de las estructuras correctos y útiles dentro de un programa.

El programa tiene la opción de buscar palabras y definiciones por nombre. Existen 2 opciones de consola, sin argumentos (se cargan 300 datos). 2 argumentos, donde el primero es el número de entradas a pre-procesar y el segundo es la palabra a buscar.

> Implementa mecanismos de lectura de archivos correctos y útiles dentro de un programa.

- Todas las palabras se almacenan en words.txt y sus definiciones correspondientes en dict.tsv
- Filtrado de las entradas del archivo XML

> Implementa mecanismos de escritura de archivos correctos y útiles dentro de un programa. 

- El archivo xml nunca se abre y mientras existan los archivos previos, no se vuelve a realizar el pre-procesado de datos, cargándolos directamente a la memoria. 
