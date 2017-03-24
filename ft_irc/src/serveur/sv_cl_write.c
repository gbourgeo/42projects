/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:15:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 12:20:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void				sv_cl_write(char *str, t_fd *cl)
{
	if (!str || !cl)
		return ;
	while (*str)
	{
		*cl->wr.tail = *str;
		cl->wr.tail++;
		if (cl->wr.tail == cl->wr.end)
			cl->wr.tail = cl->wr.start;
		str++;
	}
}
