# lang-dict

This is a small project to parse an xml french dictionary file provided by L’Université Toulouse - Jean Jaurès (UT2J)
The dictionary file was created by (Franck Sajous) [sajous@univ-tlse2.fr] and is available (here) [http://redac.univ-tlse2.fr/lexiques/wiktionaryx.html] for download.

## Objective

To sort the file and its entries in different forms using basic data structures and algorithms.
As of now, this program uses regex expressions to parse the opening and closing xml statements to dump them in a csv file for sorting.

## Regarding the 7z file

The included 7z file is the compressed form of the xml file, which is quite large for versioning. I have decided to add only the compressed file for backup purposes as it will not change. 
With that in mind however, be careful when extracting the 7z because it is *300 MB heavy*.


