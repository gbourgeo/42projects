/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 03:52:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_leave(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*ch;

	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, cmds[0], NULL, cl, e));
	ch = e->chans;
	while (ch && ft_strncmp(cmds[1], ch->name, CHAN_LEN))
		ch = ch->next;
	if (ch == NULL)
		return (sv_err(ERR_NOSUCHCHANNEL, cmds[1], NULL, cl, e));
	if (!cl->chan || ft_strncmp(cmds[1], cl->chan->name, CHAN_LEN))
		return (sv_err(ERR_NOTONCHANNEL, cmds[1], NULL, cl, e));
	sv_sendto_chan_msg(" :leaved the channel.", cl);
	sv_leave_chan(e, cl);
	send(cl->fd, ":Channel leaved.", 16, 0);
	send(cl->fd, "\r\n", 2, 0);
}
