/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 00:11:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static int		ft_check_if_surrounded(int team)
{
	int			c;
	int			surr;

	surr = 0;
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
	if (e.x < MAP_WIDTH - 1 && c != -1 && c !=team)
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
	printf((surr < 2 ? "" : "I'm surrouded. Aaaaargh !\n"));
	return (surr);
}

static void		check_who_wins(int *players)
{
	size_t		nb_teams;
	int			*ptr;

	nb_teams = 0;
	ptr = players;
	while (ptr - players < MAX_TEAMS)
		nb_teams += (*ptr++ > 0) ? 1 : 0;
	ft_putnbr(nb_teams);
	if (nb_teams == 1)
	{
		ptr = players;
		while (ptr - players < MAX_TEAMS && *ptr == 0)
			ptr++;
		e.data->end = ptr - players;
	}
}

void			ft_launch_game(void)
{
	char		*winner;

	winner = NULL;
	ft_termdo("rc");
	ft_termdo("cd");
	ft_putendl("\033[1;32mGAME IN PROGRESS...\033[00m");
	ft_termdo("sc");
	while (e.data->end == -1)
	{
		if (e.creator)
			print_map();
		ft_lock();
		if (ft_check_if_surrounded(e.team) > 1)
			break ;
/* 		ft_strategy(); */
		check_who_wins(e.data->connected);
		ft_unlock();
		sleep(1);
	}
	*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	winner = (e.data->end == (int)e.team) ? "You Won !" : "You Looses...";
	if (ft_nb_players(e.data->connected) > 1)
		ft_exit_client(0, winner);
	ft_exit_server(0, winner);
}
