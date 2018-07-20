/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 00:42:55 by root              #+#    #+#             */
/*   Updated: 2018/07/20 05:03:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo etc. */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
/* signal */
#include <signal.h>

#include "ft_dprintf.h"
#include "durex.h"
#include "shell.h"

static void			serverShellError(char *err, t_sh *shell, t_cl *client)
{
	if (shell->fd >= 0)
		close(shell->fd);
	ft_dprintf(client->fd, "%s\n", err);
}

static void		sigchld_handler(int sig)
{
	(void)sig;
}

static int			openSocket(struct addrinfo *p)
{
	int				fd;
	int				on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) &&
		!bind(fd, p->ai_addr, p->ai_addrlen) &&
		!listen(fd, SHELL_CLIENT_MAX))
		return fd;
	close(fd);
	return -1;
}

static int			openShell(const char *addr, const char *port)
{
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	fd = -1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, &res))
		return (-1);
	p = res;
	while (p != NULL)
	{
		if (p->ai_family == AF_INET)
			fd = openSocket(p);
		if (fd >= 0)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || fd < 0)
		return (-1);
	return fd;
}

static int			setupSelect(t_sh *shell)
{
	int				i;
	int				max;

	FD_ZERO(&shell->fdr);
	FD_ZERO(&shell->fdw);
	FD_SET(shell->fd, &shell->fdr);
	max = shell->fd;
	i = 0;
	while (i < SHELL_CLIENT_MAX)
	{
		if (shell->client[i].fd > max)
			max = shell->client[i].fd;
		if (shell->client[i].fd != -1) {
			FD_SET(shell->client[i].fd, &shell->fdr);
			FD_SET(shell->client[i].fd, &shell->fdw);
		}
		i++;
	}
	return max;
}

static void		quitShell(t_sh *shell)
{
	close(shell->fd);
	for (int i = 0; i < SHELL_CLIENT_MAX; i++) {
		if (shell->client[i].fd >= 0)
			close(shell->client[i].fd);
	}
}

static void		shellAcceptConnection(t_sh *shell)
{
	struct sockaddr		csin;
	socklen_t			len= sizeof(csin);
	int					fd;

	fd = accept(shell->fd, &csin, &len);
	if (fd < 0)
		return ;
	for (int i = 0; i < SHELL_CLIENT_MAX; i++) {
		if (shell->client[i].fd == -1) {
			shell->client[i].fd = fd;
			return ;
		}
	}
	write(fd, "Server Full\n", 13);
	close(fd);
}

void			serverShell(t_cl *client)
{
	t_sh		shell;
	int			maxfd;
	int			ret;
	struct timeval	timeout;

	ft_dprintf(client->fd, "Spawning shell on port %s\n", SERVER_PORT);
	client->shell = 1;
	return ;

	shell.fd = openShell(SERVER_ADDR, SHELL_PORT);
	if (shell.fd < 0)
		return serverShellError("Unable to open shell socket", &shell, client);
	for (int i = 0; i < SHELL_CLIENT_MAX; i++) {
		clearClient(&shell.client[i]);
	}
	if (signal(SIGCHLD, &sigchld_handler) == SIG_ERR)
		return serverShellError("Unable to use sig_child handler", &shell, client);
	serverQuitClient(client);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (1)
	{
		maxfd = setupSelect(&shell);
		ret = select(maxfd, &shell.fdr, &shell.fdw, NULL, &timeout);
		if (ret == -1)
			break ;
		if (FD_ISSET(shell.fd, &shell.fdr))
			shellAcceptConnection(&shell);
		/* for (int i = 0; i < SHELL_CLIENT_MAX; i++) */
		/* { */
		/* 	if (shell.client[i].fd == -1) */
		/* 		continue ; */
		/* 	if (FD_ISSET(shell.client[i].fd, &shell.fdr)) */
		/* 		shellReadClient(&shell.client[i]); */
		/* 	if (FD_ISSET(shell.client[i].fd, &shell.fdw)) */
		/* 		shellWriteClient(&shell.client[i]); */
		/* } */
	}
	quitShell(&shell);
}
