/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/14 23:14:29 by gbourgeo         ###   ########.fr       */
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
	if (msgsnd(e.msgqid, &e.snd, sizeof(e.snd.msg), IPC_NOWAIT) == -1)
		ft_exit_client(1, "msgsnd");
}

void				ft_rcvmsg(void)
{
	int				size;

	size = sizeof(e.rcv.msg);
	ft_bzero(&e.rcv, sizeof(e.rcv));
	if (msgrcv(e.msgqid, &e.rcv, size, e.team, IPC_NOWAIT) == -1 &&
		errno != ENOMSG)
		ft_exit_client(1, "msgrcv");
	printf("My friend (x:%d, y:%d) wants to attack x:%d y:%d dist:%d\n",
			e.rcv.msg.ally.x, e.rcv.msg.ally.y,
			e.rcv.msg.ennemy.x + 1, e.rcv.msg.ennemy.y + 1,
			e.rcv.msg.ennemy.dist);
}
