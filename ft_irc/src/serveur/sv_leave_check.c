/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:41:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:45:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_leave(char **cmd, t_chan *chan, t_fd *cl)
{
	t_buf		*b;

	b = &cl->wr;
	sv_write(":", &cl->wr);
	sv_write((chan->cmode & CHFL_ANON) ? "anonymous" : cl->reg.nick, b);
	sv_write("!~", &cl->wr);
	sv_write((chan->cmode & CHFL_ANON) ? "anonymous" : cl->reg.username, b);
	sv_write("@", &cl->wr);
	sv_write((chan->cmode & CHFL_ANON) ? "anonymous" : cl->addr, b);
	sv_write(" LEAVE ", &cl->wr);
	sv_write(chan->name, &cl->wr);
	sv_write(" :", &cl->wr);
	if (*cmd)
	{
		sv_write(*cmd, &cl->wr);
		while (*++cmd)
		{
			sv_write(" ", &cl->wr);
			sv_write(*cmd, &cl->wr);
		}
	}
	sv_write(END_CHECK, &cl->wr);
}

static void		sv_send_leavemsg(t_chan *chan, t_fd *cl)
{
	t_listin	*list;
	t_fd		*us;

	list = chan->users;
	while (list)
	{
		us = (t_fd *)list->is;
		if (!(chan->cmode & CHFL_QUIET) || us->fd == cl->fd)
			sv_cl_send_to(us, &cl->wr);
		list = list->next;
	}
	cl->wr.head = cl->wr.tail;
}

static void		sv_find_chaninuser(t_chan *chan, t_fd *cl)
{
	t_listin	*tmp;

	tmp = cl->chans;
	while (tmp && sv_strcmp(((t_chan *)tmp->is)->name, chan->name))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl));
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		cl->chans = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	tmp->is = NULL;
	free(tmp);
	tmp = NULL;
}

void			sv_find_userinchan(char **cmd, t_chan *chan, t_fd *cl)
{
	t_listin	*tmp;

	tmp = chan->users;
	while (tmp && sv_strcmp(((t_fd *)tmp->is)->reg.nick, cl->reg.nick))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl));
	chan->nbusers--;
	cl->chansnb--;
	rpl_leave(cmd, chan, cl);
	sv_send_leavemsg(chan, cl);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		chan->users = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	tmp->is = NULL;
	free(tmp);
	tmp = NULL;
	sv_find_chaninuser(chan, cl);
}
