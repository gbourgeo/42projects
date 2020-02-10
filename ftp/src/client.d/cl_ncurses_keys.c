/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:09:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 22:10:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_ctrl_c(t_buff *ring, t_client *cl)
{
	(void)cl;
	ring->head = ring->buff;
	ring->tail = ring->buff;
	ring->len = 0;
	wclear(cl->ncu.textwin);
	wrefresh(cl->ncu.textwin);
	return (IS_OK);
}

int			cl_ctrl_d(t_buff *ring, t_client *cl)
{
	(void)cl;
	if (ring->len == 0)
		return (ERR_QUIT);
	return (IS_OK);
}

int			cl_lf(t_buff *ring, t_client *cl)
{
	int		errnb;

	errnb = IS_OK;
	if (ring->len > 0)
	{
		*ring->tail++ = '\0';
		errnb = cl_client_commands(ring, cl);
		ring->head = ring->buff;
		ring->tail = ring->buff;
		ring->len = 0;
		werase(cl->ncu.textwin);
		wrefresh(cl->ncu.textwin);
	}
	return (errnb);
}

int			cl_backspace(t_buff *ring, t_client *cl)
{
	if (ring->tail > ring->buff && ring->len > 0)
	{
		ring->tail--;
		ft_strcpy(ring->tail, ring->tail + 1);
		ring->len--;
		mvwdelch(cl->ncu.textwin, getcury(cl->ncu.textwin),
		getcurx(cl->ncu.textwin) - 1);
		wrefresh(cl->ncu.textwin);
	}
	return (IS_OK);
}

int			cl_key_dc(t_buff *ring, t_client *cl)
{
	if (*ring->tail)
	{
		ft_strcpy(ring->tail, ring->tail + 1);
		ring->len--;
		wdelch(cl->ncu.textwin);
		wrefresh(cl->ncu.textwin);
	}
	return (IS_OK);
}
