/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 18:40:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			send_joinmsg_toothers(t_chan *chan, t_fd *cl)
{
	t_listin	*other;
	t_fd		*us;

	other = chan->users;
	while (other)
	{
		us = (t_fd *)other->is;
		if (!(chan->cmode & CHFL_QUIET) || us->fd == cl->fd)
		{
			send(us->fd, ":", 1, 0);
			send(us->fd, cl->reg.nick, NICK_LEN, 0);
			send(us->fd, "!~", 2, 0);
			send(us->fd, cl->reg.username, USERNAME_LEN, 0);
			send(us->fd, "@", 1, 0);
			send(us->fd, cl->addr, ADDR_LEN, 0);
			send(us->fd, " JOIN ", 6, 0);
			send(us->fd, chan->name, ft_strlen(chan->name), 0);
			send(us->fd, END_CHECK, END_CHECK_LEN, 0);
		}
		other = other->next;
	}
}

t_listin		*sv_add_usertochan(t_fd *cl, t_chan *chan)
{
	t_listin	*new;

	chan->nbusers++;
	if ((new = malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: out of memory", &e);
	new->prev = NULL;
	new->is = cl;
	new->mode = 0;
	new->next = chan->users;
	if (new->next)
		new->next->prev = new;
	return (new);
}

t_listin		*sv_add_chantouser(t_chan *chan, t_fd *cl)
{
	t_listin	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: out of memory", &e);
	new->prev = NULL;
	new->is = chan;
	new->mode = 0;
	new->next = cl->chans;
	if (new->next)
		new->next->prev = new;
	return (new);
}
