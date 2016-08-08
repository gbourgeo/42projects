/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 03:00:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/02 18:42:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

void			cl_nick(char **cmds, t_client *cl)
{
	if (!cmds[1] && cl->sock == -1)
		ft_putendl_fd("\e[31mMissing parameters.\e[0m", 2);
}

void			cl_help(char **cmds, t_client *cl)
{
	if (cl->sock == -1)
	{
		ft_putendl("Here's a list of usefull commands:");
		ft_putendl("/nick <nickname>");
		ft_putendl("/connect <_host_[:port]>");
		ft_putendl("/quit");
	}
	(void)cmds;
}

void			cl_void(char **cmds, t_client *cl)
{
	(void)cmds;
	(void)cl;
}

void			cl_quit(char **cmds, t_client *cl)
{
	ft_free(&cmds);
	if (cl->sock >= 0)
		close(cl->sock);
	FD_ZERO(&cl->fds);
	ft_memset(cl, 0, sizeof(*cl));
	exit(0);
}

void			cl_connect(char **cmds, t_client *cl)
{
	char		*port;
	int			fd;

	fd = cl->sock;
	if (!cmds[1])
		return (ft_putendl_fd("Missing parameters.", 2));
	port = (cmds[2] == NULL) ? ft_strrchr(cmds[1], ':') : cmds[2];
	ft_strclr(cl->read);
	if (fd != -1)
		send(fd, "/quit\n", 6, 0);
	if (cmds[2] == NULL)
		*port++ = '\0';
	if (cl_getaddrinfo(cmds[1], port, cl))
		cl->sock = fd;
	else if (*cl->name)
	{
		send(cl->sock, "/nick ", 6, 0);
		send(cl->sock, cl->name, NAME_SIZE, 0);
		send(cl->sock, "\n", 1, 0);
	}
}
