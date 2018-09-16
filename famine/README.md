# FAMINE
*Ce projet consiste à coder votre premier virus.*

## The Program
Famine est un binaire qui modifie un ou plusieurs autre(s) binaire(s) pour y appliquer
des fonctionnalités supplémentaires, sans altérer le comportement initial du-dit binaire.
Pour le coup, on se limite à ajouter une "signature" à ce binaire et rien d’autre.
Famine applique cette "signature" à tous les binaires présents dans un dossier
temporaire spécifique.

## SPECIFICITIES
- L’exécutable se nomme Famine.
- L’exécutable est codé en assembleur et en C.
- L’exécutable ne va rien afficher sur la sortie standard ni d’erreur.
- L’exécutable agit sur les dossiers /tmp/test et /tmp/test2.
- Une seule infection sur les binaires est possible.
- Les infections se font sur des binaires 64 bits.
