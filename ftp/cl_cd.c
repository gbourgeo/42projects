/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 00:50:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/06 04:57:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_cd(char **cmds, t_envi *cl)
{
	char			*tmp;

	(void)cmds;
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	if ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		if (ft_strchr(cl->buff, '\2'))
			return (file_error(cl->buff, cl, CLIENT, 0));
		free(cl->pwd);
		tmp = ft_strchr(cl->buff, '\1');
		cl->pwd = (tmp == NULL) ? ft_strndup(cl->buff, cl->rec) :
			ft_strndup(cl->buff, cl->rec - ft_strlen(tmp));
		if (!tmp && (cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
			write(1, cl->buff, cl->rec);
		else if (tmp)
			write(1, tmp, ft_strlen(tmp));
		return (0);
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	else if (cl->rec == -1)
		return (file_error("\033[31mERROR: recv() fail.", cl, CLIENT, 0));
	return (file_error(cl->buff, cl, CLIENT, 0));
}
