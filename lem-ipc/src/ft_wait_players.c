/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/07 17:05:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include <time.h>

static void		ft_quit(char *err)
{
	if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
		*(e.map + e.x + e.y * MAP_WIDTH) = MAP_VALUE;
	if (ft_nb_players(e.data->connected) > 0)
		ft_exit_client(1, err);
	ft_exit_server(1, err);
}

static void		ft_place_player(void)
{
	while (1)
	{
		e.x = rand() % MAP_WIDTH;
		e.y = rand() % MAP_HEIGTH;
		if (*(e.map + e.x + e.y * MAP_HEIGTH) != MAP_VALUE)
			continue ;
		*(e.map + e.x + e.y * MAP_HEIGTH) = e.team;
		break ;
	}
}

void			ft_wait_players(void)
{
	int			i;

	srand(time(NULL));
	ft_lock(e.semid);
	e.data->connected[e.team] += 1;
	ft_place_player();
	ft_unlock(e.semid);
	while (ft_check_minimum_players(e.data->connected) ||
			ft_check_even_teams(e.data->connected))
		e.data->game_in_process = 0;
	e.data->game_in_process = 1;
	i = ft_nb_players(e.data->connected);
	if ((e.players = malloc(sizeof(*e.players) * i)) == NULL)
		ft_quit("malloc");
}
