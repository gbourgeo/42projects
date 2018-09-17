# IRC
*Ce projet consiste à implémenter un client et un serveur IRC permettant l’échange de messages en réseau TCP/IP.*

## DESCRIPTION
Ce projet consiste à faire un client et un serveur IRC (Internet Relay Chat) qui permettent d’envoyer et recevoir des messages entre plusieurs personnes, au sein de groupes de discussion appelés “channel”. Ils doivent communiquer correctement ensemble.
La communication entre le client et le serveur se fera en TCP/IP (v4 ou v6).

## USAGE
Creating client and server
```
$> make
```
Only client
```
$> make client
$> ./client
Usage: ./client [host_name[:port]] [port]
Welcome to gbourgeos' IRC client
You can type HELP for a list of commands.
...
```
Only server
```
$> make server
$> ./server
Usage: ./server [-v] <port>
	-v		Interactive server.
			It will print info about the server activity.
	<port>		The port that will receive connections.
$> ./server -v 4242
IPv4: Available 127.0.0.1(XXX.XXX.XXX.XXX):4242
IPv6: Unavailable
SERVEUR: Waiting for clients...

```

## SERVER

### Norme
- Respect de la [RFC 2811](https://tools.ietf.org/html/rfc2811), [RFC 2812](https://tools.ietf.org/html/rfc2812).
(exceptions des wildcards)

### Support
- IP v4
- IP v6

### Configuring the Server
- Server configuration file : [irc.conf](https://github.com/gbourgeo/42projects/blob/master/irc/irc.conf).
- Configuration file example: [irc.conf.example](https://github.com/gbourgeo/42projects/blob/master/irc/irc.conf.example).

### Registering to Server
- You need to send your **NICK**, **USER** and optionnaly the **PASS** forms.

```
NICK gbo
USER gilles 0 0 The Almighty
PASS ****
```

### FUNCTIONNALITIES
- **nick <nickname>**               : Implémenter la notion de nickname (un surnom, le login par
                                      défaut, maximum 9 charactères, comme dans la RFC).
- **join <#chan>, leave [#channel], etc...** 
                                    : Implémenter la notion de channel
- **who <user|channel>**            : Qui est loggué ? sur le channel ?
- **msg <nick|channel> <message>**  : Envoi de messages à un utilisateur particulier sur le
                                      serveur ou à un channel.
- **connect <machine> [port]**      : Connexion au serveur depuis le client.
- **away <msg>**                    : Envoi automatique de réponse a des messages privés.
- **help [command]**                : Fourni une aide sur les commandes disponibles et une aide spécifique à
                                      chaque commande.
- **mode <user> <[+|-][aiwroO]>**   : Permet de définir différents mode pour
                                      un utilisateur (invisible, recoit les wallops, etc).
- **mode <channel> <[+|-][Oovamnqpstkl]> [params]**
- **pass <motdepasse>**
- **user <username> <mode> <unused> <real name>**
- **topic <channel> [topic message]**
- **Gestion d'un login/password pour se connecter.**
- Passage du code en mode non-bloquant.
