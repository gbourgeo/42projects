/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 02:31:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 12:25:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void			ncurses()
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
		ncu.tchatWinBox = subwin(ncu.mainWin, (LINES * 0.8), COLS, 0, 0);
		box(ncu.tchatWinBox, 0, 0);
		mvwaddch(ncu.tchatWinBox, 0, (COLS * 0.5) - 6, ACS_RTEE);
		wattron(ncu.tchatWinBox, COLOR_PAIR(3));
		mvwaddstr(ncu.tchatWinBox, 0, (COLS * 0.5) - 5, " MiniTalk " );
		wattroff(ncu.tchatWinBox, COLOR_PAIR(3));
		mvwaddch(ncu.tchatWinBox, 0, (COLS * 0.5) + 5, ACS_LTEE);
		wrefresh(ncu.tchatWinBox);
		ncu.tchatWin = subwin(ncu.tchatWinBox, (LINES * 0.8 - 2), COLS - 2, 1, 1);
		scrollok(ncu.tchatWin, TRUE);

		ncu.textWinBox = subwin(ncu.mainWin, (LINES * 0.2) - 1, COLS, (LINES * 0.8) + 1, 0);
		box(ncu.textWinBox, 0, 0);
		wrefresh(ncu.textWinBox);
		ncu.textWin = subwin(ncu.textWinBox, (LINES * 0.2) - 3, COLS - 2, (LINES * 0.8) + 2, 1);

		ncu.infoLine = subwin(ncu.mainWin, 1, COLS, (LINES - 1), 0);
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
	delwin(ncu.textWin);
	delwin(ncu.textWinBox);
	delwin(ncu.infoLine);
	endwin();
}
