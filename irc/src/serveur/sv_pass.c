/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 10:02:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/03 21:16:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_pass(char **cmds, t_env *e, t_fd *cl)
{
	(void)e;
	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "PASS", NULL, cl));
	if (cl->registered > 0)
		return (sv_err(ERR_ALREADYREGISTERED, NULL, NULL, cl));
	if (cl->inf->pass)
		free(cl->inf->pass);
	cl->inf->pass = ft_strdup(*cmds);
}
