/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:30:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:38:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_info_next(t_fd *user, t_fd *cl)
{
	t_listin	*li;
	char		**tmp;

	li = user->chans;
	if (user->inf->umode & USR_OP || user->inf->umode & USR_LOCALOP)
		sv_cl_write("*", cl);
	if (li && li->mode & CHFL_CHANOP)
		sv_cl_write("@", cl);
	if (li && li->mode & CHFL_VOICE)
		sv_cl_write("+", cl);
	sv_cl_write(" :0", cl);
	tmp = user->inf->realname;
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
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	if (us->chans)
		sv_cl_write(((t_chan *)us->chans->is)->name, cl);
	else
		sv_cl_write("*", cl);
	sv_cl_write(" ~", cl);
	sv_cl_write(us->inf->username, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(us->i.addr, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(us->inf->nick, cl);
	sv_cl_write(" ", cl);
	if (us->inf->umode & USR_AWAY)
		sv_cl_write("G", cl);
	else
		sv_cl_write("H", cl);
	sv_info_next(us, cl);
}
