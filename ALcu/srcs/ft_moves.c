/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:21:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/31 20:16:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "alcu.h"

int				ft_moves(t_env *e, int player)
{
	int		ret;
	int		pos;
	char	*buf;

	while ((ret = get_next_line(STDIN_FILENO, &buf)) > 0)
	{
		if (!(pos = ft_check_buf(buf, e->y))
			|| ft_check_board(player, pos - 1, e))
		{
			ft_putstr(buf);
			ft_putendl(" <- Wrong argument.");
			free(buf);
			buf = NULL;
		}
		else
			break ;
	}
	write(1, "\n", 1);
	free(buf);
	return ((player == PLAYER) ? COMPUT : PLAYER);
}
