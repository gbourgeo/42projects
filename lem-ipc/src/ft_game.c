/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/12 19:26:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static int		ft_check_if_surrounded(char ennemy)
{
	int			surr;

	surr = 0;
	if (e.x > 0 && e.y > 0 &&
		*(e.map + (e.x - 1) + ((e.y - 1) * WIDTH)) == ennemy)
		surr++;
	if (e.y > 0 && *(e.map + e.x + ((e.y - 1) * WIDTH)) == ennemy)
		surr++;
	if (e.x < WIDTH - 1 && e.y > 0 &&
		*(e.map + (e.x + 1) + ((e.y - 1) * WIDTH)) == ennemy)
		surr++;
	if (e.x < WIDTH - 1 && *(e.map + (e.x + 1) + (e.y * WIDTH)) == ennemy)
		surr++;
	if (e.x < WIDTH - 1 && e.y < HEIGTH - 1 &&
		*(e.map + (e.x + 1) + ((e.y + 1) * WIDTH)) == ennemy)
		surr++;
	if (e.y < HEIGTH - 1 && *(e.map + e.x + ((e.y + 1) * WIDTH)) == ennemy)
		surr++;
	if (e.x > 0 && e.y < HEIGTH - 1 &&
		*(e.map + (e.x - 1) + ((e.y + 1) * WIDTH)) == ennemy)
		surr++;
	if (e.x > 0 && *(e.map + (e.x - 1) + e.y * WIDTH) == ennemy)
		surr++;
	return (surr);
}

void			ft_launch_game(void)
{
	char		ennemy;

	ennemy = (e.team == 1) ? 2 : 1;
	while (1)
	{
		ft_lock();
		if (e.creator)
			print_map();
		if (e.data->end)
			break ;
		if (ft_check_if_surrounded(ennemy) >= 2)
			ft_exit(0, "I am surrounded ! Aaaaaargh...");
		ft_strategy();
		if (TEAM_1 < 2 || TEAM_2 < 2)
			e.data->end = (TEAM_1 < 2) ? 2 : 1;
		ft_unlock();
		sleep(1);
	}
	*(e.map + e.x + e.y * WIDTH) = 0;
	*((int *)e.data + e.team) -= 1;
	if (TEAMS_SUMM > 0)
		ft_exit_client(0, (e.data->end == 1) ? "Team 1 Wins." : "Team 2 Wins.");
	ft_exit_server(0, (e.data->end == 1) ? "Team 1 Wins." : "Team 2 Wins.");
}
