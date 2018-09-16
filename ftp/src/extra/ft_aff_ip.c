/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_ip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 04:50:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 20:49:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include "libft.h"

void					ft_aff_ip(struct addrinfo *p, int v6)
{
	struct sockaddr_in	*ipv4;
	struct sockaddr_in6	*ipv6;
	void				*addr;
	char				name[INET6_ADDRSTRLEN];

	if (v6)
	{
		ipv6 = (struct sockaddr_in6 *)p->ai_addr;
		addr = &(ipv6->sin6_addr);
		ft_putstr("\033[4mIPv6:\033[0m ");
	}
	else
	{
		ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &(ipv4->sin_addr);
		ft_putstr("\033[4mIPv4:\033[0m ");
	}
	inet_ntop(p->ai_family, addr, name, sizeof(name));
	ft_putstr(name);
}
