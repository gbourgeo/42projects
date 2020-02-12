/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_userinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:44:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/12 17:41:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "cl_struct.h"

static int	cl_get_next(int ret, t_server *sv, t_client *cl)
{
	if (ret != 10)
		wprintw(cl->ncu.chatwin, "%c", ret);
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	if (ret == 10 || ret == 'y' || ret == 'Y')
		return (cl_get_username(sv, cl));
	return (IS_OK);
}

int			cl_get_userinfo(t_server *sv, t_client *cl)
{
	int				ret;

	wmove(cl->ncu.chatwin, 0, 0);
	wprintw(cl->ncu.chatwin, "Do you want to sign to the server ? (y/n) ");
	wrefresh(cl->ncu.chatwin);
	while ((ret = wgetch(cl->ncu.chatwin)) != ERR)
		if (ft_isprint(ret) || ret == 10)
			break ;
		else if (ret == 3 || ret == 4)
			return (ERR_QUIT);
	if (ret != ERR)
		ret = cl_get_next(ret, sv, cl);
	return ((ret == ERR) ? ERR_READ : IS_OK);
}
