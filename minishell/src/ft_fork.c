/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 19:03:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/04 21:38:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		*check_command(char **cmd, char **env)
{
	char		*pwd;
	char		*tmp;
	int			i;

	pwd = ft_strdup(ft_getenv("PWD", env));
	if (pwd == NULL)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		if (!ft_strcmp(cmd[i], ".."))
			ft_strcpy(ft_strrchr(pwd, '/'), "/0");
		else if (ft_strcmp(cmd[i], "."))
			break ;
		i++;
	}
	while (cmd && cmd[i])
	{
		tmp = ft_strjoin(pwd, "/");
		free(pwd);
		pwd = ft_strjoin(tmp, cmd[i]);
		i++;
	}
	ft_free(&cmd);
	return (pwd);
}

static char		*check_path(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
		return (NULL);
	if (access(path, F_OK) != 0)
		return (NULL);
	return (path);
}


static char		*search_path(char *cmd, char **env)
{
	int			i;
	char		*ret;
	char		*tmp;
	char		**paths;

	i = 0;
	ret = NULL;
	paths = (ft_getenv("PATH", env)) ?
		ft_strsplit(ft_getenv("PATH", env), ':') : NULL; // e->path
	while (paths && paths[i])
	{
		tmp = (paths[i][ft_strlen(paths[i]) - 1] != '/') ?
			ft_strjoin(paths[i], "/") : paths[i];
		ret = ft_strjoin(tmp, cmd);
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			free(tmp);
		if (check_path(ret))
			break ;
		free(ret);
		ret = NULL;
		i++;
	}
	if (paths && ft_getenv("PATH", env))
		ft_free(&paths);
	return (ret);
}

static char		*get_path(char **cmd, char **env)
{
	if (cmd && *cmd[0] == '/')
		return (check_path(ft_strdup(*cmd)));
	if (cmd && ft_strchr(*cmd, '/'))
		return (check_command(ft_strsplit(*cmd, '/'), env));
	return (search_path(*cmd, env));
}

int				fork_function(char **args, char **env)
{
	pid_t		pid;
	int			status;
	char		*path;

	status = 127;
	if ((path = get_path(args, env)) != NULL)
	{
		pid = fork();
		if (pid > 0)
		{
			if (waitpid(pid, &status, 0) < 0)
				ft_putendl_fd("minishell: waitpid error.", 2);
		}
		else if (pid == 0)
		{
			execve(path, args, env);
			ft_putendl_fd("minishell: check your arguments.", 2);
			exit(1);
		}
		else
			ft_putendl_fd("minishell: Fork error.", 2);
		free(path);
	}
	else
		ft_putendl_fd("minishell: command not found.", 2);
	return (status);
}
