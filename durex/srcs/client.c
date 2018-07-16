/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:49:03 by root              #+#    #+#             */
/*   Updated: 2018/07/16 22:19:33 by root             ###   ########.fr       */
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
		if (client->rd.head + 1 == client->rd.buff + CLIENT_BUFF)
			client->rd.head = client->rd.buff;
		else
			client->rd.head++;
		if (client->rd.tail == client->rd.head) {
			if (client->rd.tail + 1 == client->rd.buff + CLIENT_BUFF)
				client->rd.tail = client->rd.buff;
			else
				client->rd.tail++;
		}
		i++;
	}
}

void			clientWrite(char *str, t_cl *client)
{
	while (*str) {
		*client->wr.head = *str;
		if (client->wr.head + 1 == client->wr.buff + CLIENT_BUFF)
			client->wr.head = client->wr.buff;
		else
			client->wr.head++;
		if (client->wr.tail == client->wr.head) {
			if (client->wr.tail + 1 == client->wr.buff + CLIENT_BUFF)
				client->wr.tail = client->wr.buff;
			else
				client->wr.tail++;
		}
		str++;
	}
}
