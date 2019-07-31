/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ingame_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 00:31:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/31 19:44:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int			ft_check_buf(char *buf, int y)
{
	int			i;
	int			col;

	i = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i++]) == 0)
			return (0);
	}
	if ((col = ft_atoi(buf)) > y || col <= 0)
		return (0);
	return (col);
}

int			ft_check_board(int player, int pos, t_env *e)
{
	int			i;

	i = e->x - 1;
	while (i >= 0 && e->board[i][pos] != EMPTY)
		i--;
	if (i < 0)
		return (1);
	if (player == PLAYER)
		e->board[i][pos] = 'O';
	else
		e->board[i][pos] = 'X';
	return (0);
}
