/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 14:16:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 02:56:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

static void				ft_init_hdr(t_hdr *hdr)
{
	ft_memset(&e.inpack, 0, sizeof(e.inpack));
	ft_memset(&hdr->from, 0, sizeof(hdr->from));
	ft_memset(&e.ctrl, 0, sizeof(e.ctrl));
	ft_memset(&hdr->msg, 0, sizeof(hdr->msg));
	hdr->msg.msg_name = &hdr->from;
	hdr->msg.msg_namelen = sizeof(hdr->from);
	hdr->msg.msg_control = (caddr_t)e.ctrl;
	hdr->msg.msg_controllen = sizeof(e.ctrl);
	hdr->msg.msg_iov = &hdr->iov;
	hdr->msg.msg_iovlen = 1;
	hdr->iov.iov_base = e.inpack;
	hdr->iov.iov_len = IP_MAXPACKET;
	hdr->cmsg = (struct cmsghdr *)e.ctrl;
}

void					ft_setup(void)
{
	t_hdr				hdr;
	int					i;

	gettimeofday(&e.start, NULL);
	ft_alarm(0);
	while (1)
	{
		ft_init_hdr(&hdr);
		if ((i = recvmsg(e.sock, &hdr.msg, 0)) < 0)
		{
			if (errno == EINTR)
				continue ;
			fprintf(stderr, "%s: recvmsg: ", e.prog);
			perror("");
			continue ;
		}
		if (hdr.cmsg->cmsg_level == SOL_SOCKET &&
			hdr.cmsg->cmsg_type == SCM_TIMESTAMP &&
			hdr.cmsg->cmsg_len == CMSG_LEN(sizeof(struct timeval)))
			ft_memcpy(&e.end_time, CMSG_DATA(hdr.cmsg), sizeof(struct timeval));
		else
			gettimeofday(&e.end_time, NULL);
		ft_analyse((char *)e.inpack, i, &hdr.from);
		if (e.options & OPT_COUNT && e.nreceived == e.count)
			break ;
	}
	ft_finish(0);
}
