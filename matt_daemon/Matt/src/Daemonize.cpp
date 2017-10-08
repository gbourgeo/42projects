// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemonize.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/23 04:39:24 by root              #+#    #+#             //
//   Updated: 2017/10/08 13:17:40 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Daemonize.hpp"

void		daemonize()
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		quitClearlyDaemon(NULL, "");

	if (setsid() < 0)
		throw DAEMONException("setsid");
	pid = fork();
	if (pid < 0)
		throw DAEMONException("fork");
	if (pid > 0)
		quitClearlyDaemon(NULL, "");

	fd = 0;
	while (fd < NSIG)
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
