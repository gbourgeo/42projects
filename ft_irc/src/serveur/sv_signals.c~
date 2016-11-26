/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 00:27:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/11/17 01:43:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void	ft_kill_connections(t_fd *client)
{
	if (client == NULL)
		return ;
	if (client->next)
		ft_kill_connections(client->next);
	close(client->fd);
	if (client->away)
		free(client->away);
	if (client->user)
	{
		ft_bzero(client->user, sizeof(*client->user));
		free(client->user);
	}
	ft_bzero(client, sizeof(*client));
	free(client);
	client = NULL;
}

static void	ft_kill_channels(t_chan *chan)
{
	if (chan == NULL)
		return ;
	if (chan->next)
		ft_kill_channels(chan->next);
	ft_bzero(chan, sizeof(*chan));
	free(chan);
	chan = NULL;
}

void		sv_quit(int sig)
{
	(void)sig;
	if (e.verb)
	{
		if (sig == SIGTERM)
			ft_putendl_fd("Server Killed By SIGTERM", 2);
		if (sig == SIGINT)
			ft_putendl_fd("Server Killed By SIGINT", 2);
		if (sig == SIGBUS)
			ft_putendl_fd("Server Killed By SIGBUS", 2);
	}
	ft_kill_connections(e.fds);
	ft_kill_channels(e.chan);
	FD_ZERO(&e.fd_read);
	FD_ZERO(&e.fd_write);
	close(e.ipv4);
	close(e.ipv6);
	ft_bzero(&e, sizeof(e));
	exit(0);
}
