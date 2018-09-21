# Matt Daemon
*This project is an introduction to the concept of Daemon*

This little program main function is to treat and stock messages received on a specific port, opened by the daemon.

## The Server

### Behaviour
* The program launch itself only if you are root.
* The program run in the background like a real daemon.
* The program open and listen on port 4242.
* The program logs all actions made in a logfile named matt_daemon.log on the form [ DD / MM / YYYY - HH : MM : SS] located
in /var/log/matt_daemon/.
* The program creates a lock file named matt_daemon.lock in /var/lock, so only one instance of the daemon can be started.
* The program close when you send "quit" on the open socket.
* Three clients can connect simultaneously on the daemon.
* The program catch signals, writes it to the log file and quits properly.

### Functionnalities
* Here's a list of all the daemon functionnalities :
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
* The daemon can be password protected. No password required for the first client to connect. Alterable on the run.
* The daemon can be in encrypt mode: All messages send and received will and must be encrypted.
* The daemon can send mail with informations about the machine and services of the infected host.

### Usage
```
$> ./Matt_Daemon
$>
```

## The Client

You can connect to the daemon with netcat :
```
$> nc [machine IP] 4242

```
or by executing Ben_AFK :
```
$> ./Ben_AFK
```
![](https://github.com/gbourgeo/42projects/blob/master/matt_daemon/Common/ben_afk.png)

## Dependencies

* FOr the graphical client, download and install [**Qt 5.9.1**](https://download.qt.io/archive/qt/5.9/5.9.1/)
![](https://github.com/gbourgeo/42projects/blob/master/matt_daemon/Common/qt_logo.png)
* For sending mails, download and install **openssl**
```
apt-get install openssl-dev
```

## Configuration

You can change :
* The lock file (inc/Main.hpp).
* The log directory and file (inc/Tintin.hpp).
* The server address and port, encryption mode and password protection at start, the maximum client and the loggin' time (inc/Server.hpp)
* The mail server connection configuration like server URL, port, domain, uid, password (inc/mail.hpp).
* The mail send information like, from, to, header, header from, header to (inc/mail.hpp).

## Compilation
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
