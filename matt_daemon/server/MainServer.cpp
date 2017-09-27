// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MainServer.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/25 07:33:40 by root              #+#    #+#             //
//   Updated: 2017/09/28 00:42:39 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MainServer.hpp"
#include <sys/time.h> //getrlimit
#include <sys/resource.h>
#include <unistd.h> //close
#include <sys/file.h> //flock
#include <fcntl.h> //open
#include <stdlib.h> //exit

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

static void			lockFile(void)
{
	int				lock;

	lock = open(LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (lock < 0)
		throw DAEMONException(LOCK_FILE);
	if (flock(lock, LOCK_EX | LOCK_NB))
	{
		close(lock);
		throw DAEMONException(LOCK_FILE);
	}
	close(lock);
}

int					main(void)
{
	bool			first = false;

	try
	{
		if (setuid(getuid()) == -1)
			throw DAEMONException("You need to be root !");
		closeFileDescriptors();
		sanitizeEnvironnement();

		tintin = new Tintin_reporter();
		tintin->log("INFO", "Started.");

		lockFile();
		first = true;
		
		tintin->log("INFO", "Creating server.");
		server = new Server();
		tintin->log("INFO", "Server created.");
		
		tintin->log("INFO", "Entering Daemon mode...");
		daemonize();
		tintin->log("INFO", "Done. PID: ", getpid());

		server->loopServ(tintin);
		
		tintin->log("INFO", "Quitting...");
		remove(LOCK_FILE);
		delete server;
		delete tintin;
	}
	catch (DAEMONException& e) {
		std::cerr << "Matt_daemon: " << e.explain() << std::endl;
		quitClearlyDaemon("ERROR", e.explain(), first);
	}
	catch (std::exception& e) {
		std::cerr << "Matt_daemon: " << e.what() << std::endl;
		quitClearlyDaemon("ERROR", e.what(), first);
	}
	return 0;
}

void				quitClearlyDaemon(const char *info, std::string more, bool unlock)
{
	if (unlock)
		remove(LOCK_FILE);
	if (server)
		delete server;
	if (tintin)
	{
		if (info) {
			tintin->log(info, more);
			tintin->log("INFO", "Quitting...\n");
		}
		delete tintin;
	}
	exit(0);
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
		if (sig < 0 || sig > NSIG)
			sig = NSIG + 1;
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
