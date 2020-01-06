/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:46:53 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:57:06 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int				len_hex(unsigned char bin)
{
	int len;

	len = 0;
	while (bin > 0)
	{
		len++;
		bin /= 16;
	}
	return (len);
}

void			nprint_nb(t_data *data, int base, unsigned char n, char letter)
{
	char	c;

	if (n <= base - 1)
	{
		if (n <= 9)
		{
			mvwprintw(data->main_win, data->y, data->x + 1, "%c", n + 48);
			wrefresh(data->main_win);
			data->x = data->x + 1;
		}
		else
		{
			c = (n - 10) + letter;
			mvwprintw(data->main_win, data->y, data->x + 1, "%c", c);
			wrefresh(data->main_win);
			data->x = data->x + 1;
		}
	}
	if (n > base - 1)
	{
		nprint_nb(data, base, n / base, letter);
		nprint_nb(data, base, n % base, letter);
	}
}

static void		init_struct(t_data *data)
{
	lseek(data->fd, 0, SEEK_SET);
	data->y = 3;
	data->x = 1;
	data->pos = 0;
	data->zero = 0;
	data->i = 0;
	if (!(data->buffer = ft_memalloc(sizeof(unsigned char) * 17)))
		return ;
}

static void		init_newline(t_data *data, unsigned char buff)
{
	data->zero = 0;
	data->y = data->y + 1;
	data->x = 1;
	data->buffer[data->i] = buff;
	data->i = data->i + 1;
	check_zero(data, buff);
}

void			print_hex(t_data *data)
{
	unsigned char	buff;

	init_struct(data);
	while (read(data->fd, &buff, 1) > 0)
	{
		starting_color(data);
		if (fill_buffer(data) == 1)
			init_newline(data, buff);
		else
		{
			data->buffer[data->i] = buff;
			data->i = data->i + 1;
			check_zero(data, buff);
		}
	}
	if (data->e->flag & FLAG_O)
		print_offset(data);
	print_buff(data);
	free(data->buffer);
	reset_colors(data);
	wait_or_enter(data, 10000);
}
