/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/17 04:16:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		send_joinmsg_toothers(t_chan *chan, t_fd *cl)
{
	t_listin	*other;
	t_fd		*us;

	other = chan->users;
	while (other)
	{
		us = (t_fd *)other->is;
		send(us->fd, ":", 1, 0);
		send(us->fd, cl->reg.nick, NICK_LEN, 0);
		send(us->fd, "!~", 2, 0);
		send(us->fd, cl->reg.username, USERNAME_LEN, 0);
		send(us->fd, "@", 1, 0);
		send(us->fd, cl->addr, ADDR_LEN, 0);
		send(us->fd, " JOIN ", 6, 0);
		send(us->fd, chan->name, ft_strlen(chan->name), 0);
		send(us->fd, END_CHECK, END_CHECK_LEN, 0);
		other = other->next;
	}
}

t_listin		*sv_add_usertochan(t_fd *cl, t_chan *chan)
{
	t_listin	*new;

	chan->nbusers++;
	if ((new = malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: out of memory", &e);
	send_joinmsg_toothers(chan, cl);
	new->prev = NULL;
	new->is = cl;
	new->next = chan->users;
	if (chan->users)
		chan->users->prev = new;
	return (new);
}

t_listin		*sv_add_chantouser(t_chan *chan, t_fd *cl)
{
	t_listin	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: out of memory", &e);
	new->prev = NULL;
	new->is = chan;
	new->next = cl->chans;
	if (cl->chans)
		cl->chans->prev = new;
	return (new);
}
