/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 02:31:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 09:33:34 by root             ###   ########.fr       */
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

static int		get_options(t_opt *opt, char **av)
{
	if (strcmp(av[1], "-l") == 0) {
		opt->ip = "localhost";
		opt->port = av[2];
		opt->size = MAX_CLIENTS;
		if (!(opt->fd = opensocket(opt->ip, opt->port, &bind, &listen)))
			return (-1);
		clear_clients(&clients[0], 1);
		clients[0].fd = STDIN_FILENO;
		clients[0].try = 0;
		strcpy(clients[0].user, opt->user);
	} else {
		opt->ip = av[1];
		opt->port = av[2];
		opt->size = 2;
		if (!(opt->fd = opensocket(opt->ip, opt->port, &connect, NULL)))
			return (-1);
		clear_clients(&clients[0], 1);
		clients[0].fd = opt->fd;
		clients[0].try = 0;
		strncpy(clients[0].user, "Server", sizeof(clients[0].user) - 1);
		clear_clients(&clients[1], 1);
		clients[1].fd = STDIN_FILENO;
		clients[1].try = 0;
		strcpy(clients[1].user, opt->user);
		strcpy(clients[1].rd, "/USER ");
		strcat(clients[1].rd, clients[1].user);
		write(opt->fd, clients[1].rd, strlen(clients[1].rd));
		memset(clients[1].rd, 0, sizeof(clients[1].rd));
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
	signal(SIGWINCH, &changewindow);
	clear_clients(clients, MAX_CLIENTS);
	if (get_options(&opt, av) != -1)
		loop(opt.fd, opt.size, opt.ip, opt.port);
	return (0);
}
