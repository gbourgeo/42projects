/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:02:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/25 23:16:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_pass(char **cmds, t_env *e, t_fd *cl)
{
	(void)e;
	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "PASS", NULL, cl));
	if (cl->reg.registered > 0)
		return (sv_err(ERR_ALREADYREGISTERED, NULL, NULL, cl));
	if (cl->reg.password)
		free(cl->reg.password);
	cl->reg.password = ft_strdup(*cmds);
}
