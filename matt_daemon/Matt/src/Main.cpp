// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/28 18:38:19 by root              #+#    #+#             //
//   Updated: 2017/11/01 16:37:06 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Main.hpp"
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

int					main(void)
{
	e.tintin = NULL;
	e.server = NULL;
	e.lock = -1;
	e.first = false;
	try
	{
		if (setuid(getuid()) == -1)
			throw DAEMONException("You need to be root !");
		closeFileDescriptors();
		sanitizeEnvironnement();

		e.tintin = new Tintin_reporter();
		e.tintin->log("INFO", "Started.");

		e.lock = open(LOCK_FILE, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (e.lock < 0)
			throw DAEMONException(LOCK_FILE);
		if (flock(e.lock, LOCK_EX | LOCK_NB))
			throw DAEMONException(LOCK_FILE);
		
		e.tintin->log("INFO", "Creating server.");
		e.server = new Server();
		e.server->setReporter(e.tintin);
		e.tintin->log("INFO", "Server created.");
		
		e.tintin->log("INFO", "Entering Daemon mode...");
		daemonize();
		e.first = true;
		e.tintin->log("INFO", "Daemon child #%d survived...", getpid());

		e.server->mailMeDaemonInfo();
		e.server->launchServer();
		
		flock(e.lock, LOCK_UN);
		remove(LOCK_FILE);
		close(e.lock);
		delete e.server;
		e.tintin->log("INFO", "Quitting...");
		delete e.tintin;
	}
	catch (DAEMONException& err) {
		std::cerr << "Matt_daemon: " << err.explain() << std::endl;
		quitClearlyDaemon("ERROR", err.explain());
	}
	catch (std::exception& err) {
		std::cerr << "Matt_daemon: " << err.what() << std::endl;
		quitClearlyDaemon("ERROR", err.what());
	}
	return 0;
}

void				quitClearlyDaemon(const char *info, std::string more)
{
	if (e.first) {
		flock(e.lock, LOCK_UN);
		remove(LOCK_FILE);
	}
	if (e.lock > -1)
		close(e.lock);
	if (e.server)
	{
		e.server->quitReason += more;
		delete e.server;
	}
	if (e.tintin)
	{
		e.tintin->log(info, more);
		delete e.tintin;
	}
	exit(0);
}

void			daemonSigHandler(int sig)
{
	const std::string signals[] = { "0", "SIGUP", "SIGINT", "SIGQUIT", "SIGILL",
									"SIGTRAP", "SIGABRT", "SIGPOLL/SIGEMT",
									"SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV",
									"SIGSYS", "SIGPIPE", "SIGALRM", "SIGTERM",
									"SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT",
									"SIGCHLD", "SIGTTIN", "SIGTTOU", "SIGIO",
									"SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
									"SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2",
									"UNKNOWN SIGNAL"};

	quitClearlyDaemon("ERROR", signals[sig]);
}
