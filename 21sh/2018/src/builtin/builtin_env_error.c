/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 19:36:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 11:40:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_env.h"

int				env_error(int err, char *c, t_e_opt *opt, t_s_env *e)
{
	static char	*errors[] = {
		"", MALLOC_STR, ILLEGAL_OPTION_STR, NEED_ARG_STR, NOT_FOUND_STR,
		WRITE_STR,
	};
	static int	values[] = {
		1, 1, 1, 1, 127, 1,
	};

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "env: %s", errors[err]);
	if (c)
		if (err == ERR_ILLEGAL_OPT || err == ERR_NEED_ARG)
		{
			ft_dprintf(STDERR_FILENO, " -- %c\nusage: env ", c[opt->j]);
			ft_dprintf(STDERR_FILENO, "[-iv] [-P utilpath] [-u name]\n       ");
			ft_dprintf(STDERR_FILENO, "    [name=value ...]");
			ft_dprintf(STDERR_FILENO, " [utility [argument ...]]");
		}
	ft_dprintf(STDERR_FILENO, "\n");
	env_free_opt(opt);
	*e->ret = values[err];
	return (values[err]);
}
