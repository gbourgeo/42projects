/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 04:19:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void			init_addrinfo(char *addr, char *port, struct addrinfo **res)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, res))
		ft_error("ERROR: getaddrinfo() returns.");
}

static void			ft_getaddrinfo(char *addr, char *port, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				on;

	on = 1;
	init_addrinfo(addr, port, &results);
	tmp = results;
	while (tmp != NULL)
	{
		cl->fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (cl->fd == -1)
			continue ;
		if (connect(cl->fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(cl->fd);
		tmp = tmp->ai_next;
	}
	freeaddrinfo(results);
	if (tmp == NULL)
		ft_error("Error: No server found.");
	if (setsockopt(cl->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ft_error("Error: setsockopt(SO_REUSEADDR) failed");
}

static void			init_client(char *addr, char *port, t_client *cl, char **env)
{
	ft_getaddrinfo(addr, port, cl);
}

int					main(int ac, char **av)
{
	t_client	*cl;
	int			errnb;

	cl = &client;
	if ((errnb = ft_init(cl, sizeof(*cl), CLIENT, av[0])) != IS_OK)
		return (ft_error(errnb, cl));
	if (ac < 3)
		return (usage(av[0], CLIENT));
	init_client(av[1], av[2], &cl, environ);
	ft_signals();
	cl_loop(&cl);
	return (0);
}
