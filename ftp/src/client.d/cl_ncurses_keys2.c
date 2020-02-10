/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_keys2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:11:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 22:12:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_key_up(t_buff *ring, t_client *cl)
{
	(void)ring;
	wprintw(cl->ncu.chatwin, "UP\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

int			cl_key_down(t_buff *ring, t_client *cl)
{
	(void)ring;
	wprintw(cl->ncu.chatwin, "DOWN\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

int			cl_key_left(t_buff *ring, t_client *cl)
{
	(void)ring;
	wprintw(cl->ncu.chatwin, "LEFT\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

int			cl_key_right(t_buff *ring, t_client *cl)
{
	(void)ring;
	wprintw(cl->ncu.chatwin, "RIGHT\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}
