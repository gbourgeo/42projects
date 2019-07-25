/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computer_moves.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 00:29:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/10 05:18:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int			ft_computer_shot(t_env *e)
{
	int			ret;
	int			pos;
	char		*buf;

	ft_print_info(e->board, COMPUT);
	while ((ret = get_next_line(0, &buf)) > 0)
	{
		if (!(pos = check_buf(buf, e->y)) || ft_check_board(COMPUT, pos - 1, e))
		{
			ft_putstr(buf);
			ft_putendl(" <- Wrong argument.");
			free(buf);
			buf = NULL;
			ft_print_info(e->board, COMPUT);
		}
		else
			break;
	}
	write(1, "\n", 1);
	free(buf);
	buf = NULL;
	return (PLAYER);
}
