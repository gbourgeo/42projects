/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 02:31:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 06:55:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int		usage(const char *prog)
{
	printf("Server:\n");
	printf("\t%s -l [port]\n", prog);
	printf("Client:\n");
	printf("\t%s [target ip] [port]\n", prog);
	return (1);
}

static void		quitprogram(int signum)
{
	if (signum == SIGINT)
	{
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if (clients[i].fd == -1)
				continue ;
			close(clients[i].fd);
		}
		clear_clients(clients, MAX_CLIENTS);
		exit(0);
	}
}

int 			main(int ac, char **av)
{
	char		*ip;
	char		*port;
	int			(*func)(int, const struct sockaddr *, socklen_t);
	int			(*func2)(int, int);
	int			size;
	int			is_client;
	char 		*user;

	clear_clients(clients, MAX_CLIENTS);
	if (ac != 3)
		return (usage(*av));
	if ((user = getenv("USER")) == NULL || !*user)
		return (printf("Error: $USER variable not set or empty.\n"));
	signal(SIGINT, &quitprogram);
	if (strcmp(av[1], "-l") == 0) {
		ip = "localhost";
		port = av[2];
		func = &bind;
		func2 = &listen;
		size = MAX_CLIENTS;
		is_client = 0;
	} else {
		ip = av[1];
		port = av[2];
		func = &connect;
		func2 = NULL;
		size = 2;
		is_client = 1;
		strcpy(clients[1].wr, "/USER ");
		strcat(clients[1].wr, user);
	}
	if ((clients[0].fd = opensocket(ip, port, func, func2)) == 0)
		return (1);
	strncpy(clients[0].user, "[Server] ", sizeof(clients[0].user) - 1);
	clients[1].fd = STDIN_FILENO;
	strcpy(clients[1].user, "[");
	strncpy(clients[1].user + 1, user, 8);
	strcat(clients[1].user, "] ");
	loop(size, is_client);
	return (0);
}
