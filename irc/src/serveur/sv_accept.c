/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:16:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/26 20:32:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <time.h>
#include <arpa/inet.h>

static void				sv_print(int id, int port, t_env *e)
{
	if (e->verb)
	{
		ft_putstr("\e[32mSERVEUR: New client #\e[0m");
		ft_putnbr(id);
		ft_putstr("\e[32m from \e[0m");
		ft_putstr(e->fds[id].addr);
		ft_putstr(" \e[32mport:\e[0m");
		ft_putnbr(port);
		ft_putchar('\n');
	}
}

static void				sv_fill_buf(t_buf *info, char *buff)
{
	info->start = &buff[0];
	info->end = &buff[BUFF];
	info->head = &buff[0];
	info->tail = &buff[0];
}

static void				sv_new_client(t_env *e, int i, int port)
{
	e->members++;
	e->chan->users++;
	e->fds[i].type = FD_CLIENT;
	e->fds[i].time = time(NULL);
	ft_strcpy(e->fds[i].name, ft_strjoin("guest", ft_itoa(i)));
	ft_strcpy(e->fds[i].chan, "Global");
	send(e->fds[i].fd, e->fds[i].name, NAME_SIZE, 0);
	e->fds[i].fct_read = sv_cl_read;
	e->fds[i].fct_write = sv_cl_write;
	sv_fill_buf(&e->fds[i].rd, e->fds[i].buf_read);
	sv_fill_buf(&e->fds[i].wr, e->fds[i].buf_write);
	send(e->fds[i].fd, "\e[33;1m\nWelcome to my IRC stranger !\n", 37, 0);
	send(e->fds[i].fd, "You're actually connected to the [\e[0m", 38, 0);
	send(e->fds[i].fd, "Global\e[1;33m] channel.\n", 24, 0);
	send(e->fds[i].fd, "\e[33;1mType /help for a list of usefull ", 40, 0);
	send(e->fds[i].fd, "commands.\nHave Fun !\e[0m\n\n", 27, 0);
	send(e->fds[i].fd, END_CHECK, END_CHECK_LEN, 0);
	sv_print(i, port, e);
}

static int				sv_check_ip(t_env *e, struct sockaddr *csin, int fd)
{
	size_t				i;
	size_t				all;
	size_t				max;

	i = 1;
	while (e->fds[i].type != FD_FREE)
		i++;
	all = 1;
	max = 1;
	inet_ntop(AF_INET6, &((struct sockaddr_in6 *)csin)->sin6_addr,
					e->fds[i].addr, sizeof(e->fds[i].addr));
	while (all < e->maxfd)
	{
		if (e->fds[all].type == FD_CLIENT &&
			!ft_strcmp(e->fds[i].addr, e->fds[i].addr))
		{
			if (max >= MAX_CLIENT_BY_IP)
				return (send(fd, "Not allowed\n", 12, 0));
			max++;
		}
		all++;
	}
	e->fds[i].fd = fd;
	sv_new_client(e, i, ntohs(((struct sockaddr_in6 *)csin)->sin6_port));
	return (0);
}

void					sv_accept(t_env *e)
{
	int					fd;
	struct sockaddr		csin;
	socklen_t			cslenght;

	cslenght = sizeof(csin);
	fd = accept(e->fds[0].fd, &csin, &cslenght);
	if (fd == -1)
		return ;
	if (csin.sa_family == AF_INET)
		ft_putendl("v4");
	if (e->members >= e->maxfd)
		send(fd, "Server: Maximum clients reached. Try again later\n", 49, 0);
	else if (sv_check_ip(e, &csin, fd) == 0)
		return ;
	close(fd);
}
