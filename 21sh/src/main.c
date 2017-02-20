/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/20 21:11:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_exit_all(char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	ft_free(&data.env);
	ft_free(&data.path);
	if (data.histpath)
		free(data.histpath);
	if (data.cpy.str)
		free(data.cpy.str);
	ft_free_hist(&data.hist);
	restore_term();
	exit(EXIT_FAILURE);
}

static void		init_environment(char **environ)
{
	char		**path;
	int			i;

	i = 0;
	if ((data.env = ft_envcpy(environ)) == NULL)
		ft_exit_all("Can't copy environnement.");
	
	if ((path = ft_strsplit(ft_getenv("PATH", data.env), ':')) == NULL)
		ft_exit_all("Can't split PATH.");
	if (!(data.path = malloc(sizeof(*data.path) * (ft_tablen(path) + 1))))
		ft_exit_all("Can't copy PATH.");
	while (path[i])
	{
		data.path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	data.path[i] = NULL;
	ft_free(&path);
	data.histpath = ft_strjoin(ft_getenv("HOME", data.env), HISTFILE);
	data.hist = retreive_history();
	if ((data.hist = hist_new(NULL, 0, data.hist)) == NULL)
		ft_exit_all("Malloc failed.");
	data.cmd = data.hist;
}

int				main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(data));
	init_environment(environ);
	init_termcaps(NULL, 0);
	init_signals();
	ft_minishell(&data);
	ft_exit(NULL, NULL);
	return (0);
}
