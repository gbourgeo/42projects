/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_for_a_winner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 05:58:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/10 06:56:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int	ft_check_horizontaly(int turns, t_env *e);

int			ft_check_for_a_winner(int turns, t_env *e)
{
	if (ft_check_horizontaly(turns, e) == turns)
		return (turns);
	return (e->x * e->y + 1);
}

static int	ft_check_horizontaly(int turns, t_env *e)
{
	int		lin;
	int		col;

	lin = e->x - 1;
	while (lin >= 0)
	{
		col = 0;
		while (col < e->y)
		{
			if (e->board[lin][col] != EMPTY)
			{
				ft_putendl("ok1");
				while (col < e->y
					   && e->board[lin][col] == e->board[lin][col + 1])
					col++;
				ft_putendl("ok2");
				if (col >= 4)
					return (0);
			}
			col++;
		}
		lin--;
	}
	return (turns);
}

/* static int	ft_check_verticaly(int turns, t_env *e) */
/* { */
/* 	int		lin; */
/* 	int		col; */

/* 	lin = e->x - 1; */
