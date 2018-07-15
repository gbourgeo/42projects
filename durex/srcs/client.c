/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:49:03 by root              #+#    #+#             */
/*   Updated: 2018/07/15 05:20:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			clearClient(t_cl *client)
{
	client->fd = -1;
	client->logged = 0;
	memset(client->rd, 0, CLIENT_BUFF);
	client->rdHead = &client->rd[0];
	client->rdTail = client->rdHead;
	memset(client->wr, 0, CLIENT_BUFF);
	client->wrHead = &client->wr[0];
	client->wrTail = client->wrHead;
}

void			clientRead(t_cl *client)
{
	(void)client;
}

void			clientWrite(char *str, t_cl *client)
{
	
}
