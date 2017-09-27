// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MainServer.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/25 07:33:40 by root              #+#    #+#             //
//   Updated: 2017/09/25 07:34:50 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MainServer.hpp"
#include <sys/time.h> //getrlimit
#include <sys/resource.h>
#include <unistd.h> //close
#include <sys/file.h> //flock
#include <fcntl.h> //open

Tintin_reporter	*tintin = NULL;
Server			*server = NULL;

static void			closeFileDescriptors(void)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		throw DAEMONException("getrlimit");
	while (i < lim.rlim_max)
		close(i++);
}

static void			sanitizeEnvironnement(void)
{
	extern char		**environ;

	for (int i = 0; environ && environ[i]; i++)
		memset(environ[i], 0, strlen(environ[i]));
}

static int			lockFile(void)
{
	int				lock;

	lock = open(LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (lock < 0)
		return -1;
	if (flock(lock, LOCK_EX | LOCK_NB))
	{
		close(lock);
		return -1;
	}
	return lock;
}

int					main(void)
{
	int				lock;
	bool			first_daemon = false;

	try
	{
		if (setuid(getuid()) == -1)
			throw DAEMONException("You need to be root !");
		closeFileDescriptors();
		sanitizeEnvironnement();

		tintin = new Tintin_reporter();
		tintin->log("INFO", "Started.");

		if ((lock = lockFile()) < 0)
		{
			errno = 0;
			throw DAEMONException("Error file locked.");
		}
		first_daemon = true;
		
		tintin->log("INFO", "Creating server.");
		server = new Server();
		tintin->log("INFO", "Server created.");
		
		tintin->log("INFO", "Entering Daemon mode...");
		daemonize(lock);
		tintin->log("INFO", "Done. PID: ", getpid());

		server->loopServ(tintin);
		flock(lock, LOCK_UN);
		remove(LOCK_FILE);
		delete server;
		delete tintin;

	}
	catch (DAEMONException& e) {
		std::cerr << "Matt_daemon: " << e.explain() << std::endl;
		if (server)
			delete server;
		if (tintin)
		{
			tintin->log("ERROR", e.explain());
			delete tintin;
		}
		if (first_daemon)
		{
			flock(lock, LOCK_UN);
			remove(LOCK_FILE);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Matt_daemon: " << e.what() << std::endl;
		if (server)
			delete server;
		if (tintin)
		{
			tintin->log("ERROR", e.what());
			delete tintin;
		}
		if (first_daemon)
		{
			flock(lock, LOCK_UN);
			remove(LOCK_FILE);
		}
	}
	return 0;
}

void			daemonSigHandler(int sig)
{
	struct tm	*tm;
	time_t		t;
	const char	*signals[] = { "0", "SIGUP", "SIGINT", "SIGQUIT", "SIGILL",
							  "SIGTRAP", "SIGABRT", "SIGPOLL/SIGEMT",
							  "SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV",
							  "SIGSYS", "SIGPIPE", "SIGALRM", "SIGTERM",
							  "SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT",
							  "SIGCHLD", "SIGTTIN", "SIGTTOU", "SIGIO",
							  "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
							   "SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2",
	"UNKNOWN SIGNAL"};

	if (tintin->_logfd.is_open())
	{
		t = time(NULL);
		tm = localtime(&t);
		if (sig < 0 || sig > _NSIG)
			sig = _NSIG + 1;
		tintin->_logfd << "[" << tm->tm_mday << "/";
		tintin->_logfd << tm->tm_mon << "/";
		tintin->_logfd << 1900 + tm->tm_year;
		tintin->_logfd << "-" << tm->tm_hour;
		tintin->_logfd << ":" << tm->tm_min;
		tintin->_logfd<< ":" << tm->tm_sec;
		tintin->_logfd << "] [ ERROR ] - Matt_daemon: ";
		tintin->_logfd << signals[sig] << " caught.\n";
	}
	server->quit();
}
