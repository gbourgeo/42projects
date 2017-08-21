/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 23:39:21 by root              #+#    #+#             */
/*   Updated: 2017/08/20 14:21:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <netdb.h>

void				ft_getaddr(void)
{
	int				ret;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*tmp;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = e.af;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;
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
	e.af = tmp->ai_family;
	ft_memcpy(&e.dest, tmp->ai_addr, tmp->ai_addrlen);
	getnameinfo((struct sockaddr *)&e.dest, sizeof(e.dest),
			e.srcip, sizeof(e.srcip), 0, 0, NI_NUMERICHOST);
	ft_memcpy(&e.res, tmp, sizeof(e.res));
	freeaddrinfo(res);
}
