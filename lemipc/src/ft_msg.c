/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 15:36:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <sys/msg.h>
#include <errno.h>

void				ft_sendmsg(void)
{
	e.snd.mtype = e.team->uid;
	e.snd.msg.ally.x = e.x;
	e.snd.msg.ally.y = e.y;
	ft_memcpy(&e.snd.msg.ennemy, e.target, sizeof(e.snd.msg.ennemy));
	if (msgsnd(e.game.msgqid, &e.snd, sizeof(e.snd.msg), IPC_NOWAIT) == -1)
		ft_exit(1, "msgsnd");
}

int					ft_rcvmsg(void)
{
	int				size;

	size = sizeof(e.rcv.msg);
	ft_memset(&e.rcv, 0, sizeof(e.rcv));
	errno = 0;
	if (msgrcv(e.game.msgqid, &e.rcv, size, e.team->uid, IPC_NOWAIT) == -1)
	{
		if (errno != ENOMSG)
			ft_exit(1, "msgrcv");
		return (1);
	}
	return (0);
}
