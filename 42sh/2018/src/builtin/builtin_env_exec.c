/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:15:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 17:04:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <wait.h>
#endif
#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "command.h"

static int		env_fork(t_e_opt *opt, t_s_env *e)
{
	t_s_env		newe;
	pid_t		pid;

	ft_memcpy(&newe, e, sizeof(newe));
	newe.progname = opt->cmdname;
	newe.public_env = opt->public_env;
	newe.forked = 1;
	if ((pid = fork()) > 0)
		waitpid(pid, NULL, 0);
	else if (pid == 0)
	{
		launch_new_cmd(&opt->cmd, &newe);
		exit(*newe.ret);
	}
	else
		return (ERR_FORK);
	return (ERR_OK);
}

static int		env_prepare_command(char **cmd, t_e_opt *opt, int err)
{
	if (!opt->path || ft_strchr(cmd[0], '/'))
	{
		if (!opt->cmd)
		{
			if (!(opt->cmd = ft_strdup(cmd[0])))
				return (ERR_MALLOC);
		}
		else if (!(opt->cmd = ft_strjoinfree(opt->cmd, " ", 1))
			|| !(opt->cmd = ft_strjoinfree(opt->cmd, cmd[0], 1)))
			return (ERR_MALLOC);
		return (ERR_OK);
	}
	if (opt->verbosity > 1
	&& (ft_dprintf(err, "#%s Searching: '%s'\n", opt->cmdname, opt->path) < 0
		|| ft_dprintf(err, "#%s  for file: '%s'\n", opt->cmdname, cmd[0]) < 0))
		return (ERR_WRITE);
	if (!(opt->cmd = ft_strjoinfree(ft_strjoin(opt->path, "/"), cmd[0], 1)))
		return (ERR_MALLOC);
	if (access(opt->cmd, F_OK | X_OK))
		return (ERR_NOT_FOUND);
	else if (opt->verbosity > 1
	&& ft_dprintf(err, "#%s   matched: '%s'\n", opt->cmdname, opt->cmd) < 0)
		return (ERR_WRITE);
	return (ERR_OK);
}

static int		env_get_command(char **cmd, t_e_opt *opt)
{
	size_t		i;

	i = 1;
	if (opt->options & BUILTIN_OPT_V
	&& ft_dprintf(STDERR_FILENO, "#%s    arg[%d]= '%s'\n",
	opt->cmdname, 0, opt->cmd) < 0)
		return (ERR_WRITE);
	while (cmd[i])
	{
		if (opt->options & BUILTIN_OPT_V
		&& ft_dprintf(STDERR_FILENO, "#%s    arg[%d]= '%s'\n",
		opt->cmdname, i, cmd[i]) < 0)
			return (ERR_WRITE);
		if (!(opt->cmd = ft_strjoinfree(opt->cmd, " ", 1))
		|| !(opt->cmd = ft_strjoinfree(opt->cmd, cmd[i], 1)))
			return (ERR_MALLOC);
		i++;
	}
	return (ERR_OK);
}

static int		env_setenv(char **cmd, t_e_opt *opt)
{
	char		*ptr;

	while (*cmd && (ptr = ft_strchr(*cmd, '=')))
	{
		if (opt->options & BUILTIN_OPT_V
		&& ft_dprintf(STDERR_FILENO, "#%s setenv:    %s\n",
		opt->cmdname, *cmd) < 0)
			return (ERR_WRITE);
		*ptr = '\0';
		if (sh_setenv(*cmd, ptr + 1, &opt->public_env))
			return (ERR_MALLOC);
		++cmd;
		++opt->i;
	}
	return (ERR_OK);
}

int				env_exec(t_execute *exec, t_e_opt *opt, t_s_env *e)
{
	int			error;

	if (opt->options & BUILTIN_OPT_I)
	{
		if (opt->options & BUILTIN_OPT_V
		&& ft_dprintf(STDERR_FILENO, "#%s clearing environ\n",
		opt->cmdname) < 0)
			return (ERR_WRITE);
		sh_freetab(&opt->public_env);
	}
	if ((error = env_setenv(exec->cmd + opt->i, opt)) != ERR_OK)
		return (error);
	if (!exec->cmd[opt->i] && sh_puttab((const char **)opt->public_env) < 0)
		return (env_error(ERR_WRITE, exec->cmd[opt->i], opt, e));
	else if (!exec->cmd[opt->i])
		return (ERR_OK);
	if ((error = env_prepare_command(exec->cmd + opt->i, opt, STDERR_FILENO)))
		return (error);
	if (opt->options & BUILTIN_OPT_V
	&& ft_dprintf(STDERR_FILENO, "#%s executing: %s\n",
	opt->cmdname, opt->cmd) < 0)
		return (ERR_WRITE);
	if ((error = env_get_command(exec->cmd + opt->i, opt)) != ERR_OK)
		return (error);
	return (env_fork(opt, e));
}
