/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 17:27:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <sys/sem.h>
#include <sys/msg.h>

void				ft_create_game(t_ipc *ipc)
{
	struct msqid_ds	buf;

	ipc->shmid = shmget(ipc->key, ipc->size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (ipc->shmid < 0)
		ft_exit_creation(1, "shmget", ipc);
	ipc->board = shmat(ipc->shmid, NULL, 0);
	if (ipc->board == (void *)-1)
		ft_exit_creation(1, "shmat", ipc);
	ft_memset(ipc->board, 0, ipc->size);
	ipc->board->players = 1;
	ipc->map = (ULL *)ipc->board + sizeof(*ipc->board);
	ft_memset(ipc->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*ipc->map));
	ipc->semid = semget(ipc->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (ipc->semid < 0)
		ft_exit_creation(1, "semget IPC_CREAT", ipc);
	if (semctl(ipc->semid, 0, SETVAL, 0) < 0)
		ft_exit_creation(1, "semctl SETVAL", ipc);
	ipc->msgqid = msgget(ipc->key, IPC_CREAT | SHM_R | SHM_W);
	if (ipc->msgqid < 0)
		ft_exit_creation(1, "msgget IPC_CREAT", ipc);
	if (msgctl(ipc->msgqid, IPC_STAT, &buf) < 0)
		ft_exit_creation(1, "msgctl IPC_STAT", ipc);
}

void				ft_join_game(t_ipc *ipc)
{
	ipc->semid = semget(ipc->key, 1, SHM_R | SHM_W);
	if (ipc->semid < 0)
		ft_exit_client(1, "semget", ipc);
	ipc->board = shmat(ipc->shmid, NULL, 0);
	if (ipc->board == (void *)-1)
		ft_exit_client(1, "shmat", ipc);
	/* if (ft_nb_players(ipc->data->connected) >= MAP_WIDTH * MAP_HEIGTH - 1) */
	/* 	ft_exit_client(0, "Game is full.\n"); */
	/* if (ipc->data->game_in_process > 0) */
	/* 	ft_exit_client(0, "Game in process. You can't join the battle."); */
	ipc->map = (ULL *)ipc->board + sizeof(*ipc->board);
	ipc->msgqid = msgget(ipc->key, SHM_R | SHM_W);
	if (ipc->msgqid < 0)
		ft_exit_client(1, "msgget", ipc);
}
