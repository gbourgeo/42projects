/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/07 16:58:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>

void				ft_sendmsg(void)
{
	int				size;

	size = sizeof(e.snd.mtext);
	e.snd.mtype = e.team;
	ft_memcpy(e.snd.mtext, e.target, size);
	msgsnd(e.msgqid, &e.snd, size, IPC_NOWAIT);
}

int					ft_rcvmsg(void)
{
	int				size;

	size = sizeof(e.rcv.mtext);
	ft_memset(&e.rcv, 0, sizeof(e.rcv));
	errno = 0;
	if (msgrcv(e.msgqid, &e.rcv, size, e.team, IPC_NOWAIT) == -1)
	{
		if (errno != ENOMSG)
			perror("msgrcv");
		return (1);
	}
	e.target = (t_player *)e.rcv.mtext;
	return (0);
}
