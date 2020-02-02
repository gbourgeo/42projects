/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:44:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 19:05:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "cl_main.h"

static int			cl_ctrl_d(t_client *cl)
{
	if (cl->rd.len == 0)
		return (ERR_DISCONNECT);
	return (IS_OK);
}

static int			cl_lf(t_client *cl)
{
	int		errnb;

	errnb = IS_OK;
	if (cl->rd.len > 0)
	{
		errnb = cl_client_commands(cl);
		cl->rd.len = 0;
		cl->pos = 0;
		werase(cl->ncu.textwin);
		wrefresh(cl->ncu.textwin);
	}
	return (errnb);
}

static int			cl_backspace(t_client *cl)
{
	if (cl->rd.len > 0)
	{
		mvwdelch(cl->ncu.textwin, getcury(cl->ncu.textwin), getcurx(cl->ncu.textwin) - 1);
		wrefresh(cl->ncu.textwin);
		if (--cl->rd.tail < cl->rd.buff)
			cl->rd.tail = cl->rd.buff + sizeof(cl->rd.buff) - 1;
		*cl->rd.tail = '\0';
		cl->rd.len--;
		cl->pos--;
	}
	return (IS_OK);
}

static int			cl_key_dc(t_client *cl)
{
	if (cl->rd.len > 0 && cl->pos != cl->rd.len)
	{
		wdelch(cl->ncu.textwin);
		wrefresh(cl->ncu.textwin);
		// if (--cl->rd.tail < cl->rd.buff)
		// 	cl->rd.tail = cl->rd.buff + sizeof(cl->rd.buff) - 1;
		// *cl->rd.tail = '\0';
		// cl->rd.len--;
	}
	return (IS_OK);
}

static int			cl_default(int ret, t_client *cl)
{
	if (ret >= 32 && ret <= 126)
	{
		if (cl->rd.len < sizeof(cl->rd.buff))
		{
			*cl->rd.tail++ = ret;
			wprintw(cl->ncu.textwin, "%c", ret);
			wrefresh(cl->ncu.textwin);
			cl->rd.len++;
			cl->pos++;
		}
		return (IS_OK);
	}
	wprintw(cl->ncu.textwin, "%d", ret);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}

static int			cl_key_up(t_client *cl)
{
	wprintw(cl->ncu.chatwin, "UP\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

static int			cl_key_down(t_client *cl)
{
	wprintw(cl->ncu.chatwin, "DOWN\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

static int			cl_key_left(t_client *cl)
{
	wprintw(cl->ncu.chatwin, "LEFT\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

static int			cl_key_right(t_client *cl)
{
	wprintw(cl->ncu.chatwin, "RIGHT\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}


int					cl_ncurses_read(t_client *cl)
{
	static t_read	ch[] = {
		{ 4, cl_ctrl_d }, { 10, cl_lf },
		{ KEY_BACKSPACE, cl_backspace }, { KEY_DC, cl_key_dc },
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
			return (ch[i].hdlr(cl));
		i++;
	}
	return (cl_default(ret, cl));
}
