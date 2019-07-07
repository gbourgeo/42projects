/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:37:12 by naminei           #+#    #+#             */
/*   Updated: 2019/07/07 14:43:39 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "lemipc.h"

void				ft_join_game(t_game *game)
{
	ft_printf("Joining game...\n");
	if (game->board == (void *)-1)
		ft_exit(1, "shmat");
	game->board->nb_players++;
	game->map = (ULL *)(game->board + 1);
	if (game->semid < 0)
		ft_exit(1, "semget");
	if (game->msgqid < 0)
		ft_exit(1, "msgget");
	if (game->board->game_in_process)
		ft_exit(0, "Game in process... Come back later !");
}

static t_uid		*ft_join_info(const char *name, t_uid *team, size_t size,
t_team *teams)
{
	ft_lock(teams);
	if (!ft_strcmp((team + size)->name, name))
		(team + size)->total++;
	else if (*(size_t *)teams->board >= MAX_TEAMS - 1)
	{
		ft_unlock(teams);
		return (NULL);
	}
	else
	{
		size = 0;
		while (size < *(size_t *)teams->board)
			if ((team + size)->total == 0)
				break ;
			else
				++size;
		ft_strncpy((team + size)->name, name, TEAMNAME_MAX - 1);
		(team + size)->uid = size + 1;
		(team + size)->total = 1;
		*(size_t *)teams->board += 1;
	}
	ft_unlock(teams);
	return (team + size);
}

t_uid				*ft_join_team(const char *name, t_team *teams)
{
	size_t			size;
	t_uid			*team;

	ft_printf("Joining team...\n");
	if (teams->semid < 0)
		ft_exit(1, "semget");
	if (teams->board == (void *)-1)
		ft_exit(1, "shmat");
	size = 0;
	team = (t_uid *)((size_t *)teams->board + 1);
	while (size < *(size_t *)teams->board)
	{
		if (!ft_strcmp((team + size)->name, name))
			return (ft_join_info(name, team, size, teams));
		size++;
	}
	return (ft_join_info(name, team, size, teams));
}
