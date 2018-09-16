/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 20:49:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 23:14:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <unistd.h>

int				main(void)
{
	t_board		board;
	t_piece		piece;
	int			start;

	start = 1;
	if (get_info(&board) == -1)
		return (-1);
	while (start)
	{
		if (get_board(&board) == -1)
			return (-1);
		if (get_piece(&piece) == -1)
			return (-1);
		init_my_pos(&piece);
		start = ft_start_program(&board, &piece);
	}
	ft_putendl("0 0");
	return (0);
}

void			init_my_pos(t_piece *piece)
{
	piece->s_x = 0;
	piece->s_y = 0;
}
