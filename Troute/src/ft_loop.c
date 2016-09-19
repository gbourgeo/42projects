/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 16:32:47 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:26:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

double				ft_get_time(void)
{
	struct timeval	tv;
	double			ret;

	gettimeofday(&tv, NULL);
	ret = ((double)tv.tv_usec / 1000000. + (unsigned long)tv.tv_sec);
	return (ret);
}

static void			ft_print_addr(t_addr_any *res)
{
	char			numeric[INET6_ADDRSTRLEN];
	char			name[INET6_ADDRSTRLEN];

	if (!res->sa.sa_family)
		return ;
	*numeric = 0;
	getnameinfo(&res->sa, sizeof(*res), numeric, sizeof(numeric),
				0, 0, NI_NUMERICHOST);
	*name = 0;
	getnameinfo(&res->sa, sizeof(*res), name, sizeof(name),
				0, 0, 0);
	printf(" %s (%s)", *name ? name : numeric, numeric);
}

static int			ft_check_addr(t_addr_any *a, t_addr_any *b)
{
	if (!a->sa.sa_family)
		return (0);
	if (a->sa.sa_family != b->sa.sa_family)
		return (0);
	if (a->sa.sa_family == AF_INET)
		return (!ft_memcmp(&a->sin.sin_addr, &b->sin.sin_addr,
							sizeof(a->sin.sin_addr)));
	else
		return (!ft_memcmp(&a->sin6.sin6_addr, &b->sin6.sin6_addr,
							sizeof(a->sin6.sin6_addr)));
	return (0);
}

static void			ft_print_probe(t_probe *pb)
{
	int				idx;
	int				ttl;
	int				np;
	int				prn;
	t_probe			*p;

	idx = pb - e.probes;
	ttl = idx / e.nprobes + 1;
	np = idx % e.nprobes;
	if (np == 0)
		printf("\n%2d ", ttl);
	if (!pb->res.sa.sa_family)
		printf(" *");
	else
	{
		prn = !np;
		if (np)
		{
			p = pb - 1;
			while (np && !p->res.sa.sa_family)
			{
				p--;
				np--;
			}
			if (!np || !ft_check_addr(&p->res, &pb->res))
				prn = 1;
		}
		if (prn)
			ft_print_addr(&pb->res);
	}
	if (pb->recv_time)
		printf("  %.3f ms", (pb->recv_time - pb->send_time) * 1000);
	if (*pb->err_str)
		printf(" %s", pb->err_str);
}

static void			ft_init_select(int *maxfd, fd_set *fds)
{
	int				i;
	
	FD_ZERO(fds);
	*maxfd = 0;
	i = 0;
	while (i < e.num_probes)
	{
		if (e.probes[i].fd > 0 && !FD_ISSET(e.probes[i].fd, fds))
		{
			FD_SET(e.probes[i].fd, fds);
			if (e.probes[i].fd > *maxfd)
				*maxfd = e.probes[i].fd;
		}
		i++;
	}
}

static void			ft_do_select(double timeout)
{
	static void		(*ft_recv[])(fd_set *) = { ft_recv_udp,
											   ft_recv_udp,
											   ft_recv_icmp };
	fd_set			fds;
	int				maxfd;
	int				ret;
	struct timeval	wait;

	ft_init_select(&maxfd, &fds);
	wait.tv_sec = (int)timeout;
	wait.tv_usec = (timeout - (int)timeout) * 1000000.0;
	ft_bzero(&e.inpack, sizeof(e.inpack));
	while (maxfd)
	{
		ret = select(maxfd + 1, &fds, (fd_set *)0, (fd_set *)0, &wait);
		if (ret <= 0)
		{
			if (ret == 0 || ret == EINTR)
				return ;
			ft_err("select", NULL);
		}
		ft_recv[e.module](&fds);
		ft_init_select(&maxfd, &fds);
	}
}

void				ft_loop(void)
{
	static void		(*ft_send[])(t_probe *, int) = { ft_send_udp, ft_send_udp, ft_send_icmp };
	int				start;
	int				end;
	double			now_time;
	double			next_time;
	double			last_send;
	double			timeout;
	int				ttl;
	int				n;
	int				sim;
	t_probe			*pb;

	start = (e.first_hop - 1) * e.nprobes;
	end = e.num_probes;
	last_send = 0;

	printf("%s to %s (%s), %d hops max, %d byte packets",
		   e.prog, e.src, e.srcip, e.max_hops, e.headerlen + e.datalen);
	fflush(stdout);
//	exit(0);
	while (start < end)
	{
		n = start - 1;
		sim = 0;
		next_time = 0;
		now_time = ft_get_time();
		while (++n < end)
		{
			pb = &e.probes[n];
			if (!pb->done &&
				pb->send_time &&
				now_time - pb->send_time >= e.wait)
			{
				if (pb->fd && pb->fd != e.sendsk)
					close(pb->fd);
				pb->fd = 0;
				pb->seq = 0;
				pb->done = 1;
//				ft_check_expired(pb);
			}

			if (pb->done)
			{
				if (n == start)
				{
					ft_print_probe(pb);
					start++;
				}
				if (pb->final)
					end = (n / e.nprobes + 1) * e.nprobes;
				continue ;
			}

			if (!pb->send_time)
			{
				if (e.send_secs && (now_time - last_send) < e.send_secs)
				{
					next_time = (last_send + e.send_secs) - e.wait;
					break ;
				}
				ttl = n / e.nprobes + 1;
				ft_send[e.module](pb, ttl);
				if (!pb->send_time)
				{
					if (next_time)
						break ;
					else
						ft_err("send probe", NULL);
				}
				last_send = pb->send_time;
			}

			if (pb->send_time > next_time)
				next_time = pb->send_time;

			sim++;
			if (sim >= e.sim_probes)
				break ;
		}
		if (next_time)
		{
			timeout = (next_time + e.wait) - now_time;
			if (timeout < 0)
				timeout = 0;
			ft_do_select(timeout);
		}
		if (e.done)
			return ;
	}
}
