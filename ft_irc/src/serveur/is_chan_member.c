/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_chan_member.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:05:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 12:07:54 by gbourgeo         ###   ########.fr       */
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
		if (us->fd == cl->fd)
			return (1);
		l = l->next;
	}
	return (0);
}
