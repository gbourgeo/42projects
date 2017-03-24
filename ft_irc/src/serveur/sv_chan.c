/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 16:46:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_join(t_chan *chan, t_fd *cl)
{
	sv_cl_write(":", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write("!~", &cl->wr);
	sv_cl_write(cl->reg.username, &cl->wr);
	sv_cl_write("@", &cl->wr);
	sv_cl_write(cl->addr, &cl->wr);
	sv_cl_write(" JOIN ", &cl->wr);
	sv_cl_write(chan->name, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
}

void			send_joinmsg_toothers(t_chan *chan, t_fd *cl)
{
	t_listin	*other;
	t_fd		*us;

	rpl_join(chan, cl);
	other = chan->users;
	while (other)
	{
		us = (t_fd *)other->is;
		if (!(chan->cmode & CHFL_QUIET) || us->fd == cl->fd)
			sv_cl_send_to(us, &cl->wr);
		other = other->next;
	}
	cl->wr.head = cl->wr.tail;
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
