/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:37:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/26 23:39:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_leave(char **cmds, t_env *e, size_t i)
{
	if (!cmds[1])
		send(e->fds[i].fd, "\e[31m/leave: Missing argument\n\e[0m", 34, 0);
	else if (ft_strcmp(cmds[1], e->fds[i].chan))
		send(e->fds[i].fd, "\e[31m/leave: Bad channel name\n\e[0m", 34, 0);
	else
	{
		sv_leave_chan(e, i);
		e->chan->users++;
		ft_strncpy(e->fds[i].chan, "Global", CHAN_SIZE);
		send(e->fds[i].fd, "\e[33mChannel leaved, you joined [", 33, 0);
		send(e->fds[i].fd, "\e[0mGlobal\e[33m] channel.\n\e[0m", 30, 0);
	}
}
