# MINITALK 2
*Simple Tchat in terminal using the ncurses library*

![minitalk][minitalk1]

[minitalk1]: https://github.com/gbourgeo/42projects/blob/master/minitalk2/minitalk2.png

### DESCRIPTION
Minitalk2 let you tchat in your terminal the simplest way it can.

### USAGE
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

### SERVER
### Norme
None.
### Support
IPv4
### FUNCTIONNALITIES
None.
## AUTHOR
- gbourgeo
