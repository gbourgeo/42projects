/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:30:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 09:06:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int			init_addrinfo(char *ip, char *port, struct addrinfo **res)
{
	struct addrinfo	hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	return (getaddrinfo(ip, port, &hints, res));
}

int 				opensocket(char *ip, char *port, type1 func, type2 func2)
{
	int				status;
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				fd;

	printf("Connection to %s:%s ... ", ip, port);
	fflush(stdout);
	if ((status = init_addrinfo(ip, port, &results))) {
		printf("\e[31mFailed\e[0m\n");
		printf("%s\n", gai_strerror(status));
		return (0);
	}
	tmp = results;
	while (tmp != NULL)
	{
		fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (fd == -1)
			continue ;
		if (func(fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(fd);
		fd = -1;
		tmp = tmp->ai_next;
	}
	freeaddrinfo(results);
	if (tmp == NULL) {
		printf("\e[31mFailed\e[0m\n");
		printf("No server found.\n");
		return (0);
	}
	if (func2)
		func2(fd, MAX_CLIENTS);
	printf("\e[32mOK\e[0m\n");
	return (fd);
}
