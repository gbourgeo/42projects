/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:09:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/28 17:15:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>
#include <sys/msg.h>
#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"

void				ft_create_game(t_game *game)
{
	struct msqid_ds	buf;

	ft_printf("Creating game...\n");
	game->shmid = shmget(game->key, game->size, LEMIPC_CREATE);
	if (game->shmid < 0)
		ft_exit(1, "shmget", 0);
	game->board = shmat(game->shmid, NULL, 0);
	if (game->board == (void *)-1)
		ft_exit(1, "shmat", 0);
	ft_memset(game->board, 0, sizeof(*game->board));
	game->board->map_width = MAP_WIDTH;
	game->board->map_heigth = MAP_HEIGTH;
	game->board->nb_players = 1;
	game->map = (ULL *)(game->board + 1);
	ft_memset(game->map, MAP_0, MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
	game->semid = semget(game->key, 1, LEMIPC_CREATE);
	if (game->semid < 0)
		ft_exit(1, "semget game IPC_CREAT", 0);
	if (semctl(game->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl game SETVAL", 0);
	game->msgqid = msgget(game->key, LEMIPC_CREATE);
	if (game->msgqid < 0)
		ft_exit(1, "msgget game IPC_CREAT", 0);
	if (msgctl(game->msgqid, IPC_STAT, &buf) < 0)
		ft_exit(1, "msgctl game IPC_STAT", 0);
}

t_uid				*ft_create_team(const char *name, t_team *teams)
{
	t_uid			*team;

	ft_printf("Creating team...\n");
	teams->shmid = shmget(teams->key, teams->size, LEMIPC_CREATE);
	if (teams->shmid < 0)
		ft_exit(1, "shmget", 0);
	teams->board = shmat(teams->shmid, NULL, 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat", 0);
	ft_memset(teams->board, 0, teams->size);
	*(size_t *)teams->board = 1;
	team = (t_uid *)((size_t *)teams->board + 1);
	ft_strncpy(team->name, name, TEAMNAME_MAX - 1);
	team->uid = 1;
	team->total = 1;
	teams->semid = semget(teams->key, 1, LEMIPC_CREATE);
	if (teams->semid < 0)
		ft_exit(1, "semget team IPC_CREAT", 0);
	if (semctl(teams->semid, 0, SETVAL, 0) < 0)
		ft_exit(1, "semctl team SETVAL", 0);
	return (team);
}

void				ft_join_game(t_game *game)
{
	ft_printf("Joining game...\n");
	if (game->board == (void *)-1)
		ft_exit(1, "shmat", 0);
	game->board->nb_players++;
	game->map = (ULL *)(game->board + 1);
	if (game->semid < 0)
		ft_exit(1, "semget", 0);
	if (game->msgqid < 0)
		ft_exit(1, "msgget", 0);
	if (game->board->game_in_process)
		ft_exit(0, "Game in process... Come back later !", 0);
}

static t_uid		*ft_join_info(const char *name, t_uid *team, size_t size,
t_team *teams)
{
	ft_lock(teams->semid);
	if (!ft_strcmp((team + size)->name, name))
		(team + size)->total++;
	else if (*(size_t *)teams->board >= MAX_TEAMS - 1)
	{
		ft_unlock(teams->semid);
		return (NULL);
	}
	else
	{
		size = 0;
		while (size < *(size_t *)teams->board)
			if ((team + size)->total == 0)
				break ;
			else
				++size;
		ft_strncpy((team + size)->name, name, TEAMNAME_MAX - 1);
		(team + size)->uid = size + 1;
		(team + size)->total = 1;
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
		ft_exit(1, "semget", 0);
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat", 0);
	size = 0;
	team = (t_uid *)((size_t *)teams->board + 1);
	while (size < *(size_t *)teams->board)
	{
		if (!ft_strcmp((team + size)->name, name))
			return (ft_join_info(name, team, size, teams));
		size++;
	}
	return (ft_join_info(name, team, size, teams));
}
