/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:30:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 18:15:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_info_next(t_fd *user, t_fd *cl)
{
	t_listin	*li;
	char		**tmp;

	li = user->chans;
	if (user->reg.umode & USR_OP || user->reg.umode & USR_LOCALOP)
		send(cl->fd, "*", 1, 0);
	if (li && li->mode & CHFL_CHANOP)
		send(cl->fd, "@", 1, 0);
	if (li && li->mode & CHFL_VOICE)
		send(cl->fd, "+", 1, 0);
	send(cl->fd, " :0", 3, 0);
	tmp = user->reg.realname;
	while (tmp && *tmp)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, *tmp, ft_strlen(*tmp), 0);
		tmp++;
	}
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

void			sv_who_info(t_fd *us, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 352 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (us->chans)
		send(cl->fd, ((t_chan *)us->chans->is)->name, CHANNAME_LEN, 0);
	else
		send(cl->fd, "*", 1, 0);
	send(cl->fd, " ~", 2, 0);
	send(cl->fd, us->reg.username, USERNAME_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, us->addr, ADDR_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, us->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	if (us->reg.umode & USR_AWAY)
		send(cl->fd, "G", 1, 0);
	else
		send(cl->fd, "H", 1, 0);
	sv_info_next(us, cl);
}
