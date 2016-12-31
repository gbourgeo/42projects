/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/21 23:23:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

void				ft_create_game(void)
{
	struct msqid_ds	buf;

	e.shmid = shmget(e.key, e.size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (e.shmid < 0)
		ft_exit_server(1, "shmget");
	printf("e.shmid: %d\n", e.shmid);
	e.data = shmat(e.shmid, NULL, 0);
	if (e.data == (void *)-1)
		ft_exit_server(1, "shmat");
	ft_memset(e.data, 0, e.size);
	*((int *)e.data + e.team) += 1;
	e.map = (char *)e.data + sizeof(*e.data);
	e.semid = semget(e.key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (e.semid < 0)
		ft_exit_server(1, "semget IPC_CREAT");
	if (semctl(e.semid, 0, SETVAL, 0) < 0)
		ft_exit_server(1, "semctl SETVAL");
	printf("e.semid: %d\n", e.semid);
	e.msgqid = msgget(e.key, IPC_CREAT | SHM_R | SHM_W);
	if (e.msgqid < 0)
		ft_exit_server(1, "msgget IPC_CREAT");
	if (msgctl(e.msgqid, IPC_STAT, &buf) < 0)
		ft_exit_server(1, "msgctl IPC_STAT");
}

void				ft_join_game(void)
{
	printf("shmid: %d\n", e.shmid);
	e.semid = semget(e.key, 1, SHM_R | SHM_W);
	if (e.semid < 0)
		ft_exit_client(1, "semget");
	printf("semid: %d\n", e.semid);
	ft_lock();
	e.data = shmat(e.shmid, NULL, 0);
	if (e.data == (void *)-1)
		ft_exit_client(1, "shmat");
	if (TEAMS_SUMM >= MIN_PLAYERS)
		ft_exit_client(0, "Game already full.\nBye.");
	if (e.data->game_in_process)
		ft_exit_client(0, "Game in process.\nCan't join the battle.");
	*((int *)e.data + e.team) += 1;
	e.map = (char *)e.data + sizeof(*e.data);
	e.msgqid = msgget(e.key, SHM_R | SHM_W);
	if (e.msgqid < 0)
		ft_exit_client(1, "msgget");
}
