/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_clear_log.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 00:35:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/06 00:36:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* mutex */
#include <pthread.h>

#include "main.h"

void			serverClearLogs(t_cl *client)
{
	int			fd;

	pthread_mutex_lock(&e.server.mutex);
	fd = open(SERVER_REPORTER, O_TRUNC | O_RDWR, 0600);
	if (fd < 0)
		clientWrite("Failed to open logs...\n", client);
	else
	{
		close(e.server.reporter);
		e.server.reporter = fd;
		serverLog(2, "[LOGS] - Server online\n");
		serverLog(1, "[LOGS] - Clients :\n");
		for (size_t i = 0; i < SERVER_CLIENT_MAX; i++)
		{
			if (e.server.client[i].fd != -1)
			{
				serverLog(1, "- %d: Online\n", i + 1);
				serverLog(1, "\tAddress: %s\n", e.server.client[i].addr);
				serverLog(1, "\tHost   : %s\n", e.server.client[i].host);
				serverLog(1, "\tPort   : %s\n", e.server.client[i].port);
				serverLog(1, "\tShell  : %s\n", e.server.client[i].shell != -1 ? "Opened" : "Closed");
				serverLog(1, "\tLogged : %s\n", e.server.client[i].logged ? "Yes" : "No");
			}
			else
				serverLog(1, "- %d: Offline\n", i + 1);
		}
		clientWrite("Logs cleared !\n", client);
	}
	pthread_mutex_unlock(&e.server.mutex);
}
