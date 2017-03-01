/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 19:03:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/01 09:13:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		*check_command(char **cmd, t_env *e)
{
	char		*pwd;
	char		*tmp;
	int			i;

	pwd = ft_strdup(ft_getenv("PWD", e->env));
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

static char		*search_path(char *cmd, t_env *e)
{
	int			i;
	char		*ret;
	char		**paths;

	i = 0;
	if ((ret = ft_getenv("PATH", e->env)) == NULL || *ret == 0)
		return (NULL);
	if ((paths = ft_strsplit(ret, ':')) == NULL)
		return (NULL);
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			ret = ft_str2join(paths[i], "/", cmd);
		else
			ret = ft_strjoin(paths[i], cmd);
		if (check_path(ret))
			break ;
		free(ret);
		ret = NULL;
		i++;
	}
	ft_free(&paths);
	return (ret);
}

char			*get_path(char **cmd, t_env *e)
{
	if (cmd == NULL || *cmd == NULL)
		return (NULL);
	if (*cmd[0] == '/')
		return (check_path(ft_strdup(*cmd)));
	if (ft_strchr(*cmd, '/'))
		return (check_command(ft_strsplit(*cmd, '/'), e));
	return (search_path(*cmd, e));
}

void			fork_function(char **args, t_env *e)
{
	pid_t		pid;
	char		*path;

	if ((path = get_path(args, e)) != NULL)
	{
		pid = fork();
		if (pid > 0)
		{
			if (waitpid(pid, &e->ret, 0) < 0)
				ft_putendl_fd("21sh: waitpid error.", 2);
		}
		else if (pid == 0)
		{
			e->ret = execve(path, args, e->env);
			ft_putendl_fd("21sh: check your arguments.", 2);
			exit(e->ret);
		}
		else
			ft_putendl_fd("21sh: Fork error.", 2);
	}
	else
		ft_put2endl_fd("21sh: command not found: ", args[0], 2);
	ft_update_env(path, args, e);
}
