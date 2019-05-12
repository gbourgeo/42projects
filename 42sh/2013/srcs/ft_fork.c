/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 19:03:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/04/29 18:26:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (access(path, F_OK) == 0 && stat(path, &buffer) == 0)
		return (path);
	free(path);
	path = NULL;
	return (NULL);
}

static char		*get_path_from_given_path(char *cmd, char **env)
{
	char		*path;
	char		*tmp;

	tmp = NULL;
	if (*cmd == '.')
	{
		tmp = ft_strjoin(ft_getenv("PWD", env), "/");
		path = ft_get_path(ft_strjoin(tmp, cmd));
		free(tmp);
		return (path);
	}
	tmp = ft_strjoin(ft_getenv("HOME", env), ft_strchr(cmd, '/'));
	path = ft_get_path(tmp);
	free(tmp);
	return (path);
}

static char		*get_path_from(char *cmd, char *base_path, char **env)
{
	int			i;
	char		**path;
	char		*tmp;
	char		*ret;

	i = 0;
	ret = NULL;
	tmp = NULL;
	if (*cmd == '/')
		return (check_path(ft_strdup(cmd)));
	if (*cmd == '.' || *cmd == '~')
		return (check_path(get_path_from_given_path(cmd, env)));
	if ((path = ft_strsplit(ft_getenv("PATH", env), ':')) == NULL)
		path = ft_strsplit(base_path, ':');
	if (path == NULL)
		return (NULL);
	while (path[i] && ret == NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		ret = check_path(ft_strjoin(tmp, cmd));
		free(tmp);
		i++;
	}
	ft_free(&path);
	return (ret);
}

int				fork_function(char **args, char *base_path, char **env)
{
	pid_t		pid;
	int			status;
	char		*path;

	status = 127;
	if ((path = get_path_from(args[0], base_path, env)))
	{
		pid = fork();
		if (pid > 0)
		{
			if (waitpid(pid, &status, 0) != pid)
				ft_putendl("42sh: Waitpid error...");
		}
		else if (pid == 0)
		{
			execve(path, args, env);
			ft_strerror(ft_strjoin("42sh: Check your arguments: ", args[0]));
		}
		else
			ft_putendl("42sh: Fork error...");
		free(path);
	}
	else
		ft_strerror(ft_strjoin("42sh: command not found: ", args[0]));
	return (status);
}
