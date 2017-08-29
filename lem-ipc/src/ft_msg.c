/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/28 01:57:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>

void				ft_sendmsg(void)
{
	e.snd.mtype = e.team;
	e.snd.msg.ally.x = e.x;
	e.snd.msg.ally.y = e.y;
	ft_memcpy(&e.snd.msg.ennemy, e.target, sizeof(e.snd.msg.ennemy));
	if (msgsnd(e.msgqid, &e.snd, sizeof(e.snd.msg), IPC_NOWAIT) == -1)
		ft_exit_client(1, "msgsnd");
}

int					ft_rcvmsg(void)
{
	int				size;

	size = sizeof(e.rcv.msg);
	ft_memset(&e.rcv, 0, sizeof(e.rcv));
	errno = 0;
	if (msgrcv(e.msgqid, &e.rcv, size, e.team, IPC_NOWAIT) == -1)
	{
		if (errno != ENOMSG)
			ft_exit_client(1, "msgrcv");
		return (1);
	}
	return (0);
}
