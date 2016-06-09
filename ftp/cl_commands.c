/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:58:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/07 20:28:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char		*get_path(char *cmd, char **dirs)
{
	char		*tmp;
	char		*ret;
	int			i;

	tmp = NULL;
	ret = NULL;
	i = 0;
	if (dirs == NULL)
	{
		ft_putendl("\033[31mERROR: ft_strsplit() failed.\033[0m");
		return (cmd);
	}
	while (dirs[i] && ret == NULL)
	{
		tmp = ft_strjoin(dirs[i], "/");
		ret = check_path(ft_strjoin(tmp, cmd + 1));
		free(tmp);
		i++;
	}
	free(cmd);
	ft_free(&dirs);
	return (ret);
}

int				cl_commands(char **args, t_envi *cl)
{
	pid_t		pid;
	int			status;

	status = 1;
	args[0] = get_path(args[0], ft_strsplit(cl->path, ':'));
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
