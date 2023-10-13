# lang-dict

This is a small project to parse an xml french dictionary file provided by L’Université Toulouse - Jean Jaurès (UT2J)
The dictionary file was created by Franck Sajous sajous@univ-tlse2.fr and is available here http://redac.univ-tlse2.fr/lexiques/wiktionaryx.html for download.

## Objective

To sort the file and its entries in different forms using basic data structures and algorithms.
As of now, this program uses regex expressions to parse the opening and closing xml statements to dump them in a csv file for sorting.

## Regarding the 7z file

The included 7z file is the compressed form of the xml file, which is quite large for versioning. I have decided to add only the compressed file for backup purposes as it will not change. 
With that in mind however, be careful when extracting the 7z because it is *300 MB heavy*.

## Steps

1. Run run.sh `./run.sh`. This will: 
    1. Compile the program.
    2. Run the program using the default parameters.
    3. Creates a file of definitions `dict.tsv` and sample words `words.txt`
2. Type any word from `words.txt` and it will return its definition and exit.

OR once youve run `./run.sh`, simply type `./a [number of entries] [word to look for]`

Example: 
`./a 1000 voler`

## Video

https://youtu.be/ADbiQ10RV3s

## SICT0302B: Toma decisiones
> Selecciona y usa una estructura lineal adecuada al problema

Este problema requiere filtrar datos de manera rápida, por lo que uso expresiones regex para encontrar las tags XML y cargar el contenido para procesar la información contenida.

Utilizo un Vector, pues se requiere de una estructura que crezca de manera dinámica para determinar el número de elementos a cargar y las definiciones las cargo a un archivo para no tenerlas en memoria dinámica.

Almaceno cadenas de texto de definiciones en un archivo para no llenar la memoria RAM, puesto que son miles de miles de entradas


## SICT0301B: Evalúa los componentes
> Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa

El programa genera una lista de todas las palabras disponibles a definir y el script por default `run.sh` genera la lista de palabras y definiciones `dict.tsv` & `words.txt`.

El programa acepta argumentos una vez compilado, el número de palabras a filtrar y la palabra a buscar

La corrida por default pide una palabra a buscar y filtra 100 palabras.

## SICT0303B: Implementa acciones científicas
> Implementa mecanismos para consultar información de las estructuras correctos y útiles dentro de un programa.

- Uso de regex para filtrar palabras con ayuda de la librería std para reducción de autómatas
- Uso de array dinámico (vector) para guardar las palabras a buscar 
- Estructuración de definiciones con índices para disminuir tiempos de búsqueda en el archivo
