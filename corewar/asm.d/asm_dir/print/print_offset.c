/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:18:50 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 21:53:46 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include <time.h>

void	print_offset(t_data *data)
{
	int offset;
	int loop;
	int x;
	int mod;

	offset = data->pos;
	loop = 7;
	x = 7;
	while (loop--)
	{
		mod = offset % 16;
		if (offset == 0)
			mvwprintw(data->main_win, data->y, x, "0");
		else
		{
			if (mod > 9)
				mvwprintw(data->main_win, data->y, x, "%c", (mod - 10) + 97);
			if (mod <= 9)
				mvwprintw(data->main_win, data->y, x, "%c", mod + 48);
		}
		wrefresh(data->main_win);
		x--;
		offset /= 16;
	}
	data->x = data->x + 8;
}

void	print_fsize(t_data *data)
{
	ft_printf("Compilation done   %C \t\t-rwx------   %s   %d\t%k\n", L'✓',
			data->file_name, data->pc + 1, time(NULL) - 12600);
}
