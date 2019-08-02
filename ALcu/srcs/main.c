/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 15:48:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 10:40:41 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static char		**ft_create_board(int x, int y)
{
	char		**board;
	int			len;

	if ((board = ft_memalloc(sizeof(*board) * (x + 1))) == NULL)
		return (NULL);
	board[x] = NULL;
	while (x--)
	{
		if ((board[x] = ft_strnew(y + 1)) == NULL)
		{
			while (board[++x])
				free(board[x]);
			free(board);
			return (NULL);
		}
		len = 0;
		while (len < y)
			board[x][len++] = EMPTY;
	}
	return (board);
}

static void		free_board(char **board)
{
	int			i;

	i = 0;
	if (!board)
		return ;
	while (board[i])
		free(board[i++]);
	free(board);
}

int				main(int ac, char **av)
{
	t_env		e;

	ft_memset(&e, 0, sizeof(e));
	if (!ft_param_error(ac, av))
	{
		e.x = ft_atoi(av[1]);
		e.y = ft_atoi(av[2]);
		if ((e.board = ft_create_board(e.x, e.y)) == NULL)
			return (1);
		ft_play_game(&e);
		free_board(e.board);
		return (0);
	}
	free_board(e.board);
	return (1);
}
