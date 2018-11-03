/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 02:31:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 08:07:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_ncu			ncu;

void			colors()
{
	start_color();
	use_default_colors();
	init_pair(1, -1, -1); // Default
	init_pair(2, COLOR_CYAN, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(4, COLOR_RED, -1);
	init_pair(5, COLOR_BLUE, -1);
	init_pair(6, COLOR_MAGENTA, -1);
	init_pair(7, COLOR_GREEN, -1);
	init_pair(8, COLOR_WHITE, COLOR_RED);
}

void			termTooSmall()
{
	wbkgd(ncu.mainWin, COLOR_PAIR(8));
	wattron(ncu.mainWin, A_BOLD);
	mvwaddstr(ncu.mainWin, (LINES * 0.5) - 1, (COLS * 0.5) - 3, "TERMINAL");
	mvwaddstr(ncu.mainWin, (LINES * 0.5), (COLS * 0.5) - 4, "TOO SMALL!");
	wattroff(ncu.mainWin, A_BOLD);
	wrefresh(ncu.mainWin);
	wbkgd(ncu.mainWin, COLOR_PAIR(1));
}

void			createChatBox()
{
	int			winx;
	int			winy;

	winx = COLS - 15;
	winy = LINES * 0.8;
	ncu.tchatWinBox = subwin(ncu.mainWin, winy, winx, 0, 0);
	box(ncu.tchatWinBox, 0, 0);
	mvwaddch(ncu.tchatWinBox, 0, (winx * 0.5) - 7, ACS_RTEE);
	wattron(ncu.tchatWinBox, COLOR_PAIR(3));
	mvwaddstr(ncu.tchatWinBox, 0, (winx * 0.5) - 6, " MiniTalk 2 ");
	wattroff(ncu.tchatWinBox, COLOR_PAIR(3));
	mvwaddch(ncu.tchatWinBox, 0, (winx * 0.5) + 6, ACS_LTEE);
	wrefresh(ncu.tchatWinBox);
	ncu.tchatWin = subwin(ncu.tchatWinBox, (winy - 2), winx - 2, 1, 1);
	scrollok(ncu.tchatWin, TRUE);
}

void			createUsersBox()
{
	int			winx;
	int			winy;

	winx = 15;
	winy = LINES * 0.8;
	ncu.usersWinBox = subwin(ncu.mainWin, winy, winx, 0, COLS - winx);
	box(ncu.usersWinBox, 0, 0);
	mvwaddch(ncu.usersWinBox, 0, 3, ACS_RTEE);
	wattron(ncu.usersWinBox, COLOR_PAIR(3));
	mvwaddstr(ncu.usersWinBox, 0, 4, " Users ");
	wattroff(ncu.usersWinBox, COLOR_PAIR(3));
	mvwaddch(ncu.usersWinBox, 0, 11, ACS_LTEE);
	wrefresh(ncu.usersWinBox);
	ncu.usersWin = subwin(ncu.usersWinBox, (winy - 2), winx - 2, 1, COLS - winx + 1);
	box(ncu.usersWin, 0, 0);
	wrefresh(ncu.usersWin);
	scrollok(ncu.usersWin, TRUE);
}

void			createTextBox()
{
	ncu.textWinBox = subwin(ncu.mainWin, (LINES * 0.2) - 1, COLS, (LINES * 0.8) + 1, 0);
	box(ncu.textWinBox, 0, 0);
	wrefresh(ncu.textWinBox);
	ncu.textWin = subwin(ncu.textWinBox, (LINES * 0.2) - 3, COLS - 2, (LINES * 0.8) + 2, 1);
	scrollok(ncu.textWin, TRUE);
}

void			createInfoLine()
{
	ncu.infoLine = subwin(ncu.mainWin, 1, COLS, (LINES - 1), 0);
}

void			ncurses_start()
{
	if ((ncu.mainWin = initscr()) == NULL)
		exit(1);
	noecho();
	cbreak();
	keypad(ncu.mainWin, TRUE);
	colors();
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

void			ncurses_end()
{
	/* wborder(ncu.tchat.win, ' ', ' ', ' ',' ',' ',' ',' ',' '); */
	/* wborder(ncu.text.win, ' ', ' ', ' ',' ',' ',' ',' ',' '); */
	/* wborder(ncu.users.win, ' ', ' ', ' ',' ',' ',' ',' ',' '); */

	/* wrefresh(ncu.tchat.win); */
	/* wrefresh(ncu.text.win); */
	/* wrefresh(ncu.users.win); */

	delwin(ncu.tchatWin);
	delwin(ncu.tchatWinBox);
	delwin(ncu.usersWin);
	delwin(ncu.usersWinBox);
	delwin(ncu.textWin);
	delwin(ncu.textWinBox);
	delwin(ncu.infoLine);
	endwin();
}
