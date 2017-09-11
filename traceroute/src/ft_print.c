/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 17:12:41 by root              #+#    #+#             */
/*   Updated: 2017/04/17 21:20:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

static void			ft_print_addr(t_probe *pb)
{
	char			numeric[NI_MAXHOST];
	char			name[NI_MAXHOST];

	if (!pb->res.sin_family)
		return ;
	numeric[0] = 0;
	getnameinfo((struct sockaddr *)&pb->res, sizeof(pb->res),
			numeric, sizeof(numeric), 0, 0, NI_NUMERICHOST);
	name[0] = '\0';
	getnameinfo((struct sockaddr *)&pb->res, sizeof(pb->res),
			name, sizeof(name), 0, 0, 32); //32 = NI_IDN <netdb.h>
	printf(" %s (%s)", *name ? name : numeric, numeric);
}

static int			ft_check_addr(struct sockaddr_in *a, struct sockaddr_in *b)
{
	if (!a->sin_family)
		return (0);
	if (a->sin_family != b->sin_family)
		return (0);
	return (!ft_memcmp(&a->sin_addr, &b->sin_addr, sizeof(a->sin_addr)));
}

void				ft_print_probe(t_probe *pb)
{
	int				idx;
	int				ttl;
	int				np;
	int				prn;
	t_probe			*p;

	idx = pb - (t_probe *)e.probes;
	ttl = idx / e.nprobes + 1;
	np = idx % e.nprobes;
	if (np == 0)
		printf("\n%2d ", ttl);
	if (!pb->res.sin_family)
		printf(" *");
	else
	{
		prn = !np;
		if (np)
		{
			p = pb - 1;
			while (np && !p->res.sin_family)
			{
				p--;
				np--;
			}
			if (!np || !ft_check_addr(&p->res, &pb->res))
				prn = 1;
		}
		if (prn)
			ft_print_addr(pb);
	}
	if (pb->recv_time)
		printf("  %.3f ms", (pb->recv_time - pb->send_time) * 1000);
	if (*pb->err_str)
		printf(" %s", pb->err_str);
	fflush(stdout);
}
