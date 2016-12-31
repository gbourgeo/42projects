/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/22 14:06:43 by gbourgeo         ###   ########.fr       */
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
	if (msgsnd(e.msgqid, &e.snd, sizeof(e.snd.ennemy), IPC_NOWAIT) == -1)
		ft_exit_client(1, "msgsnd");
}

void				ft_rcvmsg(void)
{
	int				size;

	size = sizeof(e.rcv.ennemy);
	ft_bzero(&e.rcv, sizeof(e.rcv));
	if (msgrcv(e.msgqid, &e.rcv, size, e.team, IPC_NOWAIT) == -1 &&
		errno != ENOMSG)
		ft_exit_client(1, "msgrcv");
	printf("My friend wants to attack x:%d y:%d dist:%d\n",
			e.rcv.ennemy.x,
			e.rcv.ennemy.y,
			e.rcv.ennemy.dist); 
}
