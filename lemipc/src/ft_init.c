/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:52:36 by root              #+#    #+#             */
/*   Updated: 2018/09/20 10:18:33 by gbourgeo         ###   ########.fr       */
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

void		init_team(const char *prog, t_team *team)
{
	team->key = ftok(prog, 'B');
	if (team->key == -1)
		ft_exit(1, "ftok");
	team->size = sizeof(*team->board) * 2 + sizeof(size_t);
	team->shmid = shmget(team->key, 0, SHM_R | SHM_W);
	team->semid = semget(team->key, 1, SHM_R | SHM_W);;
	team->board = shmat(team->shmid, (void *)0, 0);
}
