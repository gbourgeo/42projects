// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/07 22:26:13 by gbourgeo          #+#    #+#             //
//   Updated: 2017/09/13 22:44:51 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Tintin.hpp"
#include "Server.hpp"
#include "Exceptions.hpp"
#include <stdio.h>
#include <unistd.h> //exit close
#include <stdlib.h> //free
#include <sys/time.h> //getrlimit
#include <sys/resource.h>
#include <sys/types.h> //umask
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h> //open

static void	closeFileDescriptors(void)
{
	struct rlimit	lim;
	size_t			i;

	i = 3;
	if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
		throw DAEMONException("getrlimit");
	while (i < lim.rlim_max)
		close(i++);
}

static void	resetSignalHandlers(sigset_t *oldmask)
{
	size_t		i;
	sigset_t	newmask;

	i = 0;
	while (i < _NSIG)
		signal(i++, SIG_DFL);
	sigfillset(&newmask);
	if (sigprocmask(SIG_SETMASK, &newmask, oldmask) < 0)
		throw DAEMONException("sigprocmask");
}

static void	sanitizeEnvironnement(void)
{
	extern char **environ;

	for (int i = 0; environ && environ[i]; i++)
		memset(environ[i], 0, strlen(environ[i]));
}

static void		setupDaemon(void)
{
	int fd;

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		throw DAEMONException("/dev/null");
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	close(fd);
	umask(0);
	if (chdir(WORKING_DIR) < 0)
		throw DAEMONException(WORKING_DIR);
}

int				main(void)
{
	Tintin_reporter	*tintin;
	Server			*server;
	struct stat		buf;
	sigset_t		oldmask;
	pid_t			pid;

	tintin = NULL;
	server = NULL;
	try
	{
		if (setuid(getuid()) == -1)
			throw DAEMONException("setuid");
		closeFileDescriptors();
		resetSignalHandlers(&oldmask);
		sanitizeEnvironnement();
		tintin = new Tintin_reporter();
		tintin->log("INFO", "Started.");
		if (stat(LOCK_FILE, &buf) == 0)
			throw "Error file locked.";
		tintin->lockfd.exceptions( std::ofstream::failbit | std::ofstream::badbit);
		tintin->lockfd.open(LOCK_FILE);
		try
		{
			tintin->log("INFO", "Creating server.");
			server = new Server();
			tintin->log("INFO", "Server created.");
			tintin->log("INFO", "Entering Daemon mode...");
			pid = fork();
			if (pid < 0)
				throw DAEMONException("fork");
			if (pid == 0)
			{
				if (setsid() < 0)
					throw DAEMONException("setsid");
				pid = fork();
				if (pid < 0)
					throw DAEMONException("fork");
				if (pid == 0)
				{
					tintin->log("INFO", "Done. PID: ", getpid());
					setupDaemon();
					tintin->log("INFO", "Launching server...");
					server->loopServ(tintin);
					delete server;
					delete tintin;
					remove(LOCK_FILE);
					exit(0);
				}
				exit(0);
			}
		}
		catch (DAEMONException& e)
		{
			if (server)
				delete server;
			remove(LOCK_FILE);
			throw ;
		}
		catch (std::exception& e)
		{
			if (server)
				delete server;
			remove(LOCK_FILE);
			throw ;
		}
		catch (int error)
		{
			if (server)
				delete server;
			remove(LOCK_FILE);
			throw ;
		}
		catch (const char *str)
		{
			if (server)
				delete server;
			remove(LOCK_FILE);
			throw ;
		}
	}
	catch (DAEMONException& e)
	{
		std::cerr << "Matt_daemon: " << e.str << ": " << e.what() << std::endl;
		if (tintin)
		{
			tintin->log("ERROR", e.str, e.what());
			delete tintin;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Matt_daemon: " << e.what() << std::endl;
		if (tintin)
		{
			tintin->log("ERROR", e.what());
			delete tintin;
		}
	}
	catch (int error)
	{
		const char	*str;

		str = strerror(error);
		std::cerr << "Matt_daemon: " << str << std::endl;
		if (tintin)
		{
			tintin->log("ERROR", str);
			delete tintin;
		}
	}
	catch (const char *str)
	{
		std::cerr << "Matt_daemon: " << str << std::endl;
		if (tintin)
		{
			tintin->log("ERROR", str);
			delete tintin;
		}
	}
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return 0;
}
