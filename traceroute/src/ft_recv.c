/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:58:35 by root              #+#    #+#             */
/*   Updated: 2017/08/21 15:27:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <netinet/ip_icmp.h>

static t_probe		*ft_probe_by_fd(fd_set *fds)
{
	int				i;
	t_probe			*pb;

	i = 0;
	while (i < e.num_probes)
	{
		pb = (t_probe *)(e.probes + i * sizeof(t_probe));
		if (pb->fd > 0 && FD_ISSET(pb->fd, fds))
			return (pb);
		i++;
	}
	return (NULL);
}

void				ft_recv_icmp(fd_set *fds)
{
	int				rec;
	socklen_t		len;
	t_probe			*pb;

	if ((pb = ft_probe_by_fd(fds)) != NULL)
	{
		len = sizeof(pb->res);
		if (e.local)
			rec = recvfrom(e.sendsk, (char *)e.inpack, sizeof(e.inpack), 0,
							(struct sockaddr *)&pb->res, &len);
		else
			rec = recvfrom(pb->fd, (char *)e.inpack, sizeof(e.inpack), 0,
							(struct sockaddr *)&pb->res, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_parse(pb, rec);
		FD_CLR(pb->fd, fds);
		close(pb->fd);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}

void				ft_recv_udp(fd_set *fds)
{
	int				rec;
	socklen_t		len;
	t_probe			*pb;

	if ((pb = ft_probe_by_fd(fds)) != NULL)
	{
		len = sizeof(pb->res);
		ft_bzero(&e.inpack, sizeof(e.inpack));
		rec = recvfrom(pb->fd, (char *)e.inpack, sizeof(e.inpack), 0,
						(struct sockaddr *)&pb->res, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_parse(pb, rec);
		FD_CLR(pb->fd, fds);
		close(pb->fd);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}
