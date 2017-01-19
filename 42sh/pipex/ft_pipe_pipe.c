/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:37:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/30 00:31:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void			ft_pipe_pipe(t_args *pipes, t_env *e)
{
	int			fildes[2];
	pid_t		pid;

	if (pipe(fildes) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_dup2(fildes[1], 1);
			ft_close(fildes[0]);
			exit(check_and_exec(pipes->args, e));
		}
		else if (pid > 0)
		{
			ft_dup2(fildes[0], 0);
			ft_close(fildes[1]);
			waitpid(pid, &e->status, 0);
			e->status = check_and_exec(pipes->next->args, e);
		}
		else
			ft_putendl("42sh: Fork error...");
	}
	else
		ft_putendl("42sh: ERROR: pipe();");
}
