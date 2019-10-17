/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 00:42:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_send(t_client *cl)
{
	int			ret;

	ret = IS_OK;
	if (cl->wr.len)
	{
		if (cl->wr.tail > cl->wr.head)
			ret = send(cl->fd, cl->wr.head, cl->wr.len, 0);
		else
		{
			ret = send(cl->fd, cl->wr.head,
			cl->wr.buff + BUFF_SIZE - cl->wr.head, 0);
			ret = send(cl->fd, cl->wr.buff, cl->wr.tail - cl->wr.tail, 0);
		}
		cl->wr.head = cl->wr.tail;
		cl->wr.len = 0;
		if (ret <= 0)
			return ((ret == 0) ? ERR_DISCONNECT : ERR_SEND);
	}
	return (IS_OK);
}
