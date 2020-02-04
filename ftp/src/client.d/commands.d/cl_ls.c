/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/04 19:26:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ls(char *buf, char **cmd, t_client *cl)
{
	int			errnb;

	(void)buf;
	(void)cmd;
	errnb = cl_server_write("PASV\n", 5, &cl->server, cl);
	cl->server.wait_response = 1;
	return (errnb);
}
