/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:15:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:40:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void				sv_write(char *str, t_buf *buf)
{
	if (!str || !buf)
		return ;
	while (*str)
	{
		*buf->tail = *str;
		buf->tail++;
		if (buf->tail == buf->end)
			buf->tail = buf->start;
		str++;
	}
}
