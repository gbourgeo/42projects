/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/12 13:16:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void			print_map(void)
{
	int				i;
	int				j;
	char			c;

	i = 0;
	while (i < HEIGTH)
	{
		j = 0;
		while (j < WIDTH)
		{
			c = *(e.map + (i * WIDTH + j));
			c = (c == -1) ? '.' : c + '0';
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

static void			ft_place_player(void)
{
	printf("Placing your player... ");
	while (1)
	{
		e.x = rand() % WIDTH;
		e.y = rand() % HEIGTH;
		if (*(e.map + e.x + e.y * HEIGTH) != -1)
			continue ;
		*(e.map + e.x + e.y * HEIGTH) = e.team;
		break ;
	}
	printf("(x:%d, y:%d)\n", e.x + 1, e.y + 1);
}

void				ft_loop(void)
{
	srand(time(NULL));
	ft_place_player();
	ft_unlock();
	ft_termdo("sc");
	while (e.data->connected < MIN_PLAYERS || e.data->one != e.data->two)
	{
		print_map();
		if (e.data->connected < MIN_PLAYERS)
			printf("\033[32mWAITING FOR PLAYERS... (%d more)\033[0m\n",
					MIN_PLAYERS - e.data->connected);
		else
			printf("\033[34mWAITING FOR EVEN TEAMS...\033[0m\n");
		printf("one:%d two:%d\n", e.data->one, e.data->two);
		usleep(800);
		ft_termdo("rc");
		ft_termdo("cd");
	}
}
