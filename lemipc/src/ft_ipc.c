/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:52:36 by root              #+#    #+#             */
/*   Updated: 2018/09/07 15:41:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void			init_ipc(const char *prog, t_ipc *ipc)
{
	ipc->key = ftok(prog, 'G');
	if (ipc->key == -1)
		ft_exit(1, "ftok");
	ipc->size = MAP_WIDTH * MAP_HEIGTH * sizeof(ipc->map) + sizeof(*ipc->board);
	ipc->shmid = shmget(ipc->key, ipc->size, SHM_R | SHM_W);
	ipc->board = (void *)-1;
	ipc->map = (void *)0;
	ipc->msgqid = -1;
	ipc->semid = -1;
	ipc->teams = (void *)0;
}
