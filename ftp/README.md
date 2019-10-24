# FTP
*Ce projet consiste à implémenter un client et un serveur FTP (File Transfert Protocol) permettant le transfert de fichier en réseau TCP/IP.
La communication entre le client et le serveur se fera en TCP/IP (version 4).*

## USAGE
### Create the server
```sh
$> make server
$> ./server
Usage: ./server [port] [-i] (for interactive server)
$>
```
### Create the client
```sh
$> make client
$> ./client
Usage: ./client [server_address] [server_port]
$>
```
### Create the server and the client
```sh
$> make
$>
```

## Design
- Un prompt spécifique au client (pour le distinguer du Shell).
- Impossibilité de descendre à un niveau inférieur au répertoire d’exécution du serveur.
- Affichage sur le client des messages SUCCESS ou ERROR + explication après chaque requête.

## Commands
Those commands operate on the server side:
```
- ls [-all]   : liste le répertoire courant du serveur
- cd          : change le répertoire courant du serveur
- pwd         : affiche le chemin du répertoire courant sur le serveur
- get [file]  : récupère le fichier _file_ du serveur vers le client
- put [file]  : envoi le fichier _file_ du client vers le serveur
- mkdir [-pv] : cree un dossier
- rmdir       : supprime un dossier recursivement
- unlink      : supprime un fichier
- quit        : coupe la connection + sort du programme
```

Those commands operate on the client local system:
```
- lls
- lcd
- lpwd
- ...
- mget [dir]  : comme get mais “multiple” et pour les dossiers
- mput [dir]  : comme put mais “multiple” et pour les dossiers
```

### Bonus
- respect de la RFC (standard 9 ou rfc 959)
- support de l’IPv6
