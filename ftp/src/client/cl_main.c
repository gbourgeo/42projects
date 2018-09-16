/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:37:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 06:34:36 by gbourgeo         ###   ########.fr       */
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

static void			ft_getaddrinfo(char *addr, char *port, t_envi *cl)
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

static void			init_client(char *addr, char *port, t_envi *cl, char **env)
{
	ft_getaddrinfo(addr, port, cl);
	if ((cl->path = ft_getenv("PATH=", env)) == NULL)
		cl->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if ((cl->home = ft_strdup(ft_getenv("HOME=", env))) == NULL)
		cl->home = ft_strdup("/");
	cl->lpwd = getcwd(NULL, 0);
	if ((cl->oldpwd = ft_strdup(ft_getenv("OLDPWD=", env))) == NULL)
		cl->oldpwd = getcwd(NULL, 0);
	if ((cl->user = ft_strdup(ft_getenv("USER=", env))) == NULL)
		cl->user = ft_strdup("guest");
	if (!cl->path || !cl->home || !cl->lpwd || !cl->oldpwd)
		ft_error("ERROR: init_env() failed.");
}

int					main(int ac, char **av, char **environ)
{
	t_envi			cl;

	if (ac != 3)
		return (usage(av[0], CLIENT));
	ft_memset(&cl, 0, sizeof(cl));
	init_client(av[1], av[2], &cl, environ);
	ft_signals();
	cl_loop(&cl);
	return (0);
}
