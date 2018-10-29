# MINITALK
*Simple Tchat in terminal*

## DESCRIPTION
Minitalk let you tchat in your terminal the simplest way it can.
The server do not handle any command, except the /USER at start to authentify yourself, so your friends know who they are talkin with.
Nothing more.

## USAGE
**Make** generates a single executable that handles both *server* and *client* :
```
$> make
$> ./minitalk
Server:
	./minitalk -l [port]
Client:
	./minitalk [target ip] [port]
```
- The **-l** option create the *server* and a *client*.
- The other try to connect to the *server*.
- Change your username by modifying the $USER environnement variable.

## SERVER
### Norme
None.
### Support
IPv4
### FUNCTIONNALITIES
None.
## AUTHOR
- gbourgeo
