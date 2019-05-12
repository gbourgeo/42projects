/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:02:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 15:05:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "builtins.h"
#include "job_control.h"
#include "redirection.h"

static int		cmd_ch_builtin(int (*handler)(t_execute *, t_s_env *),
		t_jobs *job, t_process *p, t_s_env *e)
{
	int			ret;
	int			len;
	t_execute	*exec;

	exec = (t_execute *)p->exec;
	ret = command_builtin(handler, job, p, e);
	if ((len = sh_tablen((const char **)exec->cmd)))
		len--;
	if (!e->forked)
		sh_setenv("_", exec->cmd[len], &e->public_env);
	return (ret);
}

int				command_builtin_forked(t_jobs *job, t_process *p, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV, BUILTIN_JOBS,
		BUILTIN_FG, BUILTIN_BG, BUILTIN_TYPE, BUILTIN_EXPORT, BUILTIN_SET,
		BUILTIN_UNSET, BUILTIN_TEST,
	};
	size_t				i;
	t_execute			*exec;

	i = 0;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
				exit(cmd_ch_builtin(builtins[i].handler, job, p, e));
			i++;
		}
	}
	return (1);
}

int				command_is_builtin(t_process *p)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV, BUILTIN_JOBS,
		BUILTIN_FG, BUILTIN_BG, BUILTIN_TYPE, BUILTIN_EXPORT, BUILTIN_SET,
		BUILTIN_UNSET, BUILTIN_TEST,
	};
	size_t				i;
	t_execute			*exec;

	i = 0;
	p->pid = 0;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		while (i < sizeof(builtins) / sizeof(builtins[0]))
		{
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]))
				return (1);
			i++;
		}
	}
	return (0);
}

int				command_check(t_jobs *job, t_process *p, t_s_env *e)
{
	static t_builtins	builtins[] = {
		BUILTIN_ALIAS, BUILTIN_CD, BUILTIN_ECHO, BUILTIN_ENV, BUILTIN_EXIT,
		BUILTIN_SETENV, BUILTIN_UNALIAS, BUILTIN_UNSETENV, BUILTIN_JOBS,
		BUILTIN_FG, BUILTIN_BG, BUILTIN_TYPE, BUILTIN_EXPORT, BUILTIN_SET,
		BUILTIN_UNSET, BUILTIN_TEST
	};
	size_t				i;
	int					ret;
	int					len;
	t_execute			*exec;

	i = -1;
	ret = 0;
	exec = (t_execute *)p->exec;
	if (exec->cmd && exec->cmd[0])
	{
		while (++i < sizeof(builtins) / sizeof(builtins[0]))
			if (!ft_strcmp(builtins[i].name, exec->cmd[0]) && !p->next)
				if (p->pid == 0 && job->foreground == 0)
					return (cmd_ch_builtin(builtins[i].handler, job, p, e));
		ret = command_bys(job, p, e);
		(len = sh_tablen((const char **)exec->cmd)) ? len-- : 0;
		sh_setenv("_", exec->cmd[len], &e->public_env);
	}
	return (ret);
}
