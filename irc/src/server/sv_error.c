/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 07:34:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/17 14:52:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void		sv_kill_channels(t_chan *chan)
{
	t_listin	*next;

	if (chan == NULL)
		return ;
	if (chan->next)
		sv_kill_channels(chan->next);
	if (e.verb)
		printf("\n\e[31mCHAN\e[0m %s \e[31mdeleted\e[0m\n", chan->name);
	ft_bzero(chan->name, CHANNAME_LEN);
	ft_bzero(chan->topic, TOPIC_LEN);
	while (chan->users)
	{
		next = chan->users->next;
		free(chan->users);
		chan->users = next;
	}
	free(chan);
	chan = NULL;
}

static void		sv_kill_connections(t_fd *client)
{
	t_listin	*next;

	if (client == NULL)
		return ;
	if (client->next)
		sv_kill_connections(client->next);
	close(client->i.fd);
	if (e.verb)
		printf("CLIENT %s:%s killed\n", client->i.addr, client->i.port);
	if (!client->inf->pass)
	{
		ft_free(&client->inf->realname);
		free(client->inf);
	}
	if (client->away)
		free(client->away);
	while (client->chans)
	{
		next = client->chans->next;
		free(client->chans);
		client->chans = next;
	}
	ft_bzero(client, sizeof(*client));
	free(client);
	client = NULL;
}

void			sv_error(char *str, t_env *e)
{
	sv_kill_connections(e->fds);
	sv_kill_channels(e->chans);
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	close(e->v4.fd);
	close(e->v6.fd);
	if (e->verb)
		fprintf(stderr, "\b\b:%s NOTICE * :*** %s: %s\n", e->name, str, strerror(errno));
	ft_memset(e, 0, sizeof(*e));
	exit(EXIT_FAILURE);
}
