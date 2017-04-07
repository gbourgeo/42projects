/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 23:49:03 by gbourgeo         ###   ########.fr       */
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
	char		*port;

	(void)ac;
	ft_memset(&cl, 0, sizeof(cl));
	cl.sock = -1;
	port = NULL;
	if (!av[1])
	{
		ft_putendl("\e[34mUsage: ./client [host_name[:port]] [port]");
		ft_putendl("Welcome to gbourgeos' IRC client");
		ft_putendl("You can type HELP for a list of commands.\e[0m");
	}
	else if (av[2])
		port = av[2];
	else if ((port = ft_strrchr(av[1], ':')) != NULL)
		*port++ = 0;
	if (port == NULL || *port == 0)
		port = DEF_PORT;
	if (av[1])
		cl_getaddrinfo(av[1], port, &cl);
	cl_loop(&cl);
	return (0);
}
