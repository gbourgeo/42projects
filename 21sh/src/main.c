/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/01 23:56:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_exit_all(char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	ft_free(&e.env);
	ft_free(&e.path);
	if (e.cpy.str)
		free(e.cpy.str);
	ft_free_hist(&e.hist);
	restore_term();
	exit(EXIT_FAILURE);
}

static void		init_environment(char **environ)
{
	char		**path;
	int			i;

	i = 0;
	if ((e.env = ft_envcpy(environ)) == NULL)
		ft_exit_all("Can't copy environnement.");
	if ((path = ft_strsplit(ft_getenv("PATH", e.env), ':')) == NULL)
		ft_exit_all("Can't split PATH.");
	if ((e.path = malloc(sizeof(*e.path) * (ft_tablen(path) + 1))) == NULL)
		ft_exit_all("Can't copy PATH.");
	while (path[i])
	{
		e.path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	e.path[i] = NULL;
	ft_free(&path);
	e.hist = hist_new(NULL, CMD_SIZE);
}

int				main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	ft_memset(&e, 0, sizeof(e));
	init_environment(environ);
	init_termcaps(NULL, 0);
	init_signals();
	ft_minishell();
	ft_exit(NULL);
	return (0);
}
