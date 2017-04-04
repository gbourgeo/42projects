/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:40:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 01:58:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			already_registered(t_fd *cl, t_env *e)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 462 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :You may not reregister", cl);
	sv_cl_write(END_CHECK, cl);
}

static void			missing_parameters(t_fd *cl, t_env *e)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 461 * USER :Not enough parameters", cl);
	sv_cl_write(END_CHECK, cl);
}

void				sv_user(char **cmds, t_env *e, t_fd *cl)
{
	if (cl->inf->registered > 0)
		return (already_registered(cl, e));
	if (ft_tablen(cmds) < 4)
		return (missing_parameters(cl, e));
	ft_strncpy(cl->inf->username, *cmds, USERNAME_LEN);
	if (cl->inf->realname)
		ft_free(&cl->inf->realname);
	cl->inf->realname = ft_tabdup(&cmds[3]);
}
