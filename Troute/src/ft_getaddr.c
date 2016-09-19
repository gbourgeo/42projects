/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 23:39:21 by root              #+#    #+#             */
/*   Updated: 2016/09/17 23:39:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void				ft_getaddr(void)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*tmp;
	int				ret;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = e.af;
	hints.ai_flags = 0x0040; //AI_IDN
	if ((ret = getaddrinfo(e.src, NULL, &hints, &res)))
		ft_err(e.src, (char *)gai_strerror(ret));
	tmp = res;
	while (tmp)
	{
		if (tmp->ai_family == e.af)
			break ;
		if (e.af == AF_UNSPEC && tmp->ai_family == AF_INET)
			break ;
		tmp = tmp->ai_next;
	}
	if (tmp == NULL)
		tmp = res;
	ft_memcpy(&e.source, tmp->ai_addr, tmp->ai_addrlen);
	getnameinfo(&e.source.sa, sizeof(e.source),
				e.srcip, sizeof(e.srcip), 0, 0, NI_NUMERICHOST);
	freeaddrinfo(res);
}
