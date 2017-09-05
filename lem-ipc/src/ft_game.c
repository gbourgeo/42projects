/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/05 21:35:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static int		ft_check_if_surrounded(int team, int surr, int c)
{
	c = *(e.map + (e.x - 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x > 0 && e.y > 0 && c != -1 && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y - 1) * MAP_WIDTH));
	if (e.y > 0 && c != -1 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y > 0 && c != -1 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + (e.y * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && c != -1 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y < MAP_HEIGTH - 1 && c != -1 && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y + 1) * MAP_WIDTH));
	if (e.y < MAP_HEIGTH - 1 && c != -1 && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x > 0 && e.y < MAP_HEIGTH - 1 && c != -1 && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + e.y * MAP_WIDTH);
	if (e.x > 0 && c != -1 && c != team)
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
		ft_unlock(e.semid);
		sleep(1);
	}
	if (e.creator)
		waitpid(e.pid, &e.creator, 0);
	*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	e.data->connected[e.team] -= 1;
	ft_free_exit();
}
