/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/09 04:29:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_close_data(t_server *sv, int end, t_client *cl)
{
	cl->printtowin = cl->ncu.chatwin;
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
