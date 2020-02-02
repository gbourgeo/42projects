/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_box.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:28:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 16:50:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			create_s_text(t_client *cl)
{
	int		x;
	int		y;

	if (LINES < 5)
		return (IS_OK);
	x = COLS * 2 / 3;
	y = LINES * 1 / 10;
	if ((y = LINES - ((y < 3) ? 3 : y)) < 3)
		y = 3;
	if (!(cl->ncu.chatbox = subwin(cl->ncu.main, y, x, 0, 0)))
		return (ERR_NCURSE_TEXTBOX);
	box(cl->ncu.chatbox, 0, 0);
	mvwaddch(cl->ncu.chatbox, 0, (x * 0.5) - 8, ACS_RTEE);
	wattron(cl->ncu.chatbox, COLOR_PAIR(CLIENT_TITLE_COLOR));
	mvwaddstr(cl->ncu.chatbox, 0, (x * 0.5) - 7, " S E R V E R ");
	wattroff(cl->ncu.chatbox, COLOR_PAIR(CLIENT_TITLE_COLOR));
	mvwaddch(cl->ncu.chatbox, 0, (x * 0.5) + 6, ACS_LTEE);
	wrefresh(cl->ncu.chatbox);
	cl->ncu.chatwin = subwin(cl->ncu.chatbox, y - 2, x - 2, 1, 1);
	if (!cl->ncu.chatwin)
		return (ERR_NCURSE_TEXTWIN);
	scrollok(cl->ncu.chatwin, TRUE);
	return (IS_OK);
}

int			create_s_list(t_client *cl)
{
	int		x;
	int		y;

	if (LINES < 5)
		return (IS_OK);
	x = COLS * 1 / 3;
	x += (COLS % x) ? 1 : 0;
	y = LINES * 1 / 10;
	if ((y = LINES - ((y < 3) ? 3 : y)) < 3)
		y = 3;
	if (!(cl->ncu.listbox = subwin(cl->ncu.main, y, x, 0, COLS - x)))
		return (ERR_NCURSE_LISTBOX);
	box(cl->ncu.listbox, 0, 0);
	mvwaddch(cl->ncu.listbox, 0, (x * 0.5) - 5, ACS_RTEE);
	wattron(cl->ncu.listbox, COLOR_PAIR(CLIENT_TITLE_COLOR));
	mvwaddstr(cl->ncu.listbox, 0, (x * 0.5) - 4, " L I S T ");
	wattroff(cl->ncu.listbox, COLOR_PAIR(CLIENT_TITLE_COLOR));
	mvwaddch(cl->ncu.listbox, 0, (x * 0.5) + 5, ACS_LTEE);
	wrefresh(cl->ncu.listbox);
	cl->ncu.listwin = subwin(cl->ncu.listbox, y - 2, x - 2, 1, COLS - x + 1);
	if (!cl->ncu.listwin)
		return (ERR_NCURSE_LISTWIN);
	return (IS_OK);
}

int			create_c_text(t_client *cl)
{
	int		x;
	int		y;

	x = COLS;
	if ((y = LINES * 1 / 10) < 3)
		y = 3;
	if (!(cl->ncu.textbox = subwin(cl->ncu.main, y, x, LINES - y, 0)))
		return (ERR_NCURSE_CHATBOX);
	box(cl->ncu.textbox, 0, 0);
	wrefresh(cl->ncu.textbox);
	cl->ncu.textwin = subwin(cl->ncu.textbox, y - 2, x - 2, LINES - y + 1, 1);
	if (!cl->ncu.textwin)
		return (ERR_NCURSE_CHATWIN);
	keypad(cl->ncu.textwin, TRUE);
	wmove(cl->ncu.textwin, 0, 0);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}
