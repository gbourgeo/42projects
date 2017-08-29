/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/29 23:56:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void		ft_quit(char *err)
{
	if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
		*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	if (ft_nb_players(e.data->connected) > 1)
		ft_exit_client(1, err);
	ft_exit_server(1, err);
}

static void		ft_place_player(void)
{
	printf("Positionning your player... ");
	while (1)
	{
		e.x = rand() % MAP_WIDTH;
		e.y = rand() % MAP_HEIGTH;
		if (*(e.map + e.x + e.y * MAP_HEIGTH) != -1)
			continue ;
		*(e.map + e.x + e.y * MAP_HEIGTH) = e.team;
		break ;
	}
	printf("x:%d, y:%d\n", e.x + 1, e.y + 1);
	printf("Your team is %d\n", e.team);
	ft_termdo("sc");
}

int				ft_check_minimum_players(int *table)
{
	size_t		tot;
	int			*ptr;

	tot = 0;
	ptr = table;
	while (ptr - table < MAX_TEAMS)
		tot += *ptr++;
	if (tot < MIN_PPT * MIN_TEAMS)
		printf("\033[32mWAITING FOR PLAYERS... (%ld needed)\033[0m\n",
			   MIN_PPT * MIN_TEAMS - tot);
	return (tot >= MIN_PPT * MIN_TEAMS);
}

int				ft_check_even_teams(int *table)
{
	int			last;
	int			ret;
	int			*ptr;

	last = 0;
	ret = 0;
	ptr = table;
	while (ptr - table < MAX_TEAMS)
	{
		if (*ptr > 0)
		{
			ret = (last == *ptr) ? 1 : 0;
			last = *ptr;
		}
		ptr++;
	}
	printf("\033[34mWAITING FOR EVEN TEAMS...\033[0m\n");
	return (ret);
}

void			ft_wait_players(void)
{
	int			i;

	srand(time(NULL));
	ft_place_player();
	ft_unlock();
	while (!ft_check_minimum_players(e.data->connected) ||
			!ft_check_even_teams(e.data->connected))
	{
		if (e.creator)
			print_map();
		i = 0;
		while (i++ < MAX_TEAMS)
			printf("%d:%d ", i - 1, e.data->connected[i - 1]);
		printf("\n");
		sleep(1);
		ft_termdo("rc");
		ft_termdo("cd");
	}
	e.data->game_in_process = 1;
	i = ft_nb_players(e.data->connected);
	if ((e.players = malloc(sizeof(*e.players) * i)) == NULL)
		ft_quit("malloc");
}
