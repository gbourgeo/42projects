/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:19:03 by root              #+#    #+#             */
/*   Updated: 2018/07/16 23:40:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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

static void			serverCommand(t_cl *client, char *command, int size)
{
	static char		*cmd[] = { SERVER_COMMANDS };
	static void		(*func[])(t_cl *) = { SERVER_FUNCTIONS };
	
	if (!client->logged) {
		encrypt(command, size);
		//PasTa (5): ffffffa1,25,7d,ffffff92,ffffffca,a,ffffffe5,ffffff99,
		//PasTa (5): -95,37,125,-110,-54,10,-27,-103
		if (command[0] == -95	&&
			command[1] == 37	&&
			command[2] == 125	&&
			command[3] == -110	&&
			command[4] == -54	&&
			command[5] == 10	&&
			command[6] == -27	&&
			command[7] == -103)
			client->logged = 1;
		else
			clientWrite("Pass: ", client);

	} else {
		for (size_t i = 0; i < sizeof(cmd) / sizeof(*cmd); i++) {
			if (!strcmp(cmd[i], command))
				return func[i](client);
		}
	}
}

void				serverReadClient(t_cl *client)
{
	char			buff[CLIENT_BUFF];
	int				ret;
	char			*ptr;

	ret = read(client->fd, buff, CLIENT_BUFF);
	if (ret == -1) {
		close(client->fd);
		clearClient(client);
		return ;
	}
	clientRead(buff, ret, client);
	ret = 0;
	ptr = client->rd.tail;
	while (ptr != client->rd.head) {
		buff[ret++] = *ptr;
		if (*ptr == '\n') {
			buff[ret - 1] = '\0';
			serverCommand(client, buff, ret);
			ret = 0;
		}
		if (ptr + 1 == client->rd.buff + CLIENT_BUFF)
			ptr = client->rd.buff;
		else
			ptr++;
	}
}

void				serverWriteClient(t_cl *client)
{
	int				ret;

	if (client->wr.head != client->wr.tail) {
		if (client->wr.head < client->wr.tail) {
			ret = write(client->fd, client->wr.tail, CLIENT_BUFF - (client->wr.tail - client->wr.buff));
			if (ret == -1) {
				close(client->fd);
				clearClient(client);
				return ;
			}
			client->wr.tail = client->wr.buff;
		} else {
			write(client->fd, client->wr.tail, client->wr.head - client->wr.tail);
			client->wr.tail = client->wr.head;
		}
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
}

