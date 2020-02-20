/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_keys2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:11:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 17:59:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_key_up(t_buff *ring, t_client *cl)
{
	if (!cl->hist || !cl->hist->next)
		return (IS_OK);
	ft_strdel(&cl->hist->line);
	cl->hist->line = ft_strdup(ring->buff);
	cl->hist = cl->hist->next;
	ft_strncpy(ring->buff, cl->hist->line, sizeof(ring->buff) - 1);
	ring->len = ft_strlen(ring->buff);
	ring->tail = ring->buff + ring->len;
	wclear(cl->ncu.textwin);
	wprintw(cl->ncu.textwin, "%s", ring->buff);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}

int			cl_key_down(t_buff *ring, t_client *cl)
{
	if (!cl->hist || !cl->hist->prev)
		return (IS_OK);
	ft_strdel(&cl->hist->line);
	cl->hist->line = ft_strdup(ring->buff);
	cl->hist = cl->hist->prev;
	ft_strncpy(ring->buff, cl->hist->line, sizeof(ring->buff) - 1);
	ring->len = ft_strlen(ring->buff);
	ring->tail = ring->buff + ring->len;
	wclear(cl->ncu.textwin);
	wprintw(cl->ncu.textwin, "%s", ring->buff);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}

int			cl_key_left(t_buff *ring, t_client *cl)
{
	(void)cl;
	if (ring->tail > ring->buff)
	{
		ring->tail--;
		wmove(cl->ncu.textwin, getcury(cl->ncu.textwin),
		getcurx(cl->ncu.textwin) - 1);
	}
	return (IS_OK);
}

int			cl_key_right(t_buff *ring, t_client *cl)
{
	(void)cl;
	if (*ring->tail && ring->tail < ring->buff + sizeof(ring->buff) - 1)
	{
		ring->tail++;
		wmove(cl->ncu.textwin, getcury(cl->ncu.textwin),
		getcurx(cl->ncu.textwin) + 1);
	}
	return (IS_OK);
}
