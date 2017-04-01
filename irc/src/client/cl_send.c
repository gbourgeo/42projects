/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 04:45:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 04:45:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

void			cl_send(int fd, char *cmd, char *param, char **next)
{
	send(fd, cmd, ft_strlen(cmd), 0);
	send(fd, param, ft_strlen(param), 0);
	while (next && *next)
	{
		send(fd, " ", 1, 0);
		send(fd, *next, ft_strlen(*next), 0);
		next++;
	}
	send(fd, END_CHECK, END_CHECK_LEN, 0);
}
