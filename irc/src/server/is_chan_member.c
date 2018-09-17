/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chan_member.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:05:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:18:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				is_chan_member(t_chan *ch, t_fd *cl)
{
	t_listin	*l;
	t_fd		*us;

	l = ch->users;
	while (l)
	{
		us = (t_fd *)l->is;
		if (us->i.fd == cl->i.fd)
			return (1);
		l = l->next;
	}
	return (0);
}

int				is_modo(t_chan *chan, t_fd *cl)
{
	t_listin	*li;
	t_fd		*us;

	li = chan->users;
	while (li)
	{
		us = (t_fd *)li->is;
		if (us->i.fd == cl->i.fd)
			return (li->mode & CHFL_CHANOP);
		li = li->next;
	}
	return (0);
}
