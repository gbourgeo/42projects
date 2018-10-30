/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:30:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/30 03:03:13 by root             ###   ########.fr       */
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

	wprintTime(ncu.infoLine, time(NULL));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, "Connecting to ");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", ip);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, " on port ");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", port);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, "... ");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wrefresh(ncu.infoLine);
	if ((status = init_addrinfo(ip, port, &results))) {
		wattron(ncu.infoLine, COLOR_PAIR(4));
		wprintw(ncu.infoLine, "%s\n", gai_strerror(status));
		wattroff(ncu.infoLine, COLOR_PAIR(4));
		wrefresh(ncu.infoLine);
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
		wattron(ncu.infoLine, COLOR_PAIR(4));
		wprintw(ncu.infoLine, "\e[31mCan't establish connection.\n\e[0m");
		wattroff(ncu.infoLine, COLOR_PAIR(4));
		wrefresh(ncu.infoLine);
		return (0);
	}
	if (func2)
		func2(fd, MAX_CLIENTS);
	wclear(ncu.infoLine);
	wrefresh(ncu.infoLine);
	wprintTime(ncu.infoLine, time(NULL));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, "Connected to [IPv4] ");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", ip);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, ":");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", port);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wrefresh(ncu.infoLine);
	return (fd);
}
