/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:03:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:46:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		rpl_quit(char **cmds, t_chan *ch, t_fd *cl)
{
	if (ch && ch->cmode & CHFL_ANON)
	{
		sv_write(":anonymous!~anonymous@anonymous LEAVE ", &cl->wr);
		sv_write(ch->name, &cl->wr);
		sv_write(END_CHECK, &cl->wr);
		return ;
	}
	sv_write(":", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write("!~", &cl->wr);
	sv_write(cl->reg.username, &cl->wr);
	sv_write("@", &cl->wr);
	sv_write(cl->addr, &cl->wr);
	sv_write(" QUIT :", &cl->wr);
	if (cmds == NULL || !*cmds)
		sv_write("Client Quit", &cl->wr);
	while (cmds && *cmds)
	{
		sv_write(*cmds, &cl->wr);
		if (*++cmds)
			sv_write(" ", &cl->wr);
	}
	sv_write(END_CHECK, &cl->wr);
}

void			sv_quit(char **cmds, t_env *e, t_fd *cl)
{
	t_listin	*ch;
	t_listin	*us;

	ch = cl->chans;
	while (ch)
	{
		rpl_quit(cmds, ch->is, cl);
		us = ((t_chan *)ch->is)->users;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd)
				sv_cl_send_to(us->is, &cl->wr);
			us = us->next;
		}
		ch = ch->next;
	}
	if (*cl->reg.username && cl->reg.password && *cl->reg.nick)
	{
		add_in_userslist(e->users, cl);
		add_in_users(e->users, cl);
	}
	cl->leaved = 1;
	cl->reason = "Client Quit";
}
