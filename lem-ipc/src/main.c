/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 00:12:51 by root              #+#    #+#             */
/*   Updated: 2016/10/28 18:33:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

static void			ft_usage(t_env *e)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(e->prog, 2);
	ft_putstr_fd(" [team number]\n", 2);
	exit(1);
}

static void			ft_create_game(t_env *e)
{
	struct msqid_ds	buf;

	perror("shmget");
	e->shmid = shmget(e->key, e->size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (e->shmid < 0)
		ft_err("shmget", e);
	printf("e->shmid: %d\n", e->shmid);
	e->map = shmat(e->shmid, NULL, 0);
	if (e->map == (void *)-1)
		ft_err("shmat", e);
	ft_bzero(e->map, WIDTH * HEIGTH + sizeof(t_map));
	e->semid = semget(e->key, 1, IPC_CREAT | SHM_R | SHM_W);
	if (e->semid < 0)
		ft_err("semget IPC_CREAT", e);
	printf("e->semid: %d\n", e->semid);
	if (semctl(e->semid, 0, SETVAL, 1) < 0)
		ft_err("semctl SETVAL", e);
	e->msgqid = msgget(e->key, IPC_CREAT | SHM_R | SHM_W);
	if (e->msgqid < 0)
		ft_err("msgget IPC_CREAT", e);
	if (msgctl(e->msgqid, IPC_STAT, &buf) < 0)
		ft_err("msgctl IPC_STAT", e);
	printf("time: %ld\n", buf.msg_ctime);
}

static void			ft_join_game(t_env *e)
{
	e->map = shmat(e->shmid, NULL, 0);
	if (e->map == (void *)-1)
		ft_err("shmat", e);
	if (e->map->connected >= MAX_PLAYERS)
		ft_err2("Too many players are already in game.", e);
	e->semid = semget(e->key, 1, SHM_R | SHM_W);
	if (e->semid < 0)
		ft_err("semget", e);
	printf("semid found: %d\n", e->semid);
	e->msgqid = msgget(e->key, SHM_R | SHM_W);
	if (e->msgqid < 0)
		ft_err("msgget", e);
}

int					main(int ac, char **av)
{
	t_env			e;

	(void)ac;
	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(av[0], '/');
	if (e.prog == NULL)
		e.prog = av[0];
	if (!av[1])
		ft_usage(&e);
	e.team = ft_atoi(av[1]);
	if (e.team < 0)
		ft_err2("Error: Team number must be > 0", &e);
	e.key = ftok(e.prog, 1);
	if (e.key == -1)
		ft_err("ftok", &e);
	printf("e.key: %d\n", e.key);
	ft_signal(&e);
	e.size = WIDTH * HEIGTH + sizeof(t_map);
	if (e.size <= 0)
		ft_err2("Error: map size <= 0", &e);
	e.shmid = shmget(e.key, e.size, SHM_R | SHM_W);
	if (e.shmid < 0)
		ft_create_game(&e);
	else
		ft_join_game(&e);
	printf("Your team will be: %d\n", e.team);
	return (0);
}
