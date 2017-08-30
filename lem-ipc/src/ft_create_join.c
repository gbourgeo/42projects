/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 21:21:54 by gbourgeo         ###   ########.fr       */
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

static void			print_info(void)
{
	printf("msgqid: %d\n", e.msgqid);
	printf("semid: %d\n", e.semid);
	printf("shmid: %d\n", e.shmid);
}

void				ft_create_game(void)
{
	struct msqid_ds	buf;

	e.shmid = shmget(e.key, e.size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (e.shmid < 0)
		ft_exit_server(1, "shmget");
	e.data = shmat(e.shmid, NULL, 0);
	if (e.data == (void *)-1)
		ft_exit_server(1, "shmat");
	ft_memset(e.data, -1, e.size);
	ft_memset(e.data->connected, 0, sizeof(int) * MAX_TEAMS);
	e.map = (char *)e.data + sizeof(*e.data);
	ft_memset(e.map, -1, MAP_WIDTH * MAP_HEIGTH);
	e.semid = semget(e.key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (e.semid < 0)
		ft_exit_server(1, "semget IPC_CREAT");
	if (semctl(e.semid, 0, SETVAL, 0) < 0)
		ft_exit_server(1, "semctl SETVAL");
	e.msgqid = msgget(e.key, IPC_CREAT | SHM_R | SHM_W);
	if (e.msgqid < 0)
		ft_exit_server(1, "msgget IPC_CREAT");
	if (msgctl(e.msgqid, IPC_STAT, &buf) < 0)
		ft_exit_server(1, "msgctl IPC_STAT");
	e.creator = 1;
	print_info();
}

void				ft_join_game(void)
{
	e.semid = semget(e.key, 1, SHM_R | SHM_W);
	if (e.semid < 0)
		ft_exit_client(1, "semget");
	e.data = shmat(e.shmid, NULL, 0);
	if (e.data == (void *)-1)
		ft_exit_client(1, "shmat");
	if (ft_nb_players(e.data->connected) >= MAP_WIDTH * MAP_HEIGTH - 1)
		ft_exit_client(0, "Game is full.\n");
	if (e.data->game_in_process > 0)
		ft_exit_client(0, "Game in process. You can't join the battle.");
	e.map = (char *)e.data + sizeof(*e.data);
	e.msgqid = msgget(e.key, SHM_R | SHM_W);
	if (e.msgqid < 0)
		ft_exit_client(1, "msgget");
	e.creator = 0;
}
