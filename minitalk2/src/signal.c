/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:51:31 by root              #+#    #+#             */
/*   Updated: 2018/10/30 06:37:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void		quitprogram(int signum)
{
	if (signum != SIGINT)
		return ;
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients[i].fd == -1)
			continue ;
		close(clients[i].fd);
	}
	clear_clients(clients, MAX_CLIENTS);
	ncurses_end();
	exit(0);
}

void		changewindow(int signum)
{
	if (signum != SIGWINCH)
		return ;
	endwin();
	refresh();
	clear();
	if (LINES < 24 || COLS < 76)
		termTooSmall();
	else
	{
		createChatBox();
		createUsersBox();
		createTextBox();
		createInfoLine();
	}
}
