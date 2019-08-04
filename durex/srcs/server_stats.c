/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_stats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 01:26:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/04 04:45:41 by gbourgeo         ###   ########.fr       */
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
		{
			snprintf(buf, sizeof(buf), "- %d: Online (fd=%d)\n", e.server.client[i].id, e.server.client[i].fd);
			clientWrite(buf, client);
			snprintf(buf, sizeof(buf), "\tAddress: %s\n", e.server.client[i].addr);
			clientWrite(buf, client);
			snprintf(buf, sizeof(buf), "\tHost   : %s\n", e.server.client[i].host);
			clientWrite(buf, client);
			snprintf(buf, sizeof(buf), "\tPort   : %s\n", e.server.client[i].port);
			clientWrite(buf, client);
			snprintf(buf, sizeof(buf), "\tShell  : %s\n", e.server.client[i].shell != -1 ? "Opened" : "Closed");
			clientWrite(buf, client);
			snprintf(buf, sizeof(buf), "\tLogged : %s\n", e.server.client[i].logged ? "Yes" : "No");
			clientWrite(buf, client);
		}
		else
		{
			snprintf(buf, sizeof(buf), "- %d: Offline\n", e.server.client[i].id);
			clientWrite(buf, client);
		}
	}
	clientWrite("$> ", client);
}
