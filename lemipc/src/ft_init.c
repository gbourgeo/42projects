/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:52:36 by root              #+#    #+#             */
/*   Updated: 2018/09/12 17:38:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void		init_game(const char *prog, t_game *game)
{
	game->key = ftok(prog, 'G');
	if (game->key == -1)
		ft_exit(1, "ftok");
	game->size = MAP_WIDTH * MAP_HEIGTH * sizeof(*game->map) + sizeof(*game->board);
	game->shmid = shmget(game->key, 0, SHM_R | SHM_W);
	game->semid = -1;
	game->msgqid = -1;
	game->board = (void *)-1;
	game->map = (void *)0;
}

void		init_team(const char *prog, t_team *team)
{
	team->key = ftok(prog, 'B');
	if (team->key == -1)
		ft_exit(1, "ftok");
	team->size = sizeof(*team);
	team->shmid = shmget(team->key, 0, SHM_R | SHM_W);
	team->semid = -1;
	team->board = (void *)-1;
}

void		init_child(t_child *child)
{
	child->gameid = -1;
	child->game = (void *)-1;
	child->teamsid = -1;
	child->teams = (void *)-1;
}
