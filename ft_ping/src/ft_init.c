/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 01:35:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/11 00:09:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <limits.h>

static void			ft_err(char *msg, char *err_msg)
{
	fprintf(stderr, "%s: %s %s\n", e.prog, msg, err_msg);
	exit(2);
}

void				ft_init(void)
{
	struct hostent	*ht;
	socklen_t		on;

	ht = gethostbyname(e.hostname);
	on = 1;
	setuid(getuid());
	e.datalen = DEFDATALEN;
	e.tmin = LONG_MAX;
	e.interval = 1;
	if ((e.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		ft_err(e.prog, "socket");
	e.source.sin_family = AF_INET;
	if (inet_pton(AF_INET, e.hostname, &e.source.sin_addr) != 1)
	{
		if (!ht)
			ft_err("unknown host", e.hostname);
		e.source.sin_family = ht->h_addrtype;
		if (ht->h_length > (int) sizeof(e.source.sin_addr))
			ht->h_length = sizeof(e.source.sin_addr);
		ft_memcpy(&e.source.sin_addr, ht->h_addr, ht->h_length);
		inet_ntop(ht->h_addrtype, &e.source.sin_addr, e.srcname, sizeof(e.srcname) - 1);
	}
	else
		inet_ntop(AF_INET, &e.source.sin_addr, e.srcname, sizeof(e.srcname) - 1);
	e.source.sin_port = htons(PORT);
	setsockopt(e.sock, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
	on = 48 * 1024;
	setsockopt(e.sock, SOL_SOCKET, SO_RCVBUF, &on, sizeof(on));
	setsockopt(e.sock, SOL_SOCKET, SO_SNDBUF, &on, sizeof(on));
}
