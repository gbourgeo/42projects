# LIBRARY FORTY TWO
*Personnal C library of usual functions usefull for all other projects.*
## PART 1
- memset
- bzero
- memcpy
- memccpy
- memmove
- memchr
- memcmp
- strlen
- strdup
- strcpy
- strncpy
- strcat
- strncat
- strlcat
- strchr
- strrchr
- strstr
- strnstr
- strcmp
- strncmp
- atoi
- isalpha
- isdigit
- isalnum
- isascii
- isprint
- toupper
- tolower
## PART 2
- ft_memalloc
```
Prototype       void * ft_memalloc(size_t size);
Description     Alloue (avec malloc(3)) et retourne une zone de mémoire
                “fraiche”. La mémoire allouée est initialisée à 0. Si l’allocation
                échoue, la fonction renvoie NULL.
Param. #1       La taille de la zone de mémoire à allouer.
Retour          La zone de mémoire allouée.
Fonctions libc  malloc(3)
```
- ft_memdel
```
Prototype       void ft_memdel(void **ap);
Description     Prend en paramètre l’adresse d’un pointeur dont la zone pointée
                doit être libérée avec free(3), puis le pointeur est mis à
                NULL.
Param. #1       L’adresse d’un pointeur dont il faut libérer la mémoire puis le
                mettre à NULL.
Retour          Rien.
Fonctions libc  free(3).
```

- ft_strnew
```
Prototype       char * ft_strnew(size_t size);
Description     Alloue (avec malloc(3)) et retourne une chaine de caractère
                “fraiche” terminée par un ’\0’. Chaque caractère de la chaine
                est initialisé à ’\0’. Si l’allocation echoue, la fonction renvoie
                NULL.
Param. #1       La taille de la chaine de caractères à allouer.
Retour          La chaine de caractères allouée et initialisée à 0.
Fonctions libc  malloc(3)
```

- ft_strdel
```
Prototype       void ft_strdel(char **as);
Description     Prend en paramètre l’adresse d’une chaine de caractères qui
                doit être libérée avec free(3) et son pointeur mis à NULL.
Param. #1       L’adresse de la chaine de caractère dont il faut libérer la mémoire
                et mettre le pointeur à NULL.
Retour          Rien.
Fonctions libc  Free(3).
```

- ft_strclr
```
Prototype       void ft_strclr(char *s);
Description     Assigne la valeur ’\0’ à tous les caractères de la chaine passée
                en paramètre.
Param. #1       La chaine de caractères à clearer.
Retour          Rien.
Fonctions libc  Aucune.
```

- ft_striter
```
Prototype       void ft_striter(char *s, void (*f)(char *));
Description     Applique la fonction f à chaque caractère de la chaine de
                caractères passée en paramètre. Chaque caractère est passé
                par adresse à la fonction f afin de pouvoir être modifié si
                nécéssaire.
Param. #1       La chaine de caractères sur laquelle itérer.
Param. #2       La fonction à appeler sur chaque caractère de s.
Retour          Rien.
Fonctions libc  Aucune.
```

- ft_striteri
```
Prototype       void ft_striteri(char *s, void (*f)(unsigned int,
char *));
Description     Applique la fonction f à chaque caractère de la chaine de
                caractères passée en paramètre en précisant son index en premier
                argument. Chaque caractère est passé par adresse à la
                fonction f afin de pouvoir être modifié si nécéssaire.
Param. #1       La chaine de caractères sur laquelle itérer.
Param. #2       La fonction à appeler sur chaque caractère de s et son index.
Retour          Rien.
Fonctions libc  Aucune.
```

- ft_strmap
```
Prototype       char * ft_strmap(char const *s, char (*f)(char));
Description     Applique la fonction f à chaque caractère de la chaine de caractères
                passée en paramètre pour créer une nouvelle chaine
                “fraiche” (avec malloc(3)) résultant des applications successives
                de f.
Param. #1       La chaine de caractères sur laquelle itérer.
Param. #2       La fonction à appeler sur chaque caractère de s.
Retour          La chaine “fraiche” résultant des applications successives de f.
Fonctions libc  malloc(3)
```

- ft_strmapi
```
Prototype       char * ft_strmapi(char const *s, char (*f)(unsigned int, char));
Description     Applique la fonction f à chaque caractère de la chaine de
                caractères passée en paramètre en précisant son index pour
                créer une nouvelle chaine “fraiche” (avec malloc(3)) résultant
                des applications successives de f.
Param. #1       La chaine de caractères sur laquelle itérer.
Param. #2       La fonction à appeler sur chaque caractère de s en précisant
                son index.
Retour          La chaine “fraiche” résultant des applications successives de f.
Fonctions libc  malloc(3)
```

- ft_strequ
```
Prototype       int ft_strequ(char const *s1, char const *s2);
Description     Compare lexicographiquement s1 et s2. Si les deux chaines
                sont égales, la fonction retourne 1, ou 0 sinon.
Param. #1       La première des deux chaines à comparer.
Param. #2       La seconde des deux chaines à comparer.
Retour          1 ou 0 selon que les deux chaines sont égales ou non.
Fonctions libc  Aucune.
```

- ft_strsub
```
Prototype       char * ft_strsub(char const *s, unsigned int start, size_t len);
Description     Alloue (avec malloc(3)) et retourne la copie “fraiche” d’un
                tronçon de la chaine de caractères passée en paramètre. Le
                tronçon commence à l’index start et à pour longueur len. Si
                start et len ne désignent pas un tronçon de chaine valide,
                le comportement est indéterminé. Si l’allocation échoue, la
                fonction renvoie NULL.
Param. #1       La chaine de caractères dans laquelle chercher le tronçon à copier.
Param. #2       L’index dans la chaine de caractères où débute le tronçon à copier.
Param. #3       La longueur du tronçon à copier.
Retour          Le tronçon.
Fonctions libc  malloc(3)
```

- ft_strjoin
```
Prototype       char * ft_strjoin(char const *s1, char const *s2);
Description     Alloue (avec malloc(3)) et retourne une chaine de caractères
                “fraiche” terminée par un ’\0’ résultant de la concaténation
                de s1 et s2. Si l’allocation echoue, la fonction renvoie NULL.
Param. #1       La chaine de caractères préfixe.
Param. #2       La chaine de caractères suffixe.
Retour          La chaine de caractère “fraiche” résultant de la concaténation
                des deux chaines.
Fonctions libc  malloc(3)
```

- ft_strtrim
```
Prototype       char * ft_strtrim(char const *s);
Description     Alloue (avec malloc(3)) et retourne une copie de la chaine
                passée en paramètre sans les espaces blancs au debut et à la
                fin de cette chaine. On considère comme espaces blancs les
                caractères ’ ’, ’\n’ et ’\t’. Si s ne contient pas d’espaces
                blancs au début ou à la fin, la fonction renvoie une copie de
                s. Si l’allocation echoue, la fonction renvoie NULL.
Param. #1       La chaine de caractères à trimmer.
Retour          La chaine de caractère “fraiche” trimmée ou bien une copie
                de s sinon.
Fonctions libc  malloc(3)
```

- ft_strsplit
```
Prototype       char ** ft_strsplit(char const *s, char c);
Description     Alloue (avec malloc(3)) et retourne un tableau de chaines de
                caractères “fraiches” (toutes terminées par un ’\0’, le tableau
                également donc) résultant de la découpe de s selon le caractère
                c. Si l’allocation echoue, la fonction retourne NULL. Exemple :
                ft_strsplit("*salut*les***etudiants*", ’*’) renvoie
                le tableau ["salut", "les", "etudiants"].
Param. #1       La chaine de caractères à découper.
Param. #2       Le caractère selon lequel découper la chaine.
Retour          Le tableau de chaines de caractères “fraiches” résultant de la découpe.
Fonctions libc  malloc(3), free(3)
```

- ft_itoa
```
Prototype       char * ft_itoa(int n);
Description     Alloue (avec malloc(3)) et retourne une chaine de caractères
                “fraiche” terminée par un ’\0’ représentant l’entier n passé
                en paramètre. Les nombres négatifs doivent être gérés. Si l’allocation
                échoue, la fonction renvoie NULL.
Param. #1       L’entier à convertir en une chaine de caractères.
Retour          La chaine de caractères représentant l’entier passé en paramètre.
Fonctions libc  malloc(3)
```

- ft_putchar
```
Prototype       void ft_putchar(char c);
Description     Affiche le caractère c sur la sortie standard.
Param. #1       Le caractère à afficher.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putstr
```
Prototype       void ft_putstr(char const *s);
Description     Affiche la chaine s sur la sortie standard.
Param. #1       La chaine de caractères à afficher.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putendl
```
Prototype       void ft_putendl(char const *s);
Description     Affiche la chaine s sur la sortie standard suivi d’un ’\n’.
Param. #1       La chaine de caractères à afficher.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putnbr
```
Prototype       void ft_putnbr(int n);
Description     Affiche l’entier n sur la sortie standard.
Param. #1       L’entier à afficher.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putchar_fd
```
Prototype       void ft_putchar_fd(char c, int fd);
Description     Ecrit le caractère c sur le descripteur de fichier fd.
Param. #1       Le caractères à écrire.
Param. #2       Le descripteur de fichier.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putstr_fd
```
Prototype       void ft_putstr_fd(char const *s, int fd);
Description     Ecrit la chaine s sur le descripteur de fichier fd.
Param. #1       La chaine de caractères à écrire.
Param. #2       Le descripteur de fichier.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putendl_fd
```
Prototype       void ft_putendl_fd(char const *s, int fd);
Description     Ecrit la chaine s sur le descripteur de fichier fd suivi d’un ’\n’.
Param. #1       La chaine de caractères à écrire.
Param. #2       Le descripteur de fichier.
Retour          Rien.
Fonctions libc  write(2).
```

- ft_putnbr_fd
```
Prototype       void ft_putnbr_fd(int n, int fd);
Description     Ecrit l’entier n sur le descripteur de fichier fd.
Param. #1       L’entier à écrire.
Param. #2       Le descripteur de fichier.
Retour          Rien.
Fonctions libc  write(2).
```
