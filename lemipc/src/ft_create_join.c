/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/20 10:07:21 by gbourgeo         ###   ########.fr       */
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
	game->board->map_width = MAP_WIDTH;
	game->board->map_heigth = MAP_HEIGTH;
	game->board->nb_players = 0;
	game->map = (ULL *)(game->board + 1);
	ft_memset(game->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
	game->semid = semget(game->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (game->semid < 0)
		ft_exit(1, "semget game IPC_CREAT");
	if (semctl(game->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl game SETVAL");
	game->msgqid = msgget(game->key, IPC_CREAT | SHM_R | SHM_W);
	if (game->msgqid < 0)
		ft_exit(1, "msgget game IPC_CREAT");
	if (msgctl(game->msgqid, IPC_STAT, &buf) < 0)
		ft_exit(1, "msgctl game IPC_STAT");
}

t_uid				*ft_create_team(const char *name, t_team *teams)
{
	t_uid			*team;

	teams->shmid = shmget(teams->key, teams->size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (teams->shmid < 0)
		ft_exit(1, "shmget");
	teams->board = shmat(teams->shmid, NULL, 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(teams->board, 0, teams->size);
	ft_memcpy(teams->board, &teams->size, sizeof(teams->size));
	team = teams->board + sizeof(teams->size);
	ft_strncpy(team->name, name, TEAMNAME_MAX - 1);
	team->uid = 1;
	team->total = 1;
	teams->semid = semget(teams->key, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	if (teams->semid < 0)
		ft_exit(1, "semget team IPC_CREAT");
	if (semctl(teams->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl team SETVAL");
	return (team);
}

void				ft_join_game(t_game *game)
{
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	game->map = (ULL *)(game->board + 1);
	if (game->semid < 0)
		ft_exit(1, "semget");
	if (game->msgqid < 0)
		ft_exit(1, "msgget");
	if (game->board->game_in_process)
		ft_exit(0, "Game in process... Come back later !");
}

t_uid				*ft_join_team(const char *name, t_team *teams)
{
	size_t			size;
	t_uid			*team;

	if (teams->semid < 0)
		ft_exit(1, "semget");
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	size = sizeof(size);
	team = teams->board;
	while (size < *(size_t *)team)
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
	ft_printf("Adding one...\n");
	ft_lock(teams->semid);
	ft_printf("1\n");
	ft_strncpy((team + size)->name, name, TEAMNAME_MAX - 1);
	ft_printf("1\n");
	(team + size)->uid = size / sizeof(*team) + 1;
	ft_printf("1\n");
	(team + size)->total = 1;
	ft_printf("1\n");
	*(size_t *)team += sizeof(*team);
	ft_printf("1\n");
	ft_unlock(teams->semid);
	ft_printf("1\n");
	return (team + size);
}
