/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 08:59:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/12 20:34:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

void		init_game(const char *prog, t_game *game)
{
	game->key = ftok(prog, 'G');
	if (game->key == -1)
		ft_exit(1, "ftok");
	game->size = sizeof(*game->board) +
		(MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map));
	game->shmid = shmget(game->key, 0, SHM_R | SHM_W);
	game->semid = semget(game->key, 1, SHM_R | SHM_W);
	game->msgqid = msgget(game->key, SHM_R | SHM_W);
	game->board = shmat(game->shmid, (void *)0, 0);
	game->map = (void *)0;
}

void		init_team(const char *prog, t_team *teams)
{
	teams->key = ftok(prog, 'B');
	if (teams->key == -1)
		ft_exit(1, "ftok");
	teams->size = sizeof(size_t) + sizeof(*e.team) * MAX_TEAMS;
	teams->shmid = shmget(teams->key, 0, SHM_R | SHM_W);
	teams->semid = semget(teams->key, 1, SHM_R | SHM_W);
	teams->board = shmat(teams->shmid, (void *)0, 0);
}
