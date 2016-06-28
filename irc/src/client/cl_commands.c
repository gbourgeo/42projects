/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 03:00:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/26 20:05:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

void			cl_nick(char **cmds, t_client *cl)
{
	if (cmds[1])
	{
		if (cl->sock == -1 || ft_strcmp(cl->write, END_CHECK))
			ft_strncpy(cl->name, cmds[1], NAME_SIZE);
	}
}

void			cl_help(char **cmds, t_client *cl)
{
	if (cl->sock == -1)
	{
		ft_putendl("Here's a list of usefull commands:");
		ft_putendl("/nick [nickname]");
		ft_putendl("/connect _host_[:port]");
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
	exit(1);
}

void			cl_connect(char **cmds, t_client *cl)
{
	char		*port;
	int			fd;

	fd = cl->sock;
	port = ft_strrchr(cmds[1], ':');
	if (!cmds[1] || !port || !*(port + 1))
		return (ft_putendl_fd("\e[31mUsage: /connect _host_[:port]\e[0m", 2));
	ft_strclr(cl->read);
	if (fd != -1)
		send(fd, "/quit\n", 6, 0);
	*port = '\0';
	if (cl_getaddrinfo(cmds[1], port + 1, cl, 1))
		cl->sock = fd;
	else
		recv(cl->sock, cl->name, NAME_SIZE, 0);
}
