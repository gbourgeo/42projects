/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:59:31 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/12 14:43:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			check_zero(t_data *data, unsigned char buff)
{
	if (buff == 0x0)
		data->zero = data->zero + 1;
	if (buff != 0x0)
	{
		data->check = 0;
		data->zero = 0;
	}
}

void			print_zero(t_data *data)
{
	mvwprintw(data->main_win, data->y, data->x + 1, "0");
	wrefresh(data->main_win);
	data->x = data->x + 1;
}

static void		zero_loop(t_data *data)
{
	int i;

	i = 0;
	while (ZERO_LINE[i])
	{
		if (ZERO_LINE[i] == ' ')
			data->pos = data->pos + 1;
		mvwprintw(data->main_win, data->y, data->x + 1, "%c", ZERO_LINE[i++]);
		wrefresh(data->main_win);
		data->x = data->x + 1;
		wait_or_enter(data, 1);
	}
}

void			print_zero_line(t_data *data)
{
	data->x = 3;
	if (data->e->flag & FLAG_O)
		print_offset(data);
	starting_color(data);
	zero_loop(data);
	data->pos = data->pos - 1;
	data->x = 1;
	data->y = data->y + 1;
	if (data->e->flag & FLAG_O)
		mvwprintw(data->main_win, data->y, 1, "*");
	else
		mvwprintw(data->main_win, data->y, data->x + 2, "*");
	wrefresh(data->main_win);
	data->check = 1;
	data->y = data->y + 1;
}
