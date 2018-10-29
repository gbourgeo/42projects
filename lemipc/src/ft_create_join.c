/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/25 04:15:39 by gbourgeo         ###   ########.fr       */
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

	ft_printf("Creating game...\n");
	game->shmid = shmget(game->key, game->size, LEMIPC_CREATE);
	if (game->shmid < 0)
		ft_exit(1, "shmget");
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(game->board, 0, sizeof(*game->board));
	game->board->map_width = MAP_WIDTH;
	game->board->map_heigth = MAP_HEIGTH;
	game->board->nb_players = 1;
	game->map = (ULL *)game->board + 1;
	ft_memset(game->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
	game->semid = semget(game->key, 1, LEMIPC_CREATE);
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

	ft_printf("Creating team...\n");
	teams->shmid = shmget(teams->key, teams->size, LEMIPC_CREATE);
	if (teams->shmid < 0)
		ft_exit(1, "shmget");
	teams->board = shmat(teams->shmid, NULL, 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	ft_memset(teams->board, 0, teams->size);
	*(size_t *)teams->board = 1;
	team = (t_uid *)teams->board + sizeof(size_t);
	ft_strncpy(team->name, name, TEAMNAME_MAX - 1);
	team->uid = 1;
	team->total = 1;
	teams->semid = semget(teams->key, 1, LEMIPC_CREATE);
	if (teams->semid < 0)
		ft_exit(1, "semget team IPC_CREAT");
	if (semctl(teams->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl team SETVAL");
	return (team);
}

void				ft_join_game(t_game *game)
{
	ft_printf("Joining game...\n");
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	game->board->nb_players++;
	game->map = (ULL *)(game->board + 1);
	if (game->semid < 0)
		ft_exit(1, "semget");
	if (game->msgqid < 0)
		ft_exit(1, "msgget");
	if (game->board->game_in_process)
		ft_exit(0, "Game in process... Come back later !");
}

static t_uid		*ft_join_info(const char *name, t_uid *team, size_t size, t_team *teams)
{
	ft_lock(teams->semid);
	if (!ft_strcmp((team + size)->name, name))
		(team + size)->total++;
	else
	{
		ft_strncpy((team + size)->name, name, TEAMNAME_MAX - 1);
		team->uid = size;
		team->total = 1;
		*(size_t *)teams->board += 1;
	}
	ft_unlock(teams->semid);
	return (team + size);
}

t_uid				*ft_join_team(const char *name, t_team *teams)
{
	size_t			size;
	t_uid			*team;

	ft_printf("Joining team...\n");
	if (teams->semid < 0)
		ft_exit(1, "semget");
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	size = 0;
	team = (t_uid *)teams->board + sizeof(size_t);
	while (size < *(size_t *)teams->board)
	{
		if (!ft_strcmp((team + size)->name, name))
			return (ft_join_info(name, team, size, teams));
		size++;
	}
	return (ft_join_info(name, team, size, teams));
}
