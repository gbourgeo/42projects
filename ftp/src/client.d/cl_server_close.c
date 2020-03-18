/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 17:11:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

void				cl_server_close(t_server *sv, t_client *cl)
{
	ft_strdel(&sv->user);
	ft_strdel(&sv->pass);
	ft_close(&sv->fd_ctrl);
	cl_server_close_data(sv);
	cl->precmd = cl_precmd_end(cl->precmd, 1, cl);
}

void				cl_server_close_data(t_server *sv)
{
	ft_close(&sv->fd_data);
	sv->receive_data = -1;
	sv->wait_response = 0;
	ft_strdel(&sv->filename);
	ft_close(&sv->filefd);
	sv->ret = 0;
	ft_bzero(sv->cmd, sizeof(sv->cmd));
//	ft_bzero(sv->response, sizeof(sv->response));
}
