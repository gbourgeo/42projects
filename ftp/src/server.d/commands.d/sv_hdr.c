/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_hdr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 01:28:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 17:41:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "sv_main.h"

int				sv_receive_hdr(int fd, t_hdr *hdr)
{
	char	*ptr;
	int		ret;
	int		received;
	time_t	timeout;
	int		errnb;

	ptr = (char *)hdr;
	received = 0;
	timeout = time(NULL);
	errnb = IS_OK;
	while (received < (int)sizeof(hdr) && errnb == IS_OK)
	{
		ret = recv(fd, ptr + received,
			sizeof(hdr) - received, MSG_DONTWAIT | MSG_NOSIGNAL);
		if (ret <= 0)
		{
			if ((errnb = sv_recv_error(ret)) == IS_OK)
				errnb = (time(NULL) - timeout >= TRANSFERT_TIMEOUT)
					? ERR_TIMEOUT : IS_OK;
			continue ;
		}
		timeout = time(NULL);
		received += ret;
	}
	return (errnb);
}
