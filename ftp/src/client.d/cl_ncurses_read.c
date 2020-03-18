/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:44:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 11:07:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "cl_main.h"
#include "cl_struct.h"

#ifdef __linux__
# define FTP_BACKSPACE KEY_BACKSPACE
#elif
# define FTP_BACKSPACE 127
#endif

static int			cl_default(int ret, t_buff *ring, t_client *cl)
{
	if (ft_isprint(ret))
	{
		if (ring->len < (int)sizeof(ring->buff) - 1)
		{
			cl_ncurses_copy(ring->tail);
			*ring->tail++ = ret;
			ring->len++;
			wprintw(cl->ncu.textwin, "%s", ring->tail - 1);
			wmove(cl->ncu.textwin, getcury(cl->ncu.textwin),
				ring->tail - ring->buff);
			wrefresh(cl->ncu.textwin);
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
