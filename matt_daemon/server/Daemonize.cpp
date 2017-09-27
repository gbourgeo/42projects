// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemonize.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/23 04:39:24 by root              #+#    #+#             //
//   Updated: 2017/09/25 07:35:11 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MainServer.hpp"
#include <stdlib.h> //close exit
#include <unistd.h> //fork
#include <sys/types.h> //umask
#include <sys/stat.h>
#include <fcntl.h> //open

void			daemonize(int lock)
{
	pid_t		pid;
	int			fd;
	char		str[7];
		
	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		exit(0);

	if (setsid() < 0)
		throw DAEMONException("setsid");
	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		exit(0);

	sprintf(str, "%d\n", getpid());
	write(lock, str, strlen(str));

	fd = 0;
	while (fd < _NSIG)
		signal(fd++, daemonSigHandler);

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		throw DAEMONException("/dev/null");
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	close(fd);
	umask(0);
	if (chdir("/") < 0)
		throw DAEMONException("/");
}
