/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_for_a_winner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 05:58:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/31 21:03:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int	ft_check_horizontaly(int lin, int col, t_env *e)
{
	int		p;

	p = 0;
	while (col < e->y
			&& e->board[lin][col] == e->board[lin][col + 1])
	{
		col++;
		p++;
	}
	return (p >= NUMBER_TO_WIN - 1);
}

static int	ft_check_verticaly(int lin, int col, t_env *e)
{
	int		p;

	p = 0;
	while (lin > 0
			&& e->board[lin][col] == e->board[lin - 1][col])
	{
		p++;
		lin--;
	}
	return (p >= NUMBER_TO_WIN - 1);
}

static int	ft_check_diagonaly(int lin, int col, t_env *e)
{
	int		p;

	p = 0;
	while (col < e->y && lin > 0
			&& e->board[lin][col] == e->board[lin - 1][col + 1])
	{
		p++;
		lin--;
		col++;
	}
	return (p >= NUMBER_TO_WIN - 1);
}

int			ft_check_for_a_winner(int turns, t_env *e)
{
	int		lin;
	int		col;

	lin = e->x;
	while (lin--)
	{
		col = 0;
		while (col < e->y)
		{
			if (e->board[lin][col] != EMPTY)
			{
				if (col + 3 < e->y && ft_check_horizontaly(lin, col, e))
					return (e->x * e->y + 1);
				if (lin - 3 >= 0 && ft_check_verticaly(lin, col, e))
					return (e->x * e->y + 1);
				if (col + 3 < e->y && lin - 3 >= 0
					&& ft_check_diagonaly(lin, col, e))
					return (e->x * e->y + 1);
			}
			col++;
		}
	}
	return (turns);
}
