// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LaunchServer.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 06:24:16 by root              #+#    #+#             //
//   Updated: 2017/09/11 18:33:25 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Daemon.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>

static int	clientRead(Daemon &daemon, int *fd)
{
	int		ret;
	char	buff[513];

	ret = recv(*fd, buff, 512, 0);
	if (ret <= 0)
	{
		close(*fd);
		*fd = -1;
		daemon.log("INFO", "Client disconnected.");
		return (1);
	}
	buff[ret] = '\0';
	if (strcmp(buff, "quit") == 0)
	{
		daemon.log("INFO", "Request quit.");
		return (0);
	}
	daemon.log("LOG", "User input: ", buff);
	return (1);
}

static int	acceptConnections(Daemon &daemon, int *client)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;
	int				i;

	len = sizeof(csin);
	fd = accept(daemon.getServfd(), &csin, &len);
	if (fd < 0)
	{
		daemon.log("ERROR", "Error server accept().");
		return (0);
	}
	i = 0;
	while (i < 3 && client[i] != -1)
		i++;
	if (i == 3)
		return (close(fd) == 0);
	// Recuperer les infos du client et les mettre dans le fichier log.
	client[i] = fd;
	daemon.log("INFO", "New user accepted.");
	return (1);
}

static void	loop(Daemon &daemon)
{
	fd_set	fd_read;
	int		client[3];
	int		maxfd;
	int		i;
	int		ret;
	int		run;

	memset(client, -1, 3);
	run = 1;
	while (run)
	{
		FD_ZERO(&fd_read);
		FD_SET(daemon.getServfd(), &fd_read);
		maxfd = daemon.getServfd();
		i = 0;
		while (i < 3)
		{
			if (client[i] > maxfd)
				maxfd = client[i];
			if (client[i] != -1)
				FD_SET(client[i], &fd_read);
			i++;
		}
		ret = select(maxfd + 1, &fd_read, NULL, NULL, NULL);
		if (ret == -1)
		{
			daemon.log("ERROR", "Error select().");
			break ;
		}
		if (FD_ISSET(daemon.getServfd(), &fd_read))
			run = acceptConnections(daemon, client);
		i = 0;
		while (run && i < 3 && ret > 0)
		{
			if (client[i] != -1)
			{
				if (FD_ISSET(client[i], &fd_read))
				{
					run = clientRead(daemon, &client[i]);
					ret--;
				}
			}
			i++;
		}
	}
	i = 0;
	while (i < 3)
	{
		if (client[i] != -1)
			close(client[i]);
		i++;
	}
}

void	LaunchServer(void)
{
	int fd;

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	close(fd);
	umask(0);
	if (chdir("/") < 0)
		return ;
	
	Daemon			daemon;
	
	if (!daemon.isLocked())
	{
		daemon.log("ERROR", "File locked.");
		return ;
	}
	if (daemon.getServerError())
	{
		daemon.log("ERROR", daemon.getServerError());
		return ;
	}
	daemon.log("INFO", "Server created.");
	loop(daemon);
	daemon.log("INFO", "Quitting");
}
