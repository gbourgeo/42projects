/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 08:59:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/07 13:19:36 by naminei          ###   ########.fr       */
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
	game->shmid = shmget(game->key, 0, 0);
	game->semid = semget(game->key, 0, 0);
	game->msgqid = msgget(game->key, 0);
	game->board = shmat(game->shmid, (void *)0, 0);
	game->map = (void *)0;
}

void		init_team(const char *prog, t_team *teams)
{
	teams->key = ftok(prog, 'B');
	if (teams->key == -1)
		ft_exit(1, "ftok");
	teams->size = sizeof(size_t) + sizeof(*e.team) * MAX_TEAMS;
	teams->shmid = shmget(teams->key, 0, 0);
	teams->semid = semget(teams->key, 1, 0);
	teams->board = shmat(teams->shmid, (void *)0, 0);
}
