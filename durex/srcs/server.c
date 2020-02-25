/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:19:03 by root              #+#    #+#             */
/*   Updated: 2019/08/03 06:52:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
/* inet_ntop */
#include <arpa/inet.h>
/* mutex */
#include <pthread.h>

#include "main.h"

static int			openSocket(struct addrinfo *p)
{
	int				fd;
	int				on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) &&
		!setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) &&
		!bind(fd, p->ai_addr, p->ai_addrlen) &&
		!listen(fd, SERVER_CLIENT_MAX))
		return fd;
	close(fd);
	return -1;
}

int					openServer(const char *addr, const char *port)
{
	int				errcode;
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if ((errcode = getaddrinfo(addr, port, &hints, &res))) {
		serverLog(1, "[ERROR] - %s\n", gai_strerror(errcode));
		return (-1);
	}
	fd = -1;
	p = res;
	while (p != NULL)
	{
		fd = openSocket(p);
		if (fd >= 0)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || fd < 0) {
		serverLog(1, "[ERROR] - Address or Socket can't be found.\n");
		return (-1);
	}
	return e.server.fd = fd;
}

void					serverAcceptConnections()
{
	struct sockaddr		csin;
	socklen_t			len= sizeof(csin);
	int					fd;

	fd = accept(e.server.fd, &csin, &len);
	if (fd < 0) {
		serverLog(1, "[ERROR] - Accept failed.\n");
		return ;
	}
	for (int i = 0; i < SERVER_CLIENT_MAX; i++) {
		if (e.server.client[i].fd == -1) {
			clearClient(&e.server.client[i]);
			e.server.client[i].fd = fd;
			getnameinfo(&csin, sizeof(csin), e.server.client[i].host, NI_MAXHOST,
						e.server.client[i].port, NI_MAXSERV, NI_NUMERICSERV);
			inet_ntop(AF_INET, &((struct sockaddr_in *)&csin)->sin_addr.s_addr,
					  e.server.client[i].addr, sizeof(e.server.client[i].addr));
			serverLog(1, "[LOGS] - New connection from %s:%s (%s)\n", e.server.client[i].addr,
					  e.server.client[i].port, e.server.client[i].host);
			clientWrite("Pass: ", &e.server.client[i]);
			return ;
		}
	}
	write(fd, "Server Full\n", 12);
	close(fd);
}

static int			myustrncmp(unsigned char *s1, unsigned char *s2, int n)
{
	int				i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n) {
		i++;
	}
	return (i != n);
}

static void			serverLogging(unsigned char *buff, int size, t_cl *client)
{
	if (size) {
		mymemset(buff + size, 0, size % 8);
		encryptFunction(buff, size);
		if (!myustrncmp(buff, (unsigned char []){ SERVER_PASS }, size + size % 8)) {
			client->logged = 1;
			clientWrite("$> ", client);
			return ;
		}
	}
	clientWrite("Pass: ", client);
}

void				serverCommands(t_cl *client)
{
	char			buff[SERVER_CLIENT_BUFF];
	size_t			i;
	static t_cmd	cmds[] = { SERVER_COMMANDS };

	/* Here we recreate the client read buffer to get a non truncated string */
	i = 0;
	while (client->rd.tail != client->rd.head) {
		buff[i] = *client->rd.tail;
		client->rd.tail = moveTail(client->rd.tail, client->rd.buff, SERVER_CLIENT_BUFF);
		i++;
	}
	buff[i] = '\0';
	if (!client->logged)
		return serverLogging((unsigned char *)buff, i, client);
	for (i = 0; i < sizeof(cmds) / sizeof(*cmds); i++) {
		int ret = mystrcmp(buff, cmds[i].name);
		if (ret == 0 || ret == ' ') {
			cmds->opt = buff;
			return cmds[i].func(client, cmds);
		}
	}
	clientWrite("Unknown command\n$> ", client);
}

void				serverReadClient(t_cl *client)
{
	char			buff[SERVER_CLIENT_BUFF];
	int				ret;

	ret = read(client->fd, buff, SERVER_CLIENT_BUFF);
	if (ret <= 0)
		return serverQuitClient(client, NULL);
	buff[ret] = '\0';
	if (client->shell != -1) {
		write(client->shell, buff, ret);
		if (!mystrcmp(buff, "exit\n")) {
			serverQuitClientShell(client, NULL);
			clientWrite("$> ", client);
		}
	} else {
		clientRead(buff, ret, client);
	}
}

void				serverReadClientShell(t_cl *client)
{
	char			buff[SERVER_CLIENT_BUFF];
	int				ret;

	ret = read(client->shell, buff, SERVER_CLIENT_BUFF);
	if (ret <= 0)
		return serverQuitClientShell(client, NULL);
	buff[ret] = '\0';
	write(client->fd, buff, ret);
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
		serverQuitClient(&e.server.client[i], NULL);
		clearClient(&e.server.client[i]);
	}
	if (e.server.fd != -1) {
		serverLog(1, "[INFO] - Closing server...\n");
		close(e.server.fd);
	}
	if (e.server.reporter != -1) {
		serverLog(1, "[INFO] - Firing reporter...\n");		
		close(e.server.reporter);
	}
	pthread_mutex_destroy(&e.server.mutex);
}
