/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls_and_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 12:05:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/30 20:49:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ls_pwd(char **cmds, t_envi *cl)
{
	(void)cmds;
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	while ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		cl->buff[cl->rec] = '\0';
		if (ft_strchr(cl->buff, '\2'))
			return (file_error(cl->buff, cl, CLIENT, 0));
		ft_putstr(cl->buff);
		if (ft_strchr(cl->buff, '\1'))
			return (0);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	return (0);
}
