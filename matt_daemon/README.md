# Matt Daemon
*Ce projet constitue une introduction au concept de daemon.*

Ce petit programme a pour fonction de traiter et stocker les messages reçus sur un port spécifique, 
ouvert par ce daemon justement.

## The Program
* Le programme va se lancer uniquement avec les droits root.
* Votre programme devra s’exécuter en tâche de fond à la façon d’un vrai daemon.
* Le daemon va devoir écouter sur le port 4242.
* Tout ce que le daemon fait doit être visible dans un fichier de log matt_daemon.log
avec timestamp (sous la forme [ DD / MM / YYYY - HH : MM : SS]) situé dans
le dossier /var/log/matt_daemon/.
* Une seule instance du daemon doit pouvoir être lancée.
* Un fichier matt_daemon.lock doit être créé dans /var/lock/ au lancement du daemon.
* À la fermeture du daemon le fichier matt_daemon.lock doit être effacé.
* La fermeture du programme doit se faire par l’envoi d’une simple chaîne de caractère
"quit" sur le socket ouvert.
* Toute autre chaîne de caractère doit être inscrite dans le fichier de log.
* Seuls 3 clients peuvent se connecter en simultané sur le daemon.
* Lorsque le daemon reçoit un signal, il doit l’intercepter et l’inscrire dans le fichier
matt_daemon.log avec un message explicite, puis quitter proprement.

### BONUS
* Créer un client graphique pour interagir avec le daemon (Qt 5.9.1 a été mon choix).
* Ajouter des fonctions utilitaires à votre daemon:
```
    "daemonlogs"    "Prints the Daemon log file."
    "daemoninfo"    "Shows informations about the Daemon itself."
    "daemonpass"    "Changes the Daemon protection status."
                    "TRUE with an argument (will be the new password)."
                    "FALSE with no argument."
    "daemoncrypt"   "Changes the Daemon messages status."
    "machinfo"      "Gives informations about the machine the Daemon"
                    "is running on."
    "servinfo"      "Gives informations about the services of the"
                    "machine the Daemon is runing on."
    "clearlogs"     "Clears the Daemon log file."
    "mail"          "Sends an email with informations related to the"
                    "parameters given (daemonlogs, machinfo, ..., all)."
    "quit"          "Shutdown the Daemon."
```
* Chiffrer l’envoi et la réception des données (simple Base64 pour encoder et decoder).
* Envoi de mail suivant des règles de filtrages choisis.
* Créer un système d’authentification pour se connecter au daemon (via client graphique).

## Dependencies

* Pour le client graphique, installez Qt 5.9.1

[Download Qt 5.9.1](https://download.qt.io/archive/qt/5.9/5.9.1/)

* Pour l'envoi de mail, installez openssl
```
apt-get install openssl-dev
```

## Installation
* Client and Server
```
    $> make
```
* Client
```
    $> make client
```
* Server
```
    $> make server
```

## Usage
* Le server se lance sans arguments, en tache de fond automatiquement.
```
    $> ./Matt_daemon
    $> 
```
* Le client se lance egalement sans argument.
```
    $> ./Ben_AFK
    
```
![alt text](http://github.com/gbourgeo/42projects/blob/master/matt_daemon/Common/ben_afk.png)

## Information

Un démon est un processus de service qui s'exécute en arrière-plan et supervise le système ou fournit des fonctionnalités à d'autres processus. 
Ce daemon reprends les pre-requis des daemons sysV:

1.  Close all open file descriptors except standard input, output, and error (i.e. the first three file descriptors 0,1,2). 
    This ensures that no accidentally passed file descriptor stays around in the daemon process. 
    On Linux, this is best implemented by iterating through /proc/self/fd, with a fallback of iterating from file descriptor 
    3 to the value returned by getrlimit() for RLIMIT_NOFILE.
2.  Reset all signal handlers to their default. 
    This is best done by iterating through the available signals up to the limit of _NSIG and resetting them to SIG_DFL.
3.  Reset the signal mask using sigprocmask().
4.  Sanitize the environment block, removing or resetting environment variables that might negatively impact daemon runtime.
5.  Call fork(), to create a background process.
6.  In the child, call setsid() to detach from any terminal and create an independent session.
7.  In the child, call fork() again, to ensure that the daemon can never re-acquire a terminal again.
8.  Call exit() in the first child, so that only the second child (the actual daemon process) stays around. 
    This ensures that the daemon process is re-parented to init/PID 1, as all daemons should be.
9.  In the daemon process, connect /dev/null to standard input, output, and error.
10. In the daemon process, reset the umask to 0, so that the file modes passed to open(), mkdir() and suchlike directly 
    control the access mode of the created files and directories.
11. In the daemon process, change the current directory to the root directory (/), in order to avoid that the daemon 
    involuntarily blocks mount points from being unmounted.
12. In the daemon process, write the daemon PID (as returned by getpid()) to a PID file, for example /run/foobar.pid 
    (for a hypothetical daemon "foobar") to ensure that the daemon cannot be started more than once. 
    This must be implemented in race-free fashion so that the PID file is only updated when it is verified at the same 
    time that the PID previously stored in the PID file no longer exists or belongs to a foreign process.
13. In the daemon process, drop privileges, if possible and applicable.
14. From the daemon process, notify the original process started that initialization is complete. 
    This can be implemented via an unnamed pipe or similar communication channel that is created before the first fork() 
    and hence available in both the original and the daemon process.
15. Call exit() in the original process. The process that invoked the daemon must be able to rely on that this exit() 
    happens after initialization is complete and all external communication channels are established and accessible.
