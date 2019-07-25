/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 15:48:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/09 23:07:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static char		**ft_create_board(int x, int y)
{
	char		**board;
	int			len;

	if ((board = (char**)malloc(sizeof(char*) * x + 1)) == NULL)
		return (NULL);
	board[x] = '\0';
	while (--x >= 0)
	{
		len = 0;
		if ((board[x] = ft_strnew(y + 1)) == NULL)
			return (NULL);
		while (len < y)
			board[x][len++] = ' ';
	}
	return (board);
}

int				main(int ac, char **av)
{
	t_env		e;

	if (!ft_param_error(ac, av))
	{
		e.x = ft_atoi(av[1]);
		e.y = ft_atoi(av[2]);
		if ((e.board = ft_create_board(e.x, e.y)) == NULL)
			return (1);
		ft_play_game(&e);
		return (0);
	}
	return (1);
}
