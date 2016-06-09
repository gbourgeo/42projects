/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls_and_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 12:05:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 19:34:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ls_pwd(char **cmds, t_envi *cl)
{
	char		*tmp;

	(void)cmds;
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	while ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		cl->buff[cl->rec] = '\0';
		ft_putstr(cl->buff);
		if ((tmp = ft_strchr(cl->buff, '\1')))
			break ;
		if (ft_strchr(cl->buff, '\2'))
			return (1);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	if (*(tmp + 1) == 0)
		ft_putendl("\033[32mSUCCESS\033[0m");
	return (*(tmp + 1));
}
