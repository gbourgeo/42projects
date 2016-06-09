/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_mkdir_rmdir_unlink.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:34:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/06 04:58:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_mkdir(char **cmds, t_envi *cl)
{
	int		ret;

	ret = 0;
	if (!cmds || !cmds[1])
		return (file_error("ERROR: Wrong number of arguments", cl, CLIENT, 0));
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	while ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		cl->buff[cl->rec] = '\0';
		if (ft_strchr(cl->buff, '\2'))
			ret = file_error(cl->buff, cl, CLIENT, 0);
		else
			break ;
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	write(1, cl->buff, cl->rec);
	return (ret);
}

int			cl_rmdir(char **cmds, t_envi *cl)
{
	if (!cmds || !cmds[1])
		return (file_error("ERROR: Wrong number of arguments", cl, CLIENT, 0));
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	if ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		cl->buff[cl->rec] = '\0';
		if (ft_strchr(cl->buff, '\2'))
			return (file_error(cl->buff, cl, CLIENT, 0));
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	write(1, cl->buff, cl->rec);
	return (0);
}

int			cl_unlink(char **cmds, t_envi *cl)
{
	if (!cmds || !cmds[1])
		return (file_error("ERROR: Wrong number of arguments", cl, CLIENT, 0));
	send(cl->fd, cl->buff, ft_strlen(cl->buff), 0);
	if ((cl->rec = recv(cl->fd, cl->buff, BUFF_SIZE, 0)) > 0)
	{
		cl->buff[cl->rec] = '\0';
		if (ft_strchr(cl->buff, '\2'))
			return (file_error(cl->buff, cl, CLIENT, 0));
	}
	if (cl->rec == 0)
		cl_end("Server: disconnected.", cl);
	if (cl->rec == -1)
		cl_end("\033[31mERROR: recv() fail.", cl);
	write(1, cl->buff, cl->rec);
	return (0);
}
