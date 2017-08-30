/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 21:23:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

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

static void		check_who_wins(int *players)
{
	size_t		nb_teams;
	int			*ptr;

	nb_teams = 0;
	ptr = players;
	while (ptr - players < MAX_TEAMS)
		nb_teams += (*ptr++ > 1) ? 1 : 0;
	if (nb_teams == 1)
	{
		ptr = players;
		while (ptr - players < MAX_TEAMS && *ptr < 2)
			ptr++;
		e.data->end = ptr - players;
	}
}

void			ft_launch_game(void)
{
	while (e.data->end == -1)
	{
		if (e.creator)
			print_map();
		if (ft_check_if_surrounded(e.team, 0, 0) > 1)
			break ;
		ft_lock(e.semid);
		ft_strategy();
		ft_unlock(e.semid);
		check_who_wins(e.data->connected);
		sleep(1);
	}
	*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	e.data->connected[e.team] -= 1;
	while (e.data->end == -1 && e.creator)
		print_map();
	if (e.data->end != -1 && e.creator)
		printf("Team %d has won the game !!!\n", e.data->end);
	ft_free_exit();
}
