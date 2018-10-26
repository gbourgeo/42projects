/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 08:47:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_env(const char *prog, const char **environ, t_env *e)
{
	char		**path;
	int			i;

	i = 0;
	e->progname = ft_strrchr(prog, '/');
	e->progname = (e->progname == NULL) ? prog : e->progname + 1;
	e->env = ft_envdup(prog, environ);
	if (e->env == NULL)
		ft_fatal("Can't copy environnement.", e);
	path = ft_strsplit(ft_getenv("PATH", e->env), ':');
	if (path == NULL)
		ft_fatal("Can't split PATH.", e);
	e->path = malloc(sizeof(*e->path) * (ft_tablen(path) + 1));
	if (e->path == NULL)
		ft_fatal("Can't copy PATH.", e);
	while (path[i])
	{
		e->path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	e->path[i] = NULL;
	e->command = NULL;
	e->ret = 0;
	ft_freetab(&path);
}

int				main(int ac, char **av, const char **environ)
{
	(void)ac;
	(void)av;
	ft_memset(&e, 0, sizeof(e));
	init_env(av[0], environ, &e);
	ft_signals();
	ft_shell(&e);
	ft_exit(NULL, &e);
	return (0);
}
