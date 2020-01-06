/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:42:45 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:55:37 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			print_buff(t_data *data)
{
	int i;

	i = 0;
	while (data->buffer[i] || i < 16)
	{
		starting_color(data);
		data->pos = data->pos + 1;
		if (i % 8 == 0)
		{
			mvwprintw(data->main_win, data->y, data->x + 1, "  ");
			wrefresh(data->main_win);
			data->x = data->x + 2;
		}
		if (!data->buffer[i] || len_hex(data->buffer[i]) == 1)
			print_zero(data);
		nprint_nb(data, 16, data->buffer[i], 97);
		mvwprintw(data->main_win, data->y, data->x + 1, " ");
		wrefresh(data->main_win);
		data->x = data->x + 1;
		i++;
		wait_or_enter(data, 10);
	}
	ft_bzero(data->buffer, 17);
}

int				fill_buffer(t_data *data)
{
	if (data->i == 16)
	{
		data->i = 0;
		if (data->zero < 16)
		{
			data->zero = 0;
			if (data->e->flag & FLAG_O)
				print_offset(data);
			print_buff(data);
			return (1);
		}
		if (data->check == 0)
			print_zero_line(data);
		else
			data->pos = data->pos + 16;
		data->zero = 0;
		return (0);
	}
	return (0);
}
