/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 03:51:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_send_more(char **cmd, t_fd *us)
{
	int			i;

	i = 3;
	send(us->fd, ":", 1, 0);
	send(us->fd, cmd[2], ft_strlen(cmd[2]), 0);
	while (cmd[i])
	{
		send(us->fd, " ", 1, 0);
		send(us->fd, cmd[i], ft_strlen(cmd[i]), 0);
		i++;
	}
}

static void		sv_send_leavemsg(char **cmd, t_chan *chan, t_fd *cl)
{
	t_listin	*list;
	t_fd		*us;

	list = chan->users;
	while (list)
	{
		us = (t_fd *)list->is;
		send(us->fd, ":", 1, 0);
		send(us->fd, cl->reg.nick, NICK_LEN, 0);
		send(us->fd, "!~", 2, 0);
		send(us->fd, cl->reg.username, USERNAME_LEN, 0);
		send(us->fd, "@", 1, 0);
		send(us->fd, cl->addr, ADDR_LEN, 0);
		send(us->fd, " LEAVE ", 7, 0);
		send(us->fd, chan->name, CHAN_LEN, 0);
		if (cmd[2])
			sv_send_more(cmd, us);
		send(us->fd, END_CHECK, END_CHECK_LEN, 0);
		list = list->next;
	}
}

static void		sv_find_chaninuser(t_chan *chan, t_fd *cl, t_env *e)
{
	t_listin	*tmp;

	tmp = cl->chans;
	while (tmp && sv_strcmp(((t_chan *)tmp->is)->name, chan->name))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl, e));
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		cl->chans = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp);
}

static void		sv_find_userinchan(char **cmd, t_chan *chan, t_fd *cl, t_env *e)
{
	t_listin	*tmp;

	tmp = chan->users;
	while (tmp && sv_strcmp(((t_fd *)tmp->is)->reg.nick, cl->reg.nick))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl, e));
	sv_send_leavemsg(cmd, chan, cl);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		chan->users = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp);
	sv_find_chaninuser(chan, cl, e);
}

void			sv_leave(char **cmds, t_env *e, t_fd *cl)
{
	char		**list;
	int			i;
	t_chan		*chan;

	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, "LEAVE", NULL, cl, e));
	if ((list = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: SERVER: Out of memory", e);
	i = 0;
	while (list[i])
	{
		chan = e->chans;
		while (chan && sv_strcmp(list[i], chan->name))
			chan = chan->next;
		if (chan == NULL)
			sv_err(ERR_NOSUCHCHANNEL, list[i], NULL, cl, e);
		else
			sv_find_userinchan(cmds, chan, cl, e);
		i++;
	}
	ft_free(&list);
}
