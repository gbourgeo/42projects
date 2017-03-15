/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_chan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:34:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 17:44:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_listin		*sv_add_usertochan(t_fd *cl, t_chan *chan)
{
	t_listin	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: out of memory", &e);
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
