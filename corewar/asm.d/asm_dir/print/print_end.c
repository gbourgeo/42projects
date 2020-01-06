/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:17:43 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 21:53:19 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void	print_end(t_data *dat)
{
	char	c;
	char	*str;

	dat->y = dat->y + 2;
	dat->x = 4;
	if (!(str = (char *)malloc(sizeof(char) * 6)))
		return ;
	mvwprintw(dat->main_win, dat->y, dat->x, "-- Press [esc] to quit");
	mvwprintw(dat->main_win, dat->y + 1, dat->x, "-- Press [ r ] to reprint");
	while (1)
	{
		c = wgetch(dat->main_win);
		if (c == 27)
			break ;
		if (c == 114)
		{
			wclear(dat->main_win);
			print_compilation(dat);
			print_menu(dat);
			print_hex(dat);
			print_end(dat);
		}
	}
}
