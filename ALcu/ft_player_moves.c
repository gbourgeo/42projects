/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 22:09:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/10 05:18:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int			ft_player_shot(t_env *e)
{
	int			ret;
	int			pos;
	char		*buf;

	ft_print_info(e->board, PLAYER);
	while ((ret = get_next_line(0, &buf)) > 0)
	{
		if (!(pos = check_buf(buf, e->y)) || ft_check_board(PLAYER, pos - 1, e))
		{
			ft_putstr(buf);
			ft_putendl(" <- Wrong argument.");
			free(buf);
			buf = NULL;
			ft_print_info(e->board, PLAYER);
		}
		else
			break;
	}
	write(1, "\n", 1);
	free(buf);
	buf = NULL;
	return (COMPUT);
}
