/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 01:17:15 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 02:28:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static bool		set_timeout(SOCKET sock)
{
	struct timeval		timeout;
	t_flag				*timeout_flag = get_flag("timeout");

	timeout.tv_usec = 0;
	timeout.tv_sec = 0;
	if (timeout_flag && timeout_flag->value) {
		int value = ft_atoi(timeout_flag->value);
		if (value <= 10) {
			timeout.tv_sec = value;
		} else {
			timeout.tv_usec = (value * 100);
		}
	} else {
		timeout.tv_usec = DEFAULT_TIMEOUT;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
		return (false);
	}
	return (true);
}

SOCKET			init_socket(u_char protocol)
{
	SOCKET			sock = 0;
	bool			opt = true;

	if ((sock = socket(AF_INET, SOCK_RAW, protocol)) < 0) // Raw socket descriptor
	{
		printf("socket() failed : Operation not permitted\n");
		return (SOCKET_ERROR);
	}
	if ((setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt))) < 0) // set flag so socket expects us to provide IPv4 header.
	{
		printf("setsockopt() failed to set IP_HDRINCL\n");
		close(sock);
		return (SOCKET_ERROR);
	}
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&opt, sizeof(opt)) < 0) // allow socket to send datagrams to broadcast addresses
	{
		printf("setsockopt() failed to set SO_BROADCAST\n");
		close(sock);
		return (SOCKET_ERROR);
	}
	if ((set_timeout(sock)) != true) {
		close(sock);
		return (SOCKET_ERROR);
	}
	return (sock);
}

bool			send_socket_raw(t_thread_handler *handler, int raw_len, int port)
{
	struct sockaddr_in		sin;
	struct ip				*ip_header = (struct ip*)((void*)handler->buffer_raw);

	pthread_mutex_lock(&globals->queue_lock);
	ft_memset (&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ip_header->ip_dst.s_addr;
	sin.sin_port = htons(port);

	return (sendto(handler->fd, handler->buffer_raw, raw_len, 0,
		(struct sockaddr *)&sin, sizeof(struct sockaddr)));
}
