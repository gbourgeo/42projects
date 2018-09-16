# LEMIPC
*Le projet a pour but d'utiliser les communications inter-processus (IPC), la notion de mémoire partagée (SHM), 
les sémaphores (SEM)... Tout en créant un jeu !*

## Règles du jeu
Le principe est de faire combattre des joueurs (rassemblés en équipes) sur un plateau en 2 dimensions.
- Une équipe gagne le jeu quand elle est la seule restante sur le plateau.
- Lorsqu’un joueur meurt, il disparaît du plateau.
- Pour tuer un joueur, il faut qu’au moins 2 joueurs d’une même équipe adverse soient à son contact,
c’est-à-dire sur une case adjacente à la case où se situe le joueur que l’on veut tuer (y compris en diagonale).
- C’est le joueur qui doit vérifier s’il est entouré avant de bouger. Quand il se rend compte qu’il est entouré
d’au moins 2 joueurs d’une même équipe adverse, il doit quitter le plateau et terminer son exécution.
- Une case du plateau ne peut accueillir qu’un seul joueur à la fois.

### Déplacement des joueurs
Les joueurs se déplacent d’une case à la fois (une case par lock de la map), dans les directions :
haut, bas, droite, gauche (pas de diagonale).
Les déplacements doivent être intelligents. Il faut évidemment poursuivre les joueurs des autres équipes,
tout en essayant de se mettre d’accord sur une proie.

### Taille de plateau
Le plateau peut faire la taille que vous souhaitez, mais doit pouvoir être changée facilement pour la soutenance.
(ex : define)

### Nombre de joueurs
Il n’y a pas de limite au niveau du nombre de joueurs, ni du nombre d’équipes.

## Contraintes techniques
- Chaque client est un processus et il ne doit y avoir qu’un seul exécutable, ce qui implique que le premier joueur
qui démarre crée les ressources partagées (shm, msgq, sémaphores).
- De la même façon, lorsqu’un joueur quitte le jeu, il doit vérifier s’il est le dernier sur le plateau,
car dans ce cas il doit nettoyer tous les IPCs créés par le premier joueur pour éviter qu’ils restent en mémoire
- Le plateau doit être stocké dans un segment de mémoire partagé (SHM). Chaque joueur peut consulter le contenu
du plateau comme il veut, mais pour le modifier il faut respecter les contraintes liées aux ressources
partagées et aux accès concurrentiels (sémaphores).
- C’est le joueur qui doit vérifier s’il est entouré avant de bouger. Quand il se rend compte qu’il est entouré
d’au moins 2 joueurs d’une même équipe adverse, il doit quitter le plateau et terminer son exécution.
- Un joueur ne peut communiquer avec les autres joueurs que par des MSGQ.
- Sur la map, on peut voir si une case est vide ou si elle contient un joueur, et dans ce cas c’est son numéro
d’équipe que l’on voit, et on ne peut pas différencier les joueurs à l’intérieur d’une même équipe.
- Vous devez passer l’équipe en paramètre à l’exécutable.

### Affichage
- seul le premier joueur (celui qui a créé le plateau) affiche le contenu du plateau.
- soit chaque joueur le fait.
- soit un processus spécifique s’en occupe.
