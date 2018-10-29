/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:30:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 06:47:34 by gbourgeo         ###   ########.fr       */
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
	if (getaddrinfo(ip, port, &hints, res))
		return (1);
	return (0);
}

int 				opensocket(char *ip, char *port, type1 func, type2 func2)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				fd;

	printf("\e[33mConnecting to \e[0m%s\e[33m on port \e[0m%s\e[33m...\e[0m ", ip, port);
	fflush(stdout);
	if (init_addrinfo(ip, port, &results)) {
		printf("\e[31mFailed\n\e[0m");
		return 0;
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
		printf("\e[31mCan't establish connection.\n\e[0m");
		return 0;
	}
	if (func2)
		func2(fd, MAX_CLIENTS);
	printf("\e[32mOK\e[0m\n");
	return (fd);
}

