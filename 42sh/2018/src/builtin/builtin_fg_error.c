/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:50:25 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/27 18:03:15 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"
#include "ft_dprintf.h"

int	fg_error(int err, char *arg, t_s_env *e)
{
	static char *errors[] = {
		NULL, "invalid option: -", "no such job",
	};

	if (err == ERR_INVALID_OPTION)
	{
		ft_dprintf(2, "%s: fg: %s", e->progname, errors[err]);
		ft_dprintf(2, "%c\nfg: usage: fg [jobspec]", *arg);
		ft_dprintf(2, "\n");
		return (2);
	}
	else
		ft_dprintf(2, "%s: fg: %s: %s", e->progname, arg, errors[err]);
	ft_dprintf(2, "\n");
	return (1);
}
