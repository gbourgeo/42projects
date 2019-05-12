/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:52:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:35:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "ft_dprintf.h"
#include "ft_printf.h"
#include "builtin_jobs.h"
#include "job_control.h"
#include "builtins.h"

static int		jobs_opts_loop(char *arg, int *opts, t_s_env *e)
{
	size_t		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'l')
		{
			*opts &= ~JOB_OPT_P;
			*opts |= JOB_OPT_L;
		}
		else if (arg[i] == 'p')
		{
			*opts &= ~JOB_OPT_L;
			*opts |= JOB_OPT_P;
		}
		else
			return (jobs_error(ERR_INVALID_OPTION, &arg[i], e));
		i++;
	}
	return (0);
}

static int		jobs_opts(char **args, int *opts, t_s_env *e)
{
	size_t	i;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (!ft_strcmp(args[i], "--help"))
			ft_printf("--help\n");
		if (!ft_strcmp(args[i], "--"))
			return (i + 1);
		if (jobs_opts_loop(args[i], opts, e))
			return (0);
		i++;
	}
	return (i);
}

int				builtin_jobs(t_execute *exec, t_s_env *e)
{
	int		opts;
	int		i;

	opts = 0;
	e->g_notif = 1;
	if (!(i = jobs_opts(exec->cmd, &opts, e)))
		return (1);
	if (!exec->cmd[i])
		return (jobs_no_arg(e->jobs, exec, &opts));
	else
		return (jobs_spe_arg(exec, e, i, &opts));
}
