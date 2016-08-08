/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/14 07:18:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_leave(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*ch;

	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(cmds[0], ":Not enough parameters", cl->fd));
	ch = e->chan;
	while (ch && ft_strncmp(cmds[1], ch->name, CHAN_SIZE))
		ch = ch->next;
	if (ch == NULL)
		return (sv_err(cmds[1], ":No such channel", cl->fd));
	if (!cl->chan || ft_strncmp(cmds[1], cl->chan->name, CHAN_SIZE))
		return (sv_err(cmds[1], ":Not on channel", cl->fd));
	sv_sendto_chan_msg(" :leaved the channel.", cl);
	sv_leave_chan(e, cl);
	send(cl->fd, ":Channel leaved.", 16, 0);
	send(cl->fd, "\r\n", 2, 0);
}
