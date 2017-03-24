/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 12:19:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 13:00:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_cl_send_to(t_fd *to, t_fd *cl)
{
	if (cl->wr.tail < cl->wr.head)
	{
		send(to->fd, cl->wr.head, cl->wr.end - cl->wr.head, 0);
		send(to->fd, cl->wr.start, cl->wr.tail - cl->wr.start, 0);
	}
	else
		send(to->fd, cl->wr.head, cl->wr.tail - cl->wr.head + 1, 0);
}
