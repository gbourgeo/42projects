/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:41:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:29:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_leave(char **cmd, t_chan *ch, t_fd *to, t_fd *cl)
{
	sv_cl_write(":", to);
	sv_cl_write((ch->cmode & CHFL_ANON) ? "anonymous" : cl->inf->nick, to);
	sv_cl_write("!~", to);
	sv_cl_write((ch->cmode & CHFL_ANON) ? "anonymous" : cl->inf->username, to);
	sv_cl_write("@", to);
	if (*cl->i.host)
		sv_cl_write((ch->cmode & CHFL_ANON) ? "anonymous" : cl->i.host, to);
	else
		sv_cl_write((ch->cmode & CHFL_ANON) ? "anonymous" : cl->i.addr, to);
	sv_cl_write(" LEAVE ", to);
	sv_cl_write(ch->name, to);
	sv_cl_write(" :", to);
	if (cmd && *cmd)
	{
		sv_cl_write(*cmd, to);
		while (*++cmd)
		{
			sv_cl_write(" ", to);
			sv_cl_write(*cmd, to);
		}
	}
	sv_cl_write(END_CHECK, to);
}

static void		sv_send_leavemsg(char **cmd, t_chan *chan, t_fd *cl)
{
	t_listin	*list;
	t_fd		*to;

	list = chan->users;
	while (list)
	{
		to = (t_fd *)list->is;
		if (!(chan->cmode & CHFL_QUIET) || to->i.fd == cl->i.fd)
			rpl_leave(cmd, chan, to, cl);
		list = list->next;
	}
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
	while (tmp && sv_strcmp(((t_fd *)tmp->is)->inf->nick, cl->inf->nick))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl));
	(cl->inf->umode & USR_INVISIBL) ? chan->invisibl-- : chan->nbusers--;
	cl->chansnb--;
	sv_send_leavemsg(cmd, chan, cl);
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
