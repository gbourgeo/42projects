/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 22:32:31 by root             ###   ########.fr       */
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
	ft_strncpy(team->board->name, name, sizeof(team->board->name) - 1);
	team->board->uid = 1;
	team->board->total = 1;
	team->semid = semget(team->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (team->semid < 0)
		ft_exit(1, "semget IPC_CREAT");
	if (semctl(team->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl SETVAL");
	return (team->board);
}

void				ft_join_game(t_game *game)
{
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	game->board->nb_players++;
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

t_uid				*ft_join_team(const char *name, t_team *teams)
{
	size_t			size;
	t_uid			*team;

	size = 0;
	teams->board = shmat(teams->shmid, NULL, 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	team = teams->board;
	while (size < teams->size)
	{
		if (!ft_strcmp((team + size)->name, name))
		{
			ft_lock(teams->semid);
			(team + size)->total++;
			ft_unlock(teams->semid);
			return (team + size);
		}
		size += sizeof(*team);
	}
	ft_lock(teams->semid);
	teams->size += sizeof(*team);
	ft_strncpy((team + size)->name, name, sizeof((team + size)->name) - 1);
	(team + size)->uid = size / sizeof(*team) + 1;
	(team + size)->total = 1;
	ft_unlock(teams->semid);
	return (team + size);
}
