/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 16:43:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <sys/msg.h>
#include <errno.h>

void				ft_sendmsg(t_ipc *ipc)
{
	e.snd.mtype = e.player.team->uid;
	e.snd.msg.ally.x = e.x;
	e.snd.msg.ally.y = e.y;
	ft_memcpy(&e.snd.msg.ennemy, e.target, sizeof(e.snd.msg.ennemy));
	if (msgsnd(ipc->msgqid, &e.snd, sizeof(e.snd.msg), IPC_NOWAIT) == -1)
		ft_exit_client(1, "msgsnd", ipc);
}

int					ft_rcvmsg(t_ipc *ipc)
{
	int				size;

	size = sizeof(e.rcv.msg);
	ft_memset(&e.rcv, 0, sizeof(e.rcv));
	errno = 0;
	if (msgrcv(ipc->msgqid, &e.rcv, size, e.player.team->uid, IPC_NOWAIT) == -1)
	{
		if (errno != ENOMSG)
			ft_exit_client(1, "msgrcv", ipc);
		return (1);
	}
	return (0);
}
