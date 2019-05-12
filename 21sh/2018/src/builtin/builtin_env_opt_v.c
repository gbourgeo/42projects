/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_v.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:31:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/09 16:21:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "builtin_env.h"

int			env_opt_v(char **cmd, t_e_opt *opt)
{
	(void)cmd;
	opt->options |= BUILTIN_OPT_V;
	opt->verbosity++;
	if (opt->verbosity > 1)
		if (ft_dprintf(STDERR_FILENO, "#%s verbosity now at %d\n",
		opt->cmdname, opt->verbosity) < 0)
			return (ERR_WRITE);
	return (ERR_OK);
}
