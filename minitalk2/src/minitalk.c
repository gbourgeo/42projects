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

extern t_cl		clients[];

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
		clients[0].fd = STDOUT_FILENO;
		clients[0].try = 1;
		strncpy(clients[0].user, opt->user, NICK_CLIENTS - 1);
		strcpy(clients[0].wr, "/NICK ");
		strcat(clients[0].wr, opt->user);
		add_user(clients[0].user);
	} else {
		opt->ip = av[1];
		opt->port = av[2];
		opt->size = 2;
		if (!(opt->fd = opensocket(opt->ip, opt->port, &connect, NULL)))
			return (-1);
		clear_clients(clients, 2);
		clients[0].fd = STDOUT_FILENO;
		clients[0].try = 1;
		opt->user = "Paul";
		strncpy(clients[0].user, opt->user, NICK_CLIENTS - 1);
		strcpy(clients[0].wr, "/NICK ");
		strcat(clients[0].wr, opt->user);
		clients[1].fd = opt->fd;
		clients[1].try = 2;
		strncpy(clients[1].user, "Server", NICK_CLIENTS - 1);
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
