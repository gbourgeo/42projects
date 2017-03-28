/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg_chan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 04:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:46:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_msg_chan(char **cmds, t_chan *chan, t_fd *cl)
{
	if (chan->cmode & CHFL_ANON)
		sv_write(":anonymous!~anonymous@anonymous", &cl->wr);
	else
	{
		sv_write(":", &cl->wr);
		sv_write(cl->reg.nick, &cl->wr);
		sv_write("!~", &cl->wr);
		sv_write(cl->reg.username, &cl->wr);
		sv_write("@", &cl->wr);
		sv_write(cl->addr, &cl->wr);
	}
	sv_write(" MSG ", &cl->wr);
	sv_write(chan->name, &cl->wr);
	sv_write(" :", &cl->wr);
	sv_write(*cmds, &cl->wr);
	while (*++cmds)
	{
		sv_write(" ", &cl->wr);
		sv_write(*cmds, &cl->wr);
	}
	sv_write(END_CHECK, &cl->wr);
}

static void		sv_sendtochan(char **cmds, t_chan *chan, t_fd *cl)
{
	t_listin	*us;
	t_fd		*to;

	us = chan->users;
	while (us)
	{
		to = (t_fd *)us->is;
		if (to->fd != cl->fd)
		{
			rpl_msg_chan(cmds, chan, cl);
			sv_cl_send_to(to, &cl->wr);
		}
		us = us->next;
	}
	cl->wr.head = cl->wr.tail;
}

static int		user_got_mod(t_chan *ch, t_fd *cl)
{
	t_listin	*list;

	list = ch->users;
	while (list)
	{
		if (((t_fd *)list->is)->fd == cl->fd)
		{
			if (list->mode & CHFL_CHANOP || list->mode & CHFL_VOICE)
				return (1);
			return (0);
		}
		list = list->next;
	}
	return (0);
}

void			sv_msg_chan(char *chan_name, char **cmds, t_fd *cl)
{
	t_chan		*ch;

	ch = e.chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, chan_name))
		{
			if ((ch->cmode & CHFL_MOD && !user_got_mod(ch, cl)) ||
				(ch->cmode & CHFL_NOMSG && !is_chan_member(ch, cl)))
				break ;
			return (sv_sendtochan(cmds, ch, cl));
		}
		ch = ch->next;
	}
	sv_err(ERR_CANNOTSENDTOCHAN, chan_name, NULL, cl);
}
