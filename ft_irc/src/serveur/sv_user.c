/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_user.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 04:40:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:47:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			already_registered(t_fd *cl, t_env *e)
{
	sv_write(":", &e->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 462 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" :You may not reregister", &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

static void			missing_parameters(t_fd *cl, t_env *e)
{
	sv_write(":", &e->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 461 * USER :Not enough parameters", &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

void				sv_user(char **cmds, t_env *e, t_fd *cl)
{
	if (cl->reg.registered > 0)
		return (already_registered(cl, e));
	if (ft_tablen(cmds) < 4)
		return (missing_parameters(cl, e));
	ft_strncpy(cl->reg.username, *cmds, USERNAME_LEN);
	if (cl->reg.realname)
		ft_free(&cl->reg.realname);
	cl->reg.realname = ft_tabdup(&cmds[3]);
}
