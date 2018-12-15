# Fillit
*C’est l’histoire d’une pièce de Tetris, d’un petit carré et d’un(e) dev qui entrent dans un bar..*

## Résumé
Fillit est un projet vous permettant de decouvrir et/ou de vous familiariser avec une problematique récurrente
en programmation : la recherche d’une solution optimale parmi un très grand nombre de possibilités, 
dans un délai raisonable. Dans le cas de ce projet, il s’agira d’agencer des Tetriminos entre eux et de déterminer 
le plus petit carré possible pouvant les acueillir.
Un Tetriminos est une figure géométrique formée de 4 blocs que vous connaissez grâce au célèbre jeu Tetris.

## The Program

L'exécutable doit prendre en paramètre un (et un seul) fichier décrivant la liste
des Tetriminos à agencer. Ce fichier est formaté de façon très précise : chaque description
d’un Tetriminos est sur 4 lignes et deux Tetriminos sont séparés par une ligne vide.

La description d’un Tetrimino doit respecter les règles suivantes :

+ Exactement 4 lignes de 4 caractères suivis d’un retour à la ligne.
+ Un Tetriminos est une pièce de Tetris classique composée de 4 blocs.
+ Chaque caractère doit être, soit un ’#’ lorsque la case correspond à l’un des 4
blocs d’un Tetriminos, soit un ’.’ lorsque la case est vide.
+ Chaque bloc d’un Tetriminos doit être en contact avec au moins un autre bloc
sur l’un ou l’autre de ses 4 côtés.

Quelques exemples de descriptions de Tetriminos valides :
```
....  ....  ####  ....  .##.  ....  .#..  ....  ....
..##  ....  ....  ....  ..##  .##.  ###.  ##..  .##.
..#.  ..##  ....  ##..  ....  ##..  ....  #...  ..#.
..#.  ..##  ....  ##..  ....  ....  ....  #...  ..#.
```

Quelques exemples de descriptions de Tetriminos invalides :
```
####  ...#  ##...  #.    ....  ..##  ####  ,,,,  .HH.
...#  ..#.  ##...  ##    ....  ....  ####  ####  HH..
....  .#..  ....   #.    ....  ....  ####  ,,,,  ....
....  #...  ....   ....  ##..  ####  ,,,,  ....
```

## The Output

Votre programme doit afficher le plus petit carré solution sur la sortie standard. Pour
pouvoir identifier chaque Tetriminos dans le carré solution, vous assignerez une lettre
majuscule (en commencant avec ’A’) à ce Tetriminos dans l’ordre où ils apparaissent
dans le fichier de description.
Si le fichier de description comporte au moins une erreur, votre programme doit afficher
error sur la sortie standard et quitter proprement.

```sh
$> cat sample.fillit | cat -e
....$
##..$
.#..$
.#..$
$
....$
####$
....$
....$
$
#...$
###.$
....$
....$
$
....$
##..$
.##.$
....$
$> ./fillit sample.fillit | cat -e
DDAA$
CDDA$
CCCA$
BBBB$
$>
```

```
$> cat sample.fillit | cat -e
....$
....$
####$
....$
$
....$
...$
..##$
..##$
$> ./fillit sample.fillit | cat -e
error$
$>
```
