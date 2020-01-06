/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:24:17 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 22:25:02 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		print_file_name(t_data *data)
{
	wattron(data->main_win, COLOR_PAIR(2));
	mvwprintw(data->main_win, 1, 2, "%s", data->file_name);
	wattroff(data->main_win, COLOR_PAIR(2));
	wrefresh(data->main_win);
	mvwprintw(data->main_win, 1, ft_strlen(data->file_name) + 3, "created");
	wrefresh(data->main_win);
}

void		print_compilation(t_data *data)
{
	wclear(data->main_win);
	wrefresh(data->main_win);
	mvwprintw(data->main_win, 1, 2, "Starting compiling into   >>");
	wrefresh(data->main_win);
	wattron(data->main_win, COLOR_PAIR(4) | A_BLINK);
	mvwprintw(data->main_win, 1, 35, "%s", data->file_name);
	wattroff(data->main_win, COLOR_PAIR(4) | A_BLINK);
	wrefresh(data->main_win);
}

void		print_dot(t_data *data)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(data->file_name);
	while (i++ < 3)
	{
		mvwprintw(data->main_win, 1, len + 10 + i, ".\t");
		wrefresh(data->main_win);
		if (wait_or_enter(data, 10))
			break ;
	}
}
