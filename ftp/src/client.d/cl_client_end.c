/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 20:09:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/30 18:40:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <unistd.h>
#include "cl_main.h"

void			cl_ncurses_end(t_client *cl)
{
	if (cl->ncu.chatbox)
		delwin(cl->ncu.chatbox);
	if (cl->ncu.chatwin)
		delwin(cl->ncu.chatwin);
	if (cl->ncu.listbox)
		delwin(cl->ncu.listbox);
	if (cl->ncu.listwin)
		delwin(cl->ncu.listwin);
	if (cl->ncu.textbox)
		delwin(cl->ncu.textbox);
	if (cl->ncu.textwin)
		delwin(cl->ncu.textwin);
	endwin();
	ft_memset(&cl->ncu, 0, sizeof(cl->ncu));
}

static void		cl_term_end(t_client *cl)
{
	if (cl->term.fd <= 0)
		return ;
	tputs(cl_tgetstr("ei"), 1, cl_pchar);
	tcsetattr(cl->term.fd, TCSANOW, &cl->term.info);
	close(cl->term.fd);
}

void			cl_client_end(t_client *cl)
{
	int		i;

	i = 0;
	ft_freestr(&cl->info.env.path);
	ft_freestr(&cl->info.env.home);
	while (i < NSIG)
	{
		if (cl->sig[i] != SIG_ERR)
			signal(i, cl->sig[i]);
		i++;
	}
	ft_close(&cl->server.fd_ctrl);
	ft_close(&cl->server.fd_data);
	ft_close(&cl->server.fd_file);
	ft_strdel(&cl->server.pwd);
	ft_strdel(&cl->pwd);
	if (FT_CHECK(cl->options, cl_ncurses))
		cl_ncurses_end(cl);
	else
		cl_term_end(cl);
}
