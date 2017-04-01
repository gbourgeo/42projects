/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:30:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/01 22:28:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_info_next(t_fd *user, t_fd *cl)
{
	t_listin	*li;
	char		**tmp;

	li = user->chans;
	if (user->reg.umode & USR_OP || user->reg.umode & USR_LOCALOP)
		sv_cl_write("*", cl);
	if (li && li->mode & CHFL_CHANOP)
		sv_cl_write("@", cl);
	if (li && li->mode & CHFL_VOICE)
		sv_cl_write("+", cl);
	sv_cl_write(" :0", cl);
	tmp = user->reg.realname;
	while (tmp && *tmp)
	{
		sv_cl_write(" ", cl);
		sv_cl_write(*tmp, cl);
		tmp++;
	}
	sv_cl_write(END_CHECK, cl);
}

void			sv_who_info(t_fd *us, t_fd *cl, t_env *e)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 352 ", cl);
	sv_cl_write(cl->reg.nick, cl);
	sv_cl_write(" ", cl);
	if (us->chans)
		sv_cl_write(((t_chan *)us->chans->is)->name, cl);
	else
		sv_cl_write("*", cl);
	sv_cl_write(" ~", cl);
	sv_cl_write(us->reg.username, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(us->addr, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(us->reg.nick, cl);
	sv_cl_write(" ", cl);
	if (us->reg.umode & USR_AWAY)
		sv_cl_write("G", cl);
	else
		sv_cl_write("H", cl);
	sv_info_next(us, cl);
}
