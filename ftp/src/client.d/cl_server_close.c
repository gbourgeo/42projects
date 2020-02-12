/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/11 17:30:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_server_close(t_server *sv, int end, t_client *cl)
{
	cl->printtowin = cl->ncu.chatwin;
	ft_strdel(&sv->user);
	ft_strdel(&sv->pass);
	if (end)
		ft_close(&sv->fd_ctrl);
	ft_close(&sv->fd_data);
	sv->receive_data = 0;
	sv->wait_response = 0;
	ft_strdel(&sv->filename);
	ft_close(&sv->filefd);
	ft_bzero(sv->response, sizeof(sv->response));
	ft_bzero(sv->cmd, sizeof(sv->cmd));
	return (IS_OK);
}
