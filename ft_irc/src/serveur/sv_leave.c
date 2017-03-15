/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 02:40:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_leave_chan(t_env *e, t_fd *cl)
{
	(void)e;
	(void)cl;
}

static void		sv_find_chaninuser(t_chan *chan, t_fd *cl, t_env *e)
{
	t_listin	*tmp;

	tmp = cl->chans;
	while (tmp && ft_strcmp(((t_chan *)tmp->is)->name, chan->name))
		tmp = tmp->next;
	// I should not send an error here but this error should never happen.
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl, e));
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		cl->chans = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp);
/* 	sv_sendto_chan_msg(":leaved the channel.", cl); */
/* 	sv_leave_chan(e, cl); */
/* 	send(cl->fd, ":Channel leaved.", 16, 0); */
/* 	send(cl->fd, "\r\n", 2, 0); */
}

static void		sv_find_userinchan(t_chan *chan, t_fd *cl, t_env *e)
{
	t_listin	*tmp;

	tmp = chan->users;
	while (tmp && ft_strcmp(((t_fd *)tmp->is)->reg.nick, cl->reg.nick))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl, e));
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
		while (chan && ft_strncmp(list[i], chan->name, CHAN_LEN))
			chan = chan->next;
		if (chan == NULL)
			sv_err(ERR_NOSUCHCHANNEL, list[i], NULL, cl, e);
		else
			sv_find_userinchan(chan, cl, e);
	}
}
