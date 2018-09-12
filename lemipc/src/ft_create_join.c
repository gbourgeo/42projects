/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 17:54:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <sys/sem.h>
#include <sys/msg.h>

void				ft_create_game(t_game *game)
{
	struct msqid_ds	buf;

	game->shmid = shmget(game->key, game->size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (game->shmid < 0)
		ft_exit(1, "shmget");
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(game->board, 0, sizeof(*game->board));
	game->board->nb_players = 1;
	game->map = (ULL *)game->board + sizeof(*game->board);
	ft_memset(game->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
	game->semid = semget(game->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (game->semid < 0)
		ft_exit(1, "semget IPC_CREAT");
	if (semctl(game->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl SETVAL");
	game->msgqid = msgget(game->key, IPC_CREAT | SHM_R | SHM_W);
	if (game->msgqid < 0)
		ft_exit(1, "msgget IPC_CREAT");
	if (msgctl(game->msgqid, IPC_STAT, &buf) < 0)
		ft_exit(1, "msgctl IPC_STAT");
}

t_uid				*ft_create_team(const char *name, t_team *team)
{
	team->shmid = shmget(team->key, team->size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (team->shmid < 0)
		ft_exit(1, "shmget");
	team->board = shmat(team->shmid, NULL, 0);
	if (team->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(team->board, 0, sizeof(*team));
	team->board->name = name;
	team->board->uid = 1;
	team->board->total = 1;
	team->semid = semget(team->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (team->semid < 0)
		ft_exit(1, "semget IPC_CREAT");
	if (semctl(team->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl SETVAL");
	return (team->board);
}

void				ft_create_child(t_child *child)
{
	key_t			key;

	key = ftok(e.prog, 'G');
	if (key == -1)
		ft_exit_child(1, "child: ftok");
	child->gameid = shmget(key, 0, SHM_R);
	if (child->gameid < 0)
		ft_exit_child(1, "child: shmget");
	child->game = shmat(child->gameid, NULL, 0);
	if (child->game == (void *)-1)
		ft_exit_child(1, "child: shmgat");
	key = ftok(e.prog, 'B');
	if (key == -1)
		ft_exit_child(1, "child: ftok");
	child->teamsid = shmget(key, 0, SHM_R);
	if (child->teamsid < 0)
		ft_exit_child(1, "child: shmget");
	child->teams = shmat(child->teamsid, NULL, 0);
	if (child->teams == (void *)-1)
		ft_exit_child(1, "child: shmgat");
}

void				ft_join_game(t_game *game)
{
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	game->map = (ULL *)game->board + sizeof(*game->board);
	game->semid = semget(game->key, 1, SHM_R | SHM_W);
	if (game->semid < 0)
		ft_exit(1, "semget");
	game->msgqid = msgget(game->key, SHM_R | SHM_W);
	if (game->msgqid < 0)
		ft_exit(1, "msgget");
	if (game->board->nb_players >= MAP_WIDTH * MAP_HEIGTH - 1)
		ft_exit(0, "Game is full.\n");
	/* if (game->data->game_in_process > 0) */
	/* 	ft_exit(0, "Game in process. You can't join the battle."); */
}

t_uid				*ft_join_team(const char *name, t_team *team)
{
	(void)name;
	return (team->board);
}
