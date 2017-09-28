// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemonize.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/23 04:39:24 by root              #+#    #+#             //
//   Updated: 2017/09/28 17:35:56 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Exceptions.hpp"
#include <stdlib.h> //close exit
#include <unistd.h> //fork
#include <sys/types.h> //umask
#include <sys/stat.h>
#include <fcntl.h> //open
#include <signal.h>

void		quitClearlyDaemon(const char *info, std::string more, int lock, bool first);
void		daemonSigHandler(int sig);

void		daemonize(int lock)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		quitClearlyDaemon(NULL, "", lock, false);

	if (setsid() < 0)
		throw DAEMONException("setsid");
	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		quitClearlyDaemon(NULL, "", lock, false);

	fd = 0;
	while (fd < NSIG)
		signal(fd++, daemonSigHandler);

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		throw DAEMONException("/dev/null");
//	dup2(fd, STDIN_FILENO);
//	dup2(fd, STDOUT_FILENO);
//	dup2(fd, STDERR_FILENO);
	close(fd);
	umask(0);
	if (chdir("/") < 0)
		throw DAEMONException("/");
}
