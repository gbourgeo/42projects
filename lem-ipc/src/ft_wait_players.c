/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/21 21:49:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void			ft_quit(char *err)
{
	*((int *)e.data + e.team) -= 1;
	if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
		*(e.map + e.x + e.y * WIDTH) = 0;
	if (TEAMS_SUMM > 0)
		ft_exit_client(1, err);
	ft_exit_server(1, err);
}

static void			ft_place_player(void)
{
	printf("Placing your player... ");
	while (1)
	{
		e.x = rand() % WIDTH;
		e.y = rand() % HEIGTH;
		if (*(e.map + e.x + e.y * HEIGTH) != 0)
			continue ;
		*(e.map + e.x + e.y * HEIGTH) = e.team;
		break ;
	}
	printf("(x:%d, y:%d)\n", e.x + 1, e.y + 1);
}

void				ft_wait_players(void)
{
	srand(time(NULL));
	ft_place_player();
	ft_unlock();
	ft_termdo("sc");
	while (TEAMS_SUMM < MIN_PLAYERS || TEAM_1 != TEAM_2)
	{
		print_map();
		if (TEAMS_SUMM < MIN_PLAYERS)
			printf("\033[32mWAITING FOR PLAYERS... (%d more)\033[0m\n",
					MIN_PLAYERS - TEAMS_SUMM);
		else
			printf("\033[34mWAITING FOR EVEN TEAMS...\033[0m\n");
		printf("one:%d two:%d\n", TEAM_1, TEAM_2);
		usleep(800);
		ft_termdo("rc");
		ft_termdo("cd");
	}
	e.data->game_in_process = 1;
	if ((e.ally = malloc(sizeof(*e.ally) * TEAM_1)) == NULL)
		ft_quit("malloc");
	if ((e.ennemy = malloc(sizeof(*e.ennemy) * TEAM_2)) == NULL)
		ft_quit("malloc");
}

void			print_map(void)
{
	int				i;
	int				j;
	char			c;

	i = 0;
	printf("Your team is %d\n", e.team);
	while (i < HEIGTH)
	{
		j = 0;
		while (j < WIDTH)
		{
			c = *(e.map + (i * WIDTH + j));
			c = (c == 0) ? '.' : c + '0';
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
