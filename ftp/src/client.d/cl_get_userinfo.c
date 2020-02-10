/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_userinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:44:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 22:06:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static int	cl_get_return(char buff[], int ret, t_server *sv, t_client *cl)
{
	(void)buff;
	(void)ret;
	ft_strdel(&sv->user);
	ft_strdel(&sv->pass);
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (2);
}

static int	cl_get_next(char buff[], int ret, t_server *sv, t_client *cl)
{
	(void)ret;
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	if (!buff[0] || !ft_strcmp(buff, "y") || !ft_strcmp(buff, "Y"))
		return (cl_get_username(buff, sv, cl));
	if (!ft_strcmp(buff, "n") || !ft_strcmp(buff, "N"))
		return (2);
	wclear(cl->ncu.chatwin);
	buff[0] = 0;
	return (1);
}

static int	cl_get_dflt(char buff[], int ret, t_server *sv, t_client *cl)
{
	(void)sv;
	if (buff[0])
		mvwdelch(cl->ncu.chatwin, getcury(cl->ncu.chatwin),
		getcurx(cl->ncu.chatwin) - 1);
	buff[0] = 0;
	if (ft_isprint(ret))
	{
		wprintw(cl->ncu.chatwin, "%c", ret);
		buff[0] = ret;
	}
	wrefresh(cl->ncu.chatwin);
	return (0);
}

int			cl_get_userinfo(t_server *sv, t_client *cl)
{
	static	t_read	ch[] = {
		{ 3, cl_get_return }, { 4, cl_get_return }, { 10, cl_get_next },
		{ 0, cl_get_dflt },
	};
	int				i;
	char			buff[CMD_BUFF_SIZE];
	int				ret[2];

	ft_bzero(buff, sizeof(buff));
	ret[1] = 0;
	while (ret[1] == 0)
	{
		wmove(cl->ncu.chatwin, 0, 0);
		wprintw(cl->ncu.chatwin, "Do you want to sign to the server ? (y/n) ");
		wrefresh(cl->ncu.chatwin);
		while (ret[1] == 0 && (ret[0] = wgetch(cl->ncu.chatwin)) != ERR)
		{
			i = 0;
			while (i < 3 && ch[i].value != ret[0])
				i++;
			ret[1] = ch[i].hdlr(buff, ret[0], sv, cl);
		}
		ret[1]--;
	}
	return (IS_OK);
}
