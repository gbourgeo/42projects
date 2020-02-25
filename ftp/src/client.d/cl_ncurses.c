/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:11:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:16:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_resize_window(int sig)
{
	t_client	*cl;
	int			errnb;

	cl = &g_cl;
	if (sig != SIGWINCH)
		return ;
	cl_ncurses_end(cl);
	refresh();
	clear();
	if ((errnb = cl_ncurses_init(cl)) == IS_OK)
		return ;
	cl_client_end(cl);
	ft_error(errnb, &cl->info);
	exit(EXIT_FAILURE);
}

static void		cl_init_pairs(void)
{
	init_color(CLIENT_DFLT_BCKGD, 100, 100, 100);
	init_color(CLIENT_COLOR_RED, 50, 0, 50);
	init_pair(CLIENT_DFLT_COLOR, COLOR_BLACK, CLIENT_DFLT_BCKGD);
	init_pair(CLIENT_TITLE_COLOR, COLOR_YELLOW, -1);
	init_pair(CLIENT_TEXT_COLOR, COLOR_WHITE, -1);
	init_pair(CL_RED, COLOR_RED, -1);
	init_pair(CL_GREEN, COLOR_GREEN, -1);
	init_pair(CL_BLUE, COLOR_BLUE, -1);
}

int				cl_ncurses_init(t_client *cl)
{
	int			errnb;

	if (FT_CHECK(cl->options, cl_verbose))
		ft_putstr("Initialising terminal... ");
	cl->sig[SIGWINCH] = signal(SIGWINCH, cl_resize_window);
	if ((cl->ncu.main = initscr()) == NULL)
		return (ERR_NCURSE_MAIN);
	raw();
	noecho();
	start_color();
	use_default_colors();
	clear();
	cl_init_pairs();
	if ((errnb = create_s_text(cl)) == IS_OK)
		if ((errnb = create_s_list(cl)) == IS_OK)
			if ((errnb = create_c_list(cl)) == IS_OK)
				errnb = create_c_text(cl);
	return (errnb);
}
