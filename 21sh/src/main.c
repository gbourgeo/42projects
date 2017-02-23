/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 02:42:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_exit_all(char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	ft_free(&data.env);
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
	if ((data.env = ft_envcpy(environ)) == NULL)
		ft_exit_all("Can't initiate the shell correctly.");
	data.histpath = ft_strjoin(ft_getenv("HOME", data.env), HISTFILE);
	data.hist = retreive_history();
	if ((data.hist = hist_new(NULL, 0, data.hist)) == NULL)
		ft_exit_all("Error: Malloc command.");
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
