/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_userpass.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 23:26:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/12 17:42:10 by gbourgeo         ###   ########.fr       */
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
	sv->pass = ft_strdup(buff);
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (1);
}

static int	cl_get_erase(char buff[], int ret, t_server *sv, t_client *cl)
{
	int		len;

	(void)ret;
	(void)sv;
	(void)cl;
	len = ft_strlen(buff);
	if (len > 0)
		buff[len - 1] = '\0';
	return (0);
}

static int	cl_get_dflt(char buff[], int ret, t_server *sv, t_client *cl)
{
	int		len;

	(void)sv;
	(void)cl;
	len = ft_strlen(buff);
	if (len < CMD_BUFF_SIZE - 1 && ft_isprint(ret))
		buff[len] = ret;
	return (0);
}

int			cl_get_userpass(t_server *sv, t_client *cl)
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
	wmove(cl->ncu.chatwin, 2, 0);
	wprintw(cl->ncu.chatwin, "Enter your PASS word : ");
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
