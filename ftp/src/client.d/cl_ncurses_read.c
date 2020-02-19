/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:44:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/18 23:13:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "cl_main.h"
#include "cl_struct.h"

#define FTP_BACKSPACE 127
#ifdef __linux__
# define FTP_BACKSPACE KEY_BACKSPACE
#endif

static int			cl_default(int ret, t_buff *ring, t_client *cl)
{
	if (ret >= 32 && ret <= 126)
	{
		if (ring->len < (int)sizeof(ring->buff) - 1)
		{
			*ring->tail++ = ret;
			wprintw(cl->ncu.textwin, "%c", ret);
			wrefresh(cl->ncu.textwin);
			ring->len++;
		}
		return (IS_OK);
	}
	wprintw(cl->ncu.textwin, "%d", ret);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}

int					cl_ncurses_read(t_buff *ring, t_client *cl)
{
	static t_read	ch[] = {
		{ 3, cl_ctrl_c }, { 4, cl_ctrl_d }, { 10, cl_lf },
		{ FTP_BACKSPACE, cl_backspace }, { KEY_DC, cl_key_dc },
		{ KEY_UP, cl_key_up }, { KEY_DOWN, cl_key_down },
		{ KEY_LEFT, cl_key_left }, { KEY_RIGHT, cl_key_right },
	};
	unsigned long	i;
	int				ret;

	ret = wgetch(cl->ncu.textwin);
	if (ret == ERR)
		return (ERR_READ);
	i = 0;
	while (i < sizeof(ch) / sizeof(ch[0]))
	{
		if (ret == ch[i].value)
			return (ch[i].hdlr(ring, cl));
		i++;
	}
	return (cl_default(ret, ring, cl));
}
