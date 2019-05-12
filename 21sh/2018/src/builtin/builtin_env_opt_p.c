/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:33:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 19:13:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin_env.h"

int			env_opt_p(char **cmd, t_e_opt *opt)
{
	if (!cmd[opt->i][opt->j + 1] && !cmd[opt->i + 1])
		return (ERR_NEED_ARG);
	opt->options |= BUILTIN_OPT_P;
	opt->path = (cmd[opt->i][opt->j + 1]) ?
				&cmd[opt->i][opt->j + 1] : cmd[++(opt->i)];
	return (ERR_OK);
}
