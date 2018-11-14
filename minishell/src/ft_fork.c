/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 19:03:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 08:59:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "main.h"

static char		*check_command(char **cmd)
{
	char		*pwd;
	char		*tmp;
	int			i;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		if (!ft_strcmp(cmd[i], ".."))
			ft_strcpy(ft_strrchr(pwd, '/'), "\0");
		else if (ft_strcmp(cmd[i], "."))
			break ;
		i++;
	}
	while (cmd && cmd[i])
	{
		tmp = ft_strjoin(pwd, "/");
		ft_freestr(&pwd);
		pwd = ft_strjoin(tmp, cmd[i]);
		ft_freestr(&tmp);
		i++;
	}
	ft_freetab(&cmd);
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
		ft_strsplit(ft_getenv("PATH", env), ':') : NULL;
	while (paths && paths[i])
	{
		tmp = (paths[i][ft_strlen(paths[i]) - 1] != '/') ?
			ft_strjoin(paths[i], "/") : paths[i];
		ret = ft_strjoin(tmp, cmd);
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			ft_freestr(&tmp);
		if (check_path(ret))
			break ;
		ft_freestr(&ret);
		ret = NULL;
		i++;
	}
	if (paths && ft_getenv("PATH", env))
		ft_freetab(&paths);
	return (ret);
}

static char		*get_path(char **cmd, char **env)
{
	if (cmd && *cmd[0] == '/')
		return (check_path(ft_strdup(*cmd)));
	if (cmd && ft_strchr(*cmd, '/'))
		return (check_command(ft_strsplit(*cmd, '/')));
	return (search_path(*cmd, env));
}

int				fork_function(char **args, char **env, const char *prog)
{
	pid_t		pid;
	int			status;
	char		*path;

	status = 127;
	if ((path = get_path(args, env)) != NULL)
	{
		if ((pid = fork()) > 0)
		{
			if (waitpid(pid, &status, 0) < 0)
				ft_dprintf(2, "%s: waitpid error.\n", prog);
		}
		else if (pid == 0)
		{
			status = execve(path, args, env);
			ft_dprintf(2, "%s: failed to execute: %s.\n", prog, args[0]);
			exit(status);
		}
		else
			ft_dprintf(2, "%s: Fork error.\n", prog);
		ft_freestr(&path);
	}
	else
		ft_dprintf(2, "%s: command not found: %s\n", prog, args[0]);
	return (status);
}
