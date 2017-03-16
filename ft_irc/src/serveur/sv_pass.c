/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:02:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 10:07:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_pass(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, "PASS", NULL, cl, e));
	if (cl->reg.registered > 0)
		return (sv_err(ERR_ALREADYREGISTERED, NULL, NULL, cl, e));
	if (cl->reg.password)
		free(cl->reg.password);
	cl->reg.password = ft_strdup(cmds[1]);
}
