/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:26:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/05 00:46:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include "main.h"

static void		serverUptime(unsigned long long up, char *buf, size_t size, t_cl *client)
{
	static t_uptime	uptime[] = {
		{ "Second(s)", 60 },
		{ "Minute(s)", 60 },
		{ "Hour(s)", 24 },
		{ "Day(s)", 0 },
	};
	static int		i = 0;

	if (uptime[i].revolution)
	{
		i++;
		serverUptime(up / uptime[i - 1].revolution, buf, size, client);
		i--;
		up %= uptime[i].revolution;
	}
	snprintf(buf, size, " %lld", up);
	clientWrite(buf, client);
	snprintf(buf, size, " %s", uptime[i].str);
	clientWrite(buf, client);
	if (i == 0)
		clientWrite("\n", client);
}

static void		printStats(char *buf, size_t size, t_cl *client)
{
	snprintf(buf, size, "- %d: Online (fd=%d)\n", client->id, client->fd);
	clientWrite(buf, client);
	snprintf(buf, size, "\tAddress: %s\n", client->addr);
	clientWrite(buf, client);
	snprintf(buf, size, "\tHost   : %s\n", client->host);
	clientWrite(buf, client);
	snprintf(buf, size, "\tPort   : %s\n", client->port);
	clientWrite(buf, client);
	snprintf(buf, size, "\tShell  : %s\n", client->shell != -1 ? "Opened" : "Closed");
	clientWrite(buf, client);
	snprintf(buf, size, "\tLogged : %s\n", client->logged ? "Yes" : "No");
}

void			serverPrintStats(t_cl *client, t_cmd *cmds)
{
	char		buf[1048];

	(void)cmds;
	serverLog(1, "[CMDS] - %d: Statistics wanted.\n", client->id);
	clientWrite("Server Up time : ", client);
	serverUptime(time(NULL) - e.server.uptime, buf, sizeof(buf), client);
	clientWrite("Clients connected:\n", client);
	for (size_t i = 0; i < SERVER_CLIENT_MAX; i++)
	{
		if (e.server.client[i].fd != -1)
			printStats(buf, sizeof(buf), e.server.client + i);
		else
			snprintf(buf, sizeof(buf), "- %d: Offline\n", e.server.client[i].id);
		clientWrite(buf, client);
	}
	clientWrite("$> ", client);
}
