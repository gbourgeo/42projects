/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:08:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 16:32:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int		cl_server_write(const char buf[], t_server *sv, t_client *cl)
{
	int		i;
	int		errnb;

	i = 0;
	while (buf[i])
	{
		*sv->wr.tail++ = buf[i++];
		if (sv->wr.tail >= sv->wr.buff + sizeof(sv->wr.buff))
			sv->wr.tail = sv->wr.buff;
		if (sv->wr.len++ >= (int)sizeof(sv->wr.buff))
			if ((errnb = cl_server_send(&sv->wr, sv->fd_ctrl, cl)) != IS_OK)
				return (errnb);
	}
	return (IS_OK);
}
