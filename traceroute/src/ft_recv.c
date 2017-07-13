/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:58:35 by root              #+#    #+#             */
/*   Updated: 2017/04/17 21:14:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>

static t_probe		*ft_probe_by_fd(fd_set *fds)
{
	int				i;

	i = 0;
	while (i < e.num_probes)
	{
		if (e.probes[i].fd > 0 && FD_ISSET(e.probes[i].fd, fds))
			return (&e.probes[i]);
		i++;
	}
	return (NULL);
}

void				ft_recv_udp(fd_set *fds)
{
	int				rec;
	socklen_t		len;
	t_probe			*pb;

	len = sizeof(e.from);
	pb = NULL;
	if ((pb = ft_probe_by_fd(fds)))
	{
		ft_bzero(&e.inpack, sizeof(e.inpack));
		rec = recvfrom(pb->fd, (char *)e.inpack, sizeof(e.inpack), 0,
						(struct sockaddr *)&e.from, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		/* printf("\nrecv:%d %d %d", rec, pb->seq, ((struct ip *)(e.inpack))->ip_ttl); */
		/* if (pb->seq != e.from.sin_port) */
		/* 	return ; */
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_memcpy(&pb->res, &e.from, sizeof(pb->res));
		ft_parse(pb, rec);
		FD_CLR(pb->fd, fds);
		close(pb->fd);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}

void				ft_recv_icmp(fd_set *fds)
{
	int				rec;
	socklen_t		len;
	t_probe			*pb;

	len = sizeof(e.from);
	pb = NULL;
	if ((pb = ft_probe_by_fd(fds)))
	{
		rec = recvfrom(pb->fd, (char *)e.inpack, sizeof(e.inpack), 0,
						(struct sockaddr *)&e.from, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		/* printf("\nrecv:%d %d %d", rec, pb->seq, e.from.sin_port); */
		/* if (pb->seq != e.from.sin_port) */
		/* 	return ; */
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_memcpy(&pb->res, &e.from, sizeof(pb->res));
		ft_parse(pb, rec);
		FD_CLR(pb->fd, fds);
		close(pb->fd);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}
