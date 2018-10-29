/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:51:31 by root              #+#    #+#             */
/*   Updated: 2018/10/29 12:00:50 by root             ###   ########.fr       */
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
		ncu.tchatWinBox = subwin(ncu.mainWin, (LINES * 0.8), COLS, 0, 0);
		box(ncu.tchatWinBox, 0, 0);
		mvwaddch(ncu.tchatWinBox, 0, (COLS * 0.5) - 6, ACS_RTEE);
		mvwaddstr(ncu.tchatWinBox, 0, (COLS * 0.5) - 5, " MiniTalk " );
		mvwaddch(ncu.tchatWinBox, 0, (COLS * 0.5) + 6, ACS_LTEE);
		wrefresh(ncu.tchatWinBox);
		ncu.tchatWin = subwin(ncu.tchatWinBox, (LINES * 0.8 - 2), COLS - 2, 1, 1);
		scrollok(ncu.tchatWin, TRUE);

		ncu.textWinBox = subwin(ncu.mainWin, (LINES * 0.2) - 1, COLS, (LINES * 0.8) + 1, 0);
		box(ncu.textWinBox, 0, 0);
		ncu.textWin = subwin(ncu.textWinBox, (LINES * 0.2) - 3, COLS - 2, (LINES * 0.8) + 2, 1);

		ncu.infoLine = subwin(ncu.mainWin, 1, COLS, (LINES - 1), 0);
	}
}
