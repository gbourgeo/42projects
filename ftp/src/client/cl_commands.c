/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:58:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 17:20:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_commands(char **args, t_envi *cl)
{
	pid_t		pid;
	int			status;

	status = 1;
	args[0] = ft_get_command(args[0], ft_strsplit(cl->path, ':'), 1);
	pid = fork();
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == pid)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
		else
			ft_putendl("\033[31mERROR: Waitpid error...");
	}
	else if (pid == 0)
	{
		status = execv(args[0], args);
		ft_putendl("\033[31mERROR: Command not found");
		exit(127 + status);
	}
	else
		ft_putendl("\033[31mERROR: Fork error...");
	return (status);
}
