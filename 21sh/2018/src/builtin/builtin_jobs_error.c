/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:38:35 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 17:51:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "ft_dprintf.h"
#include "builtin_jobs.h"

int			jobs_error(int err, char *arg, t_s_env *e)
{
	static char	*errors[] = {
		NULL, "invalid option: -", "no such job",
	};

	if (err == ERR_INVALID_OPTION)
	{
		ft_dprintf(2, "%s: jobs: %s", e->progname, errors[err]);
		ft_dprintf(2, "%c\njobs: usage: jobs [-lp] [jobspec ...]", *arg);
	}
	else
		ft_dprintf(2, "%s: jobs: %s: %s", e->progname, arg, errors[err]);
	ft_dprintf(2, "\n");
	return (1);
}
