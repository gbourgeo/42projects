# FTP
*This project involves the implementation of a client and a File Transfer Protocol (FTP) server for TCP / IP network file transfer.*


### Create the Server, the Client or both
```sh
$> make server && ./server -h
server: -- Server Help

NAME
	server - FTP server

USAGE
	./server [OPTIONS]... PORT

DESCRIPTION
	Launch an FTP server.

	-4	   Server allows IpV4 address only.

	-6	   Server allows IpV6 address only.

	-d	   Every registered users will have his personal directory created. Works only with -u.

	-h, --help
		   Print help and exit.

	-i	   Interactive server. Prints information on STDOUT.

	-p, --path [path]
		   Server working path.

	-u, --user
		   Enables registered users mode.

	port	Port to listen to.

AUTHOR
	Written by Gilles Bourgeois.
```
```sh
$> make client && ./client
Usage: ./client [server_address] [server_port]

```
 Or simply,
```sh
$> make
```

## DESIGN
- A customer specific prompt.
- Can not go down to a level below the server's runtime directory.
- Display of SUCCESS or ERROR + explanation messages after each request.

## COMMANDS
Those commands operate on the server side:
```
- help        : list available commands
- ls          : list the current directory
- cd          : change the current directory
- pwd         : displays the path of the current directory
- get [file]  : get the _file_ file from the server to the client
- put [file]  : send the _file_ file from the client to the server
- mkdir [-pv] : create a directory
- rmdir       : erase a directory
- unlink      : erase a file
- sign        : sign-in to the server
- quit        : cut the connection
```

Those commands operate on the client local system:
```
- lls
- lcd
- lpwd
- ...
- mget [dir]  : like GET but "multiple" and for directories
- mput [dir]  : like PUT but "multiple" and for directories
```

## EXTRA
- RFC 959 compliant
- IPv6 supported
- login/password management

## AUTHOR
- gbourgeo

