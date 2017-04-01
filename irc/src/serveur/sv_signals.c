/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 00:27:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 08:49:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>

static void		ft_kill_connections(t_fd *client)
{
	t_listin	*next;

	if (client == NULL)
		return ;
	if (client->next)
		ft_kill_connections(client->next);
	close(client->fd);
	if (e.verb)
		printf("CLIENT %s:%s killed\n", client->addr, client->port);
	if (client->reg.password)
		free(client->reg.password);
	ft_free(&client->reg.realname);
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

static void		ft_kill_channels(t_chan *chan)
{
	t_listin	*next;

	if (chan == NULL)
		return ;
	if (chan->next)
		ft_kill_channels(chan->next);
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

void			sv_server_killed(int sig)
{
	(void)sig;
	if (e.verb)
	{
		if (sig == SIGTERM)
			ft_putstr_fd("\nServer Killed By SIGTERM", 2);
		if (sig == SIGINT)
			ft_putstr_fd("\nServer Killed By SIGINT", 2);
		if (sig == SIGBUS)
			ft_putstr_fd("\nServer Killed By SIGBUS", 2);
	}
	write(2, "\n", 1);
	update_users_file(&e);
	ft_kill_connections(e.fds);
	ft_kill_channels(e.chans);
	FD_ZERO(&e.fd_read);
	FD_ZERO(&e.fd_write);
	close(e.ipv4);
	close(e.ipv6);
	ft_bzero(&e, sizeof(e));
	exit(0);
}
