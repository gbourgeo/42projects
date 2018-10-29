/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:06:21 by root              #+#    #+#             */
/*   Updated: 2018/10/29 12:27:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	wprintTime(WINDOW *win, time_t ts)
{
	struct tm *timestamp;

	timestamp = localtime(&ts);

	wattron(win, COLOR_PAIR(1));
	wprintw(win, "[%02d", timestamp->tm_hour);
	wattroff(win, COLOR_PAIR(1));
	wattron(win, COLOR_PAIR(3));
	wprintw(win, ":");
	wattroff(win, COLOR_PAIR(3));
	wattron(win, COLOR_PAIR(1));
	wprintw(win, "%02d", timestamp->tm_min);
	wattroff(win, COLOR_PAIR(1));
	wattron(win, COLOR_PAIR(3));
	wprintw(win, ":");
	wattroff(win, COLOR_PAIR(3));
	wattron(win, COLOR_PAIR(1));
	wprintw(win, "%02d] ", timestamp->tm_sec);
	wattroff(win, COLOR_PAIR(1));
}
