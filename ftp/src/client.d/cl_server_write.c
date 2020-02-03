/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:08:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 17:31:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_server_write(const char *buf, int len, t_server *sv)
{
	int		i;
	int		errnb;

	i = 0;
	while (i < len)
	{
		*sv->wr.tail++ = buf[i++];
		if (sv->wr.tail >= sv->wr.buff + sizeof(sv->wr.buff))
			sv->wr.tail = sv->wr.buff;
		if (sv->wr.len++ >= (int)sizeof(sv->wr.buff))
			if ((errnb = cl_server_send(sv->fd_ctrl, &sv->wr)) != IS_OK)
				return (errnb);
	}
	return (IS_OK);
}
