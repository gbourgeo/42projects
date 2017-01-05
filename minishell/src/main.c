/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/05 19:06:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_exit_all(char *err, t_env *e)
{
	int			i;

	i = 0;
	ft_putendl_fd(err, 2);
	ft_free(&e->env);
	ft_free(&e->path);
	exit(EXIT_FAILURE);
}

static void		init_environment(char **environ, t_env *e)
{
	char		**path;
	int			i;

	i = 0;
	e->env = ft_envcpy(environ);
	if (e->env == NULL)
		ft_exit_all("Can't copy environnement.", e);
	path = ft_strsplit(ft_getenv("PATH", e->env), ':');
	if (path == NULL)
		ft_exit_all("Can't split PATH.", e);
	e->path = malloc(sizeof(*e->path) * (ft_tablen(path) + 1));
	if (e->path == NULL)
		ft_exit_all("Can't copy PATH.", e);
	while (path[i])
	{
		e->path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	e->path[i] = NULL;
	e->ret = 0;
	ft_free(&path);
}

int				main(int ac, char **av, char **environ)
{
	t_env		e;

	(void)ac;
	(void)av;
	ft_memset(&e, 0, sizeof(e));
	init_environment(environ, &e);
	ft_shell(&e);
	ft_exit(NULL, &e);
	return (0);
}
