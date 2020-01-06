/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:11:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/07 00:11:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_resize_window(int sig)
{
	t_client	*cl;
	int			errnb;

	cl = &client;
	if (sig != SIGWINCH)
		return ;
	cl_ncurses_end(cl);
	refresh();
	clear();
	if ((errnb = cl_init_ncurses(cl)) == IS_OK)
		return ;
	cl_client_end(cl);
	ft_error(errnb, &cl->info);
	exit(EXIT_FAILURE);
}

static void		cl_init_pairs(void)
{
	init_color(CLIENT_DFLT_BCKGD, 100, 100, 100);
	init_pair(CLIENT_DFLT_COLOR, COLOR_BLACK, CLIENT_DFLT_BCKGD);
	init_pair(CLIENT_TITLE_COLOR, COLOR_YELLOW, -1);
	init_pair(CLIENT_TEXT_COLOR, COLOR_WHITE, -1);
}

int				cl_init_ncurses(t_client *cl)
{
	int			errnb;

	cl->sig[SIGWINCH] = signal(SIGWINCH, cl_resize_window);
	if ((cl->ncu.main = initscr()) == NULL)
		return (ERR_NCURSE_MAIN);
	noecho();
	cbreak();
	keypad(cl->ncu.main, TRUE);
	// curs_set(0);
	start_color();
	use_default_colors();
	cl_init_pairs();
	if ((errnb = create_s_text(cl)) == IS_OK)
		if ((errnb = create_s_list(cl)) == IS_OK)
			errnb = create_c_text(cl);
	return (errnb);
}
