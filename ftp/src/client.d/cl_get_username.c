/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_username.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:08:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/12 17:42:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "cl_struct.h"

static int	cl_get_quit(char buff[], int ret, t_server *sv, t_client *cl)
{
	(void)buff;
	(void)ret;
	ft_strdel(&sv->user);
	ft_strdel(&sv->pass);
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (1);
}

static int	cl_get_next(char buff[], int ret, t_server *sv, t_client *cl)
{
	(void)ret;
	sv->user = ft_strdup(buff);
	return (cl_get_userpass(sv, cl));
}

static int	cl_get_erase(char buff[], int ret, t_server *sv, t_client *cl)
{
	int		len;

	(void)ret;
	(void)sv;
	len = ft_strlen(buff);
	if (len > 0)
	{
		buff[len - 1] = '\0';
		mvwdelch(cl->ncu.chatwin, getcury(cl->ncu.chatwin),
		getcurx(cl->ncu.chatwin) - 1);
		wrefresh(cl->ncu.chatwin);
	}
	return (0);
}

static int	cl_get_dflt(char buff[], int ret, t_server *sv, t_client *cl)
{
	int		len;

	(void)sv;
	len = ft_strlen(buff);
	if (len < CMD_BUFF_SIZE - 1 && ft_isprint(ret))
	{
		buff[len] = ret;
		wprintw(cl->ncu.chatwin, "%c", ret);
		wrefresh(cl->ncu.chatwin);
	}
	return (0);
}

int			cl_get_username(t_server *sv, t_client *cl)
{
	static	t_read	ch[] = {
		{ 3, cl_get_quit }, { 4, cl_get_quit }, { 10, cl_get_next },
		{ 127, cl_get_erase }, { 0, cl_get_dflt },
	};
	char			buff[CMD_BUFF_SIZE];
	int				i;
	int				ret;

	ft_bzero(buff, sizeof(buff));
	ret = 0;
	wmove(cl->ncu.chatwin, 1, 0);
	wprintw(cl->ncu.chatwin, "Enter your USER name : ");
	wrefresh(cl->ncu.chatwin);
	while (ret == 0 && (ret = wgetch(cl->ncu.chatwin)) != ERR)
	{
		i = 0;
		while (i < 4 && ch[i].value != ret)
			i++;
		ret = ch[i].hdlr(buff, ret, sv, cl);
	}
	return ((ret == ERR) ? ERR : 1);
}
