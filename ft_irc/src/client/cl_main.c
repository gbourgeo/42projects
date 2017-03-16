/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 02:17:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>
#include <fcntl.h>

static void		cl_loop(t_client *cl)
{
	int			max;

	while (42)
	{
		FD_ZERO(&cl->fds);
		FD_SET(STDIN_FILENO, &cl->fds);
		if (cl->sock > 0)
			FD_SET(cl->sock, &cl->fds);
		max = (cl->sock > STDIN_FILENO) ? cl->sock : STDIN_FILENO;
		if (select(max + 1, &cl->fds, NULL, NULL, NULL) == -1)
			cl_error("Client: select() failed.", cl);
		if (cl->sock > -1 && FD_ISSET(cl->sock, &cl->fds))
			read_server(cl);
		if (FD_ISSET(STDIN_FILENO, &cl->fds))
			read_client(cl);
	}
}

int				main(int ac, char **av)
{
	t_client	cl;

	(void)ac;
	ft_memset(&cl, 0, sizeof(cl));
	cl.sock = -1;
	if (!av[1] || cl_getaddrinfo(av[1], av[2], &cl))
	{
		ft_putendl("Usage: ./client [host_name] [port]");
		ft_putendl("You are not connected to any IRC server.");
		ft_putendl("\e[34mYou can type /help for a list of commands.\e[0m");
	}
	cl_loop(&cl);
	return (0);
}
