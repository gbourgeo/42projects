/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 17:51:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_client_send(t_client *cl)
{
	int			ret;

	if (cl->wr.len <= 0)
		return (IS_OK);
	if (cl->wr.tail > cl->wr.head)
	{
		ret = send(cl->fd, cl->wr.head, cl->wr.len,
					MSG_DONTWAIT | MSG_NOSIGNAL);
		if (ret <= 0)
			return (sv_send_error(ret));
		if ((cl->wr.head += ret) >= cl->wr.buff + CMD_BUFF_SIZE)
			cl->wr.head = cl->wr.buff;
		cl->wr.len -= ret;
		return (IS_OK);
	}
	ret = send(cl->fd, cl->wr.head,
	cl->wr.buff + CMD_BUFF_SIZE - cl->wr.head, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (sv_send_error(ret));
	if ((cl->wr.head += ret) >= cl->wr.buff + CMD_BUFF_SIZE)
		cl->wr.head = cl->wr.buff;
	cl->wr.len -= ret;
	return (sv_client_send(cl));
}
