/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/14 14:38:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_remove_chan(t_env *e, t_fd *cl)
{
	if (cl->chan->next)
		cl->chan->next->prev = cl->chan->prev;
	if (cl->chan->prev)
		cl->chan->prev->next = cl->chan->next;
	else
		e->chan = cl->chan->next;
	ft_memset(cl->chan, 0, sizeof(*cl->chan));
	free(cl->chan);
	cl->chan = NULL;
	cl->user->next = NULL;
	cl->user->prev = NULL;
}

void			sv_leave_chan(t_env *e, t_fd *cl)
{
	t_user		*us;

	cl->flags &= ~CHFL_CHANOP;
	if (--cl->chan->nbusers == 0)
		return (sv_remove_chan(e, cl));
	us = cl->chan->user;
	while (((t_fd *)us->is)->fd != cl->fd)
		us = us->next;
	if (us->next)
		us->next->prev = us->prev;
	if (us->prev)
		us->prev->next = us->next;
	else
		cl->chan->user = us->next;
	cl->user->next = NULL;
	cl->user->prev = NULL;
	cl->chan = NULL;
}

t_user			*sv_new_user(t_fd *id)
{
	t_user		*new;

	new = (t_user *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->is = id;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_user			*sv_add_chan_user(t_chan *chan, t_user *new)
{
	t_user		*end;

	if (chan == NULL)
		return (NULL);
	if (new == NULL)
		return (chan->user);
	end = chan->user;
	if (end == NULL)
		return (new);
	while (end->next)
		end = end->next;
	end->next = new;
	new->prev = end;
	return (chan->user);
}
