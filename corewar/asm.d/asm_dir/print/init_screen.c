/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:28:15 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 01:21:38 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		print_continue(t_data *data)
{
	wattron(data->main_win, A_BLINK);
	mvwprintw(data->main_win, 12, 55, "Press enter to continue...", 123);
	wattroff(data->main_win, A_BLINK);
	wrefresh(data->main_win);
}

static void		*thread_quit(void *thread)
{
	t_thread	*arg;
	char		c;

	arg = (t_thread *)thread;
	while (1)
	{
		c = wgetch(arg->main_win);
		if (c == '\n')
		{
			arg->stop = 0;
			pthread_exit(NULL);
			break ;
		}
	}
	return (NULL);
}

static int		print_first(t_data *data)
{
	pthread_t	thread;
	t_thread	arg;
	int			i;

	i = 0;
	ft_memset(&arg, 0, sizeof(t_thread));
	arg.main_win = data->main_win;
	arg.stop = 1;
	pthread_create(&thread, NULL, thread_quit, &arg);
	while (arg.stop)
	{
		if (i < 73)
		{
			mvwprintw(data->main_win, data->y, data->x, "%c", MSG[i]);
			wrefresh(data->main_win);
			data->x++;
			wait_or_enter(data, 1);
			i++;
		}
		else
			print_continue(data);
	}
	wclear(data->main_win);
	wrefresh(data->main_win);
	return (0);
}

int				init_screen(t_data *data)
{
	initscr();
	clear();
	refresh();
	cbreak();
	noecho();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	data->main_win = newwin(0, 0, 0, 0);
	keypad(data->main_win, TRUE);
	data->y = 10;
	data->x = 5;
	wattron(data->main_win, COLOR_PAIR(0));
	wrefresh(data->main_win);
	print_first(data);
	return (0);
}
