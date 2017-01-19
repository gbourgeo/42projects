/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:42:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/30 00:53:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_pipe_more(t_env *e)
{
	char	**args;

	if ((args = malloc(sizeof(char*) * 2)) == NULL)
		return ;
	args = malloc(sizeof(char*) * 2);
	args[0] = ft_strdup("more");
	args[1] = NULL;
	e->status = check_and_exec(args, e);
}


void		ft_pipe_left(t_args *pipes, t_env *e)
{
	int		fd;
	char	*path;

	path = ft_str2join(getcwd(NULL, 0), "/", pipes->next->args[0]);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(pipes->next->args[0], 2);
		e->status = 1;
	}
	else
	{
		ft_dup2(fd, 0);
		if (!*pipes->args)
			ft_pipe_more(e);
		else
			e->status = check_and_exec(pipes->args, e);
	}
	close(fd);
	free(path);
}
