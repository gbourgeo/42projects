/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:59:19 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:55:55 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			reset_colors(t_data *data)
{
	wattroff(data->main_win, COLOR_PAIR(0));
	wattroff(data->main_win, COLOR_PAIR(1));
	wattroff(data->main_win, COLOR_PAIR(2));
	wattroff(data->main_win, COLOR_PAIR(3));
	wattroff(data->main_win, COLOR_PAIR(4));
	wrefresh(data->main_win);
}

/*
** magic n	: pos < 4				1 - RED
** .name	: 4 <= pos < 132		2 - GREEN
** padding	: 132 <= pos < 136		0 - WHITE
** size		: 136 <= pos <= 140		5 - MAGENTA
** .comment	: 140 < pos < 2188		3 - YELLOW
** padding	: 2188 <= pos < 2192	0 - WHITE
** instruc	: pos >= 2192			6 - CYAN
*/

void			starting_color(t_data *data)
{
	reset_colors(data);
	if (data->x < 9 && (data->e->flag & FLAG_O))
		wattron(data->main_win, COLOR_PAIR(0));
	else if (data->pos >= 0 && data->pos < 4)
		wattron(data->main_win, COLOR_PAIR(1));
	else if (data->pos >= 4 && data->pos < 132)
		wattron(data->main_win, COLOR_PAIR(2));
	else if (data->pos >= 132 && data->pos < 136)
		wattron(data->main_win, COLOR_PAIR(0));
	else if (data->pos >= 136 && data->pos < 140)
		wattron(data->main_win, COLOR_PAIR(5));
	else if (data->pos >= 140 && data->pos < 2188)
		wattron(data->main_win, COLOR_PAIR(3));
	else if (data->pos >= 2188 && data->pos < 2192)
		wattron(data->main_win, COLOR_PAIR(0));
	else if (data->pos >= 2192)
		wattron(data->main_win, COLOR_PAIR(6));
	else
		wattron(data->main_win, COLOR_PAIR(0));
}
