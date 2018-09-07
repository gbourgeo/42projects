/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 14:21:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

static int		ft_check_if_surrounded(int team, int surr, int c)
{
	c = *(e.map + (e.x - 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x > 0 && e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y - 1) * MAP_WIDTH));
	if (e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y - 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + (e.y * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + (e.x + 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x < MAP_WIDTH - 1 && e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + e.x + ((e.y + 1) * MAP_WIDTH));
	if (e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + ((e.y + 1) * MAP_WIDTH));
	if (e.x > 0 && e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(e.map + (e.x - 1) + e.y * MAP_WIDTH);
	if (e.x > 0 && c != MAP_0 && c != team)
		surr++;
	return (surr);
}

/* static void		check_who_wins(int *players) */
/* { */
/* 	size_t		nb_teams; */
/* 	int			*ptr; */

/* 	nb_teams = 0; */
/* 	ptr = players; */
/* 	while (ptr - players < MAX_TEAMS) */
/* 		nb_teams += (*ptr++ > 1) ? 1 : 0; */
/* 	if (nb_teams == 1) */
/* 	{ */
/* 		ptr = players; */
/* 		while (ptr - players < MAX_TEAMS && *ptr < 2) */
/* 			ptr++; */
/* 		e.data->end = ptr - players; */
/* 	} */
/* } */

void			ft_launch_game(void)
{
	while (e.data->players > 1)
	{
		if (e.creator)
			print_map();
		ft_lock(e.semid);
		if (ft_check_if_surrounded(e.team, 0, 0) > 1)
			break ;
		ft_strategy();
		ft_unlock(e.semid);
//		check_who_wins(e.data->connected);
		sleep(1);
	}
	*(e.map + GET_POS(e.x, e.y)) = MAP_0;
	e.data->players--;
	while (e.data->players && e.creator)
		print_map();
	if (e.data->winner && e.creator)
		ft_printf("Team %lld has won the game !!!\n", e.data->winner);
	ft_free_exit();
}
