/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:29:10 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/12 14:45:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 500
#endif
#include "cw_hexdump.h"

void			print_legend(t_data *data, int x, int y)
{
	static char pad[17] = "%-4c%-15s%-27s%c";

	mvwprintw(data->main_win, y - 1, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y, x, pad, '|', "Magic number", "---", '|');
	wattron(data->main_win, COLOR_PAIR(1));
	mvwprintw(data->main_win, y, x + 25, "%s", "RED");
	reset_colors(data);
	mvwprintw(data->main_win, y + 1, x, pad, '|', "Size", "---", '|');
	wattron(data->main_win, COLOR_PAIR(5));
	mvwprintw(data->main_win, y + 1, x + 25, "%s", "MAGENTA");
	reset_colors(data);
	mvwprintw(data->main_win, y + 2, x, pad, '|', ".Name", "---", '|');
	wattron(data->main_win, COLOR_PAIR(2));
	mvwprintw(data->main_win, y + 2, x + 25, "%s", "GREEN");
	reset_colors(data);
	mvwprintw(data->main_win, y + 3, x, pad, '|', ".Comment", "---", '|');
	wattron(data->main_win, COLOR_PAIR(3));
	mvwprintw(data->main_win, y + 3, x + 25, "%s", "YELLOW");
	reset_colors(data);
	mvwprintw(data->main_win, y + 4, x, pad, '|', "Instructions", "---", '|');
	wattron(data->main_win, COLOR_PAIR(6));
	mvwprintw(data->main_win, y + 4, x + 25, "%s", "BLUE");
	reset_colors(data);
	mvwprintw(data->main_win, y + 5, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 6, x, BOX);
}

void			print_menu(t_data *data)
{
	int x;
	int y;

	x = 80;
	y = 3;
	mvwprintw(data->main_win, y, x, BOX);
	mvwprintw(data->main_win, y + 1, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 2, x,
			"%-4c%-15s%-6s%-21s%c", '|', "Pause", "---", "p", '|');
	mvwprintw(data->main_win, y + 3, x,
			"%-4c%-15s%-6s%-21s%c", '|', "Start", "---", "s", '|');
	mvwprintw(data->main_win, y + 4, x,
			"%-4c%-15s%-6s%-21s%c", '|', "Faster", "---", "enter", '|');
	mvwprintw(data->main_win, y + 5, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 6, x, BOX_MIDDLE);
	print_legend(data, x, y + 8);
}

int				wait_or_enter(t_data *data, int sleeping)
{
	char	c;
	int		pause;

	wtimeout(data->main_win, 0);
	pause = 100;
	while (sleeping-- > 0)
	{
		if ((c = wgetch(data->main_win)) == '\n')
			return (1);
		if (c == 'p')
		{
			while (pause--)
			{
				if ((c = wgetch(data->main_win)) == 's')
					break ;
				usleep(50000);
			}
		}
		usleep(50000);
	}
	return (0);
}
