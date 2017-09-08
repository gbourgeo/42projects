/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/07 17:05:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <unistd.h>
#include <sys/wait.h>

/*
** check_if_surrouded() check order:
** 2 3 4
** 1 . 5
** 8 7 6
*/

static int		ft_check_if_surrounded(int team, int surr, int c)
{
	c = *(e.map + (e.x - 1) + e.y * MAP_WIDTH);
	if (e.x % MAP_WIDTH > 0 && c != MV && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x % MAP_WIDTH > 0 && e.y > 0 && c != MV && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y - 1) * MAP_WIDTH));
	if (e.y > 0 && c != MV && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y > 0 && c != MV && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + (e.y * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && c != MV && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y < MAP_HEIGTH - 1 && c != MV && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y + 1) * MAP_WIDTH));
	if (e.y < MAP_HEIGTH - 1 && c != MV && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x % MAP_WIDTH > 0 && e.y < MAP_HEIGTH - 1 && c != MV && c != team)
		surr++;
	return (surr);
}

static void		check_who_won(int *teams)
{
	int			*ptr;
	int			*winner;

	ptr = teams;
	winner = NULL;
	while (ptr - teams < MAX_TEAMS)
	{
		if (*ptr > 1)
		{
			if (winner == NULL)
				winner = ptr;
			else
				return ;
		}
		ptr++;
	}
	if (winner)
		e.data->end = winner - teams;
}

void			ft_launch_game(void)
{
	while (e.data->end == -1)
	{
		ft_lock(e.semid);
		if (ft_check_if_surrounded(e.team, 0, 0) > 1)
			break ;
		ft_strategy();
		check_who_won(e.data->connected);
		sleep(1);
		ft_unlock(e.semid);
	}
	*(e.map + e.x + e.y * MAP_WIDTH) = MAP_VALUE;
	e.data->connected[e.team] -= 1;
	if (e.creator)
		waitpid(e.pid, &e.creator, 0);
	ft_free_exit();
}
