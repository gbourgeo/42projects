/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:58:35 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:19:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>

static t_probe			*ft_probe_by_seq(int hlen, size_t len)
{
	struct icmp			*icmp;
	struct icmp6_hdr	*icmp6;
	int					type;
	int					i;
	u_int16_t			id;
	u_int16_t			seq;
	t_probe				*pb;

	if (len < sizeof(struct icmphdr))
		return (NULL);
	if (e.af == AF_INET)
	{
		icmp = (struct icmp *)(e.inpack + hlen);
		type = icmp->icmp_type;
		id = ntohs(icmp->icmp_id);
		seq = ntohs(icmp->icmp_seq);
	}
	else
	{
		icmp6 = (struct icmp6_hdr *)e.inpack;
		type = icmp6->icmp6_type;
		id = ntohs(icmp6->icmp6_id);
		seq = ntohs(icmp6->icmp6_seq);
	}
	if (id != e.ident || seq <= 0)
		return (NULL);
	i = 0;
	pb = NULL;
	while (i < e.num_probes && pb == NULL)
	{
		if (e.probes[i].seq == seq)
			pb = &e.probes[i];
		i++;
	}
	if (!pb)
		return (NULL);
	if (!(e.af == AF_INET && type == ICMP_ECHOREPLY) &&
		!(e.af == AF_INET6 && type == ICMP6_ECHO_REPLY))
		return (NULL);
	pb->final = 1;
	return (pb);
}

void				ft_recv_icmp(fd_set *fds)
{
	int				rec;
	int				hlen;
	socklen_t		len;
	t_probe			*pb;

	len = sizeof(e.from);
	pb = NULL;
	if (FD_ISSET(e.sendsk, fds))
	{
		rec = recvfrom(e.sendsk, (char *)e.inpack, sizeof(e.inpack), 0,
					   &e.from.sa, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		if (e.af == AF_INET)
		{
			if (rec < (int)sizeof(struct iphdr))
				return ;
			hlen = ((struct iphdr *)e.inpack)->ihl << 2;
			if (rec < hlen)
				return ;
			rec -= hlen;
		}
		pb = ft_probe_by_seq(hlen, rec);
		if (!pb)
			return ;
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_memcpy(&pb->res, &e.from, sizeof(pb->res));
		ft_parse_reply(pb, rec);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}

static t_probe		*ft_probe_by_fd(fd_set *fds)
{
	int				i;

	i = 0;
	while (i < e.num_probes)
	{
		if (e.probes[i].fd && FD_ISSET(e.probes[i].fd, fds))
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
	while ((pb = ft_probe_by_fd(fds)))
	{
		rec = recvfrom(pb->fd, (char *)e.inpack, sizeof(e.inpack), 0,
					   &e.from.sa, &len);
		if (rec < 0)
			ft_err("recvfrom", NULL);
		if (pb->seq != e.from.sin.sin_port)
			return ;
		if (!pb->recv_time)
			pb->recv_time = ft_get_time();
		ft_memcpy(&pb->res, &e.from, sizeof(pb->res));
		ft_parse_reply(pb, rec);
		close(pb->fd);
		pb->fd = 0;
		pb->seq = 0;
		pb->done = 1;
	}
}
