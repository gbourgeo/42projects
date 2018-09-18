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
- **AWAY [\<message\>]**
	```
	Without an argument, it will set you back.  With an argument,
	it will set you as AWAY with the specified message.
	```
- **CONNECT <_host_> [\<port\>]**
	```
	Request the server to establish a connection to <host>.
	It is only available to FT_IRC Operators.
	```
- **HELP [\<command\>]**
	```
	HELP with a command name prints info about that command.
	HELP without parameters lists all IRC commands.
	```
- **JOIN \<[#|&|+|!]channel\> [key]**
	```
	The JOIN command allows you to enter a public chat area.
	Network wide channels are proceeded by a '#', while
	a local server channel is proceeded by an '&'. More than one
	channel may be specified, separated with commas (no spaces).
	```
- **LEAVE \<[#|&|+|!]channel\>**
	```
	Requires at least a channel argument to be given. It will
	exit the client from the specified channel. More than one
	channel may be specified, separated with commas (no spaces).
	```
- **LIST [[#|&|+|!]channel]**
	```
	Without any arguments, LIST will give an entire list of all
	channels which are not set as secret (+s). The list will be in
	the form: <#channel> <amount of users> :[topic]
	If an argument supplied is a channel name, LIST will give just
	the statistics for the given channel.
	```
- **MSG \<nick\> \<message\>**
	```	
	: MSG will send a message to the user or channel specified.
	```
- **MODE \<nick\> \<+/-\> \<mode\>, MODE \<channel\> \<+|-\> \<modes\>**

				: MODE <nick> <+|-> <modes>
				   USERMODE      DESCRIPTION
				-----------------------------------------------------------------
				      +O       - Designates this user is a local IRC operator
				      +o       - Designates this user is an IRC operator
				      +i       - Marks this users as invisible
				      +r       - Designates the user has restricted connection

				 MODE <channel> <+|-> <modes>
				  CHANNELMODE   DESCRIPTION
				----------------------------------------------------------------
				     +a       - Anonymous channel
				     +m       - moderated channel
				     +n       - No messages from client on the outside
				     +q       - quiet channel
				     +p       - Private channel
				     +s       - Secret channel
				     +t       - Topic settable by chanop only channel
				     +k       - Set/remove channel key
				     +l       - Set/remove user limit channel
- **NICK \<nick\>**
	```
	When first connected to the IRC server, NICK is required to set the client's nickname.
	NICK will also change the client's nickname once a connection has been established.
	```
- **OPER \<name\> \<password\>**
	```
	The OPER command requires two arguments to be given. The first
	argument is the name of the operator as specified in the
	configuration file. The second argument is the password for
	the operator matching the name and host.
	The operator privileges are shown on a successful OPER.
	```
- **PASS \<password\>**
	```
	PASS is used during registration to access a password protected auth {} block.
	```
- **QUIT	[\<comment\>]**
	```
	Sends a message to the IRC server letting it know you would
	like to disconnect.  The quit message will be displayed to the
	users in the channels you were in when you are disconnected.
	```
- **USER \<user> \<mode> \<unused> \<realname>**
	```
	USER is used during registration to set your gecos
	and to set your username if the server cannot get
	a valid ident response.  The second and third fields
	are not used, but there must be something in them.
	The reason is backwards compatibility
	```
- **TOPIC \<[#|&|+|!]channel> [topic]**
	```
	With only a channel argument, TOPIC shows the current topic of the specified channel.
	With a second argument, it changes the topic on that channel to [topic].
	If the channel is +t, only chanops may change the topic.
	```
- **WHO \<channel|user>**
	```
	The WHO command displays information about a user, such as their GECOS information, their user@host,
	whether they are an IRC operator or not, etc.
	The possible combinations for this field are listed here:
	H       -       The user is not away.
	G       -       The user is set away.
	*       -       The user is an IRC operator.
	@       -       The user is a channel op in the channel listed.
	+       -       The user is voiced in the channel listed.
	```
## CLIENT

### FUNCTIONNALITIES
- **CONNECT \<target_server> [port]**
- **HELP**
- **NICK \<nickname>**
- **PASS \<password>**
- **USER \<user> \<mode> \<unused> \<realname>**
- **QUIT**
