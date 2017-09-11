/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 16:32:47 by root              #+#    #+#             */
/*   Updated: 2017/08/21 15:24:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

double				ft_get_time(void)
{
	struct timeval	tv;
	double			ret;

	gettimeofday(&tv, NULL);
	ret = ((double)tv.tv_usec / 1000000. + (unsigned long)tv.tv_sec);
	return (ret);
}

static int			ft_init_select(fd_set *fds)
{
	int				i;
	int				maxfd;
	t_probe			*pb;
	
	maxfd = 0;
	i = 0;
	while (i < e.num_probes)
	{
		pb = (t_probe *)(e.probes + i * sizeof(t_probe));
		if (pb->fd > 0)
		{
			if (!FD_ISSET(pb->fd, fds))
			{
				FD_SET(pb->fd, fds);
				if (pb->fd > maxfd)
				maxfd = pb->fd;
			}
			else if (pb->fd > maxfd)
				maxfd = pb->fd;
		}
		i++;
	}
	return maxfd;
}

static void			ft_do_select(double timeout)
{
	static void		(*ft_recv[])(fd_set *) = { RECV_MODULE };
	fd_set			fds;
	int				maxfd;
	int				ret;
	struct timeval	wait;

	FD_ZERO(&fds);
	maxfd = ft_init_select(&fds);
	wait.tv_sec = (int)timeout;
	wait.tv_usec = (timeout - (int)timeout) * 1000000.0;
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
		maxfd = ft_init_select(&fds);
		wait.tv_sec = 0;
		wait.tv_usec = 0;
	}
}

void				ft_loop(void)
{
	static void		(*ft_send[])(t_probe *, int) = { SEND_MODULE };
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
	
	while (start < end)
	{
		n = start - 1;
		sim = 0;
		next_time = 0;
		now_time = ft_get_time();
		while (++n < end)
		{
			pb = (t_probe *)(e.probes + n * sizeof(t_probe));
			if (!pb->done && pb->send_time &&
				now_time - pb->send_time >= e.wait_secs)
			{
				if (pb->fd > 0)
					close(pb->fd);
				pb->fd = 0;
				pb->seq = 0;
				pb->done = 1;
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
					next_time = (last_send + e.send_secs) - e.wait_secs;
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
		fflush(stdout);
		if (next_time)
		{
			timeout = (next_time + e.wait_secs) - now_time;
			if (timeout < 0)
				timeout = 0.0;
			ft_do_select(timeout);
		}
	}
}
