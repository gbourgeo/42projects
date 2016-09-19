/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sockets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 00:44:53 by root              #+#    #+#             */
/*   Updated: 2016/09/19 01:56:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				ft_tune_socket(int fd)
{
	int				i;
	t_addr_any		addr;

	ft_memset(&addr, 0, sizeof(addr));
	addr.sa.sa_family = e.af;
	if (bind(fd, &addr.sa, sizeof(addr)) < 0)
		ft_err("error", NULL);
	if (e.af == AF_INET)
	{
		i = IP_PMTUDISC_DONT;
		if (setsockopt(fd, SOL_IP, IP_MTU_DISCOVER, &i, sizeof(i)) < 0)
			ft_err("setsockopt IP_MTU_DISCOVER", NULL);
		i = 1;
		setsockopt(fd, SOL_SOCKET, SO_TIMESTAMP, &i, sizeof(i));
		setsockopt(fd, SOL_IP, IP_RECVTTL, &i, sizeof(i));
	}
	else
	{
		i = IPV6_PMTUDISC_DONT;
		if (setsockopt(fd, SOL_IPV6, IPV6_MTU_DISCOVER, &i, sizeof(i)) < 0)
			ft_err("setsockopt IPV6_MTU_DISCOVER", NULL);
		i = 1;
		setsockopt(fd, SOL_SOCKET, SO_TIMESTAMP, &i, sizeof(i));
		setsockopt(fd, SOL_IPV6, IPV6_RECVHOPLIMIT, &i, sizeof(i));
	}
}

void				ft_set_ttl(int fd, int ttl)
{
	if (e.af == AF_INET &&
		setsockopt(fd, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_err("setsockopt IP_TTL", NULL);
	if (e.af == AF_INET6 &&
		setsockopt(fd, SOL_IPV6, IPV6_UNICAST_HOPS, &ttl, sizeof(ttl)) < 0)
		ft_err("setsockopt IPV6_UNICAST_HOPS", NULL);
}

void				ft_recverr(int fd)
{
	int				i;

	i = 1;
	if (e.af == AF_INET &&
		setsockopt(fd, SOL_IP, IP_RECVERR, &i, sizeof(i)) < 0)
		ft_err("setsockopt IP_RECVERR", NULL);
	if (e.af == AF_INET6 &&
		setsockopt(fd, SOL_IPV6, IPV6_RECVERR, &i, sizeof(i)) < 0)
		ft_err("setsockopt IPV6_RECVERR", NULL);
}
