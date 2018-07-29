/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:49:03 by root              #+#    #+#             */
/*   Updated: 2018/07/29 09:17:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			clearClient(t_cl *client)
{
	client->fd = -1;
	client->logged = 0;
	memset(&client->rd, 0, sizeof(client->rd));
	client->rd.head = &client->rd.buff[0];
	client->rd.tail = client->rd.head;
	memset(&client->wr, 0, sizeof(client->wr));
	client->wr.head = &client->wr.buff[0];
	client->wr.tail = client->wr.head;
}

void			clientRead(char *buff, int size, t_cl *client)
{
	int			i;

	i = 0;
	while (i < size) {
		*client->rd.head = buff[i];
		client->rd.head = moveTail(client->rd.head, client->rd.buff, SERVER_CLIENT_BUFF);
		if (client->rd.head == client->rd.tail) {
			client->rd.tail = moveTail(client->rd.tail, client->rd.buff, SERVER_CLIENT_BUFF);
		}
		i++;
	}
}

void			clientWrite(char *str, t_cl *client)
{
	while (*str) {
		*client->wr.head = *str;
		client->wr.head = moveTail(client->wr.head, client->wr.buff, SERVER_CLIENT_BUFF);
		if (client->wr.head == client->wr.tail) {
			client->wr.tail = moveTail(client->wr.tail, client->wr.buff, SERVER_CLIENT_BUFF);
		}
		str++;
	}
}
