/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 02:31:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/29 09:45:28 by root             ###   ########.fr       */
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

static int		get_options(t_opt *opt, char **av)
{
	if (strcmp(av[1], "-l") == 0) {
		opt->ip = "localhost";
		opt->port = av[2];
		opt->size = MAX_CLIENTS;
		if (!(opt->fd = opensocket(opt->ip, opt->port, &bind, &listen)))
			return (-1);
		clients[0].fd = STDIN_FILENO;
		strcpy(clients[0].user, "[");
		strncpy(clients[0].user + 1, opt->user, 8);
		strcat(clients[0].user, "] ");
	} else {
		opt->ip = av[1];
		opt->port = av[2];
		opt->size = 2;
		strcpy(clients[1].wr, "/USER ");
		strcat(clients[1].wr, opt->user);
		if (!(opt->fd = opensocket(opt->ip, opt->port, &connect, NULL)))
			return (-1);
		clients[0].fd = opt->fd;
		strncpy(clients[0].user, "[Server] ", sizeof(clients[0].user) - 1);
		clients[1].fd = STDIN_FILENO;
		strcpy(clients[1].user, "[");
		strncpy(clients[1].user + 1, opt->user, 8);
		strcat(clients[1].user, "] ");
		opt->fd = 0;
	}
	return (opt->fd);
}

int 			main(int ac, char **av)
{
	t_opt		opt;

	if (ac != 3)
		return (usage(*av));
	if ((opt.user = getenv("USER")) == NULL || !*opt.user)
		return (printf("Error: $USER variable not set or empty.\n"));
	signal(SIGINT, &quitprogram);
	clear_clients(clients, MAX_CLIENTS);
	if (get_options(&opt, av) != -1)
		loop(opt.fd, opt.size);
	return (0);
}
