/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/08 17:18:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>
#include <sys/msg.h>
#include "libft.h"
#include "ft_printf.h"
#include "lemipc.h"

static void			ft_init_gboard(t_game *game)
{
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(game->board, 0, sizeof(*game->board));
	game->board->map_width = MAP_WIDTH;
	game->board->map_heigth = MAP_HEIGTH;
	game->board->nb_players = 1;
	game->map = (ULL *)(game->board + 1);
	ft_memset(game->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
}

void				ft_create_game(t_game *game)
{
	struct sembuf	semops;

	ft_printf("Creating game...\n");
	game->shmid = shmget(game->key, game->size, LEMIPC_CREATE);
	if (game->shmid < 0)
		ft_exit(1, "shmget");
	ft_init_gboard(game);
	game->semid = semget(game->key, 1, LEMIPC_CREATE);
	if (game->semid < 0)
		ft_exit(1, "semget game IPC_CREAT");
	if (semctl(game->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl game SETVAL");
	semops.sem_num = 0;
	semops.sem_op = 1;
	semops.sem_flg = 0;
	if (semop(game->semid, &semops, 1) == -1)
		ft_exit(1, "semop team (init)");
	game->msgqid = msgget(game->key, LEMIPC_CREATE);
	if (game->msgqid < 0)
		ft_exit(1, "msgget game IPC_CREAT");
}

static void			ft_init_tboard(t_team *teams)
{
	teams->board = shmat(teams->shmid, NULL, 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(teams->board, 0, teams->size);
}

t_uid				*ft_create_team(const char *name, t_team *teams)
{
	t_uid			*team;
	struct sembuf	semops;

	ft_printf("Creating team...\n");
	teams->shmid = shmget(teams->key, teams->size, LEMIPC_CREATE);
	if (teams->shmid < 0)
		ft_exit(1, "shmget");
	ft_init_tboard(teams);
	*(size_t *)teams->board = 1;
	team = (t_uid *)((size_t *)teams->board + 1);
	ft_strncpy(team->name, name, TEAMNAME_MAX - 1);
	team->uid = 1;
	team->total = 1;
	teams->semid = semget(teams->key, 1, LEMIPC_CREATE);
	if (teams->semid < 0)
		ft_exit(1, "semget team IPC_CREAT");
	if (semctl(teams->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl team SETVAL");
	semops.sem_num = 0;
	semops.sem_op = 1;
	semops.sem_flg = 0;
	if (semop(teams->semid, &semops, 1) == -1)
		ft_exit(1, "semop team (init)");
	return (team);
}
