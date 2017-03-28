/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:43:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:56:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_cl_write(t_env *e, t_fd *cl)
{
	char		ptr[BUFF + 1];

	(void)e;
	if (cl->wr.head != cl->wr.tail)
	{
		if (cl->wr.tail < cl->wr.head)
		{
			ft_strncpy(ptr, cl->wr.head, cl->wr.end - cl->wr.head);
			ft_strncat(ptr, cl->wr.start, cl->wr.tail - cl->wr.start);
			send(cl->fd, ptr, ft_strlen(ptr), 0);
		}
		else
			send(cl->fd, cl->wr.head, cl->wr.tail - cl->wr.head, 0);
		cl->wr.head = cl->wr.tail;
	}
}
