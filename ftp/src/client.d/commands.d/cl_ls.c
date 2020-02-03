/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 16:05:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ls(char *buf, char **cmd, t_client *cl)
{
	int			errnb;

	(void)buf;
	(void)cmd;
	errnb = cl_server_write("PASV\n", 5, &cl->server);
	return (errnb);
}
