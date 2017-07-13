/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:20:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_join(t_chan *ch, t_fd *to, t_fd *cl)
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
	sv_cl_write(" JOIN ", to);
	sv_cl_write(ch->name, to);
	sv_cl_write(END_CHECK, to);
}

void			send_joinmsg_toothers(t_chan *chan, t_fd *cl)
{
	t_listin	*other;
	t_fd		*to;

	other = chan->users;
	while (other)
	{
		to = (t_fd *)other->is;
		if (!(chan->cmode & CHFL_QUIET) || to->i.fd == cl->i.fd)
			rpl_join(chan, to, cl);
		other = other->next;
	}
}

t_listin		*sv_add_usertochan(t_fd *cl, t_chan *chan)
{
	t_listin	*new;

	(cl->inf->umode & USR_INVISIBL) ? chan->invisibl++ : chan->nbusers++;
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
