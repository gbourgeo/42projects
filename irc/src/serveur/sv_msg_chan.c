/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg_chan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 04:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 04:25:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_msg_chan(char **cmds, t_chan *chan, t_fd *to, t_fd *cl)
{
	if (chan->cmode & CHFL_ANON)
		sv_cl_write(":anonymous!~anonymous@anonymous", to);
	else
	{
		sv_cl_write(":", to);
		sv_cl_write(cl->inf->nick, to);
		sv_cl_write("!~", to);
		sv_cl_write(cl->inf->username, to);
		sv_cl_write("@", to);
		sv_cl_write((*cl->host) ? cl->host : cl->addr, to);
	}
	sv_cl_write(" MSG ", to);
	sv_cl_write(chan->name, to);
	sv_cl_write(" :", to);
	sv_cl_write(*cmds, to);
	while (*++cmds)
	{
		sv_cl_write(" ", to);
		sv_cl_write(*cmds, to);
	}
	sv_cl_write(END_CHECK, to);
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
			rpl_msg_chan(cmds, chan, to, cl);
		us = us->next;
	}
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
