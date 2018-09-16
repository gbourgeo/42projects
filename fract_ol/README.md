# FRACT'OL
*Ce projet consiste à créer graphiquement de jolies fractales.*

## DESCRIPTION
- 3 types de fractales différentes, dont l’ensemble de Julia, l’ensemble de Mandelbrot et Burningship sont présentes.
- Il est possible de faire varier avec la souris (sans clic) le paramètre de l’ensemble de Julia et les autres.
- La molette de la souris permet de zoomer et dézoomer sur la position actuelle de la souris,
et cela de façon quasi infinie (modulo les limites de la machine).
- Un jeu de couleur, pour ressentir la profondeur de chaque fractale, est present.
- Un paramètre est passé en ligne de commande pour définir quel type de fractale est à afficher.
Si il n’y a pas de paramètre fourni, ou si le paramètre est invalide, le programme affiche la liste des paramètres
disponibles et quitte.
- Utilisation la minilibX, dans sa version pour XQuartz installée par défaut.
- Utilisation des images de la minilibX.
- Gérer l’expose correctement.
- La touche ESC permet de quitter le programme.
- En plus du zoom, déplacement avec les flèches.
- Faire tourner la palette de couleur.
- Plein de fractales sympa.
- Deux paramètres valides en ligne de commande, deux fenêtres pour deux fractales.

## USAGE

```
$> make
$> ./fractol
Usage: ./fractol [name1] [name2]
Available names :
- julia
- brain
- mandelbrot
- ship
$>
```
