/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_print_logs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:07:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/05 00:38:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "durex.h"

static void		printLogs(t_cl *client)
{
	int			fd;
	char		buf[128];
	int			ret;

	serverLog(1, "[CMDS] - %d: Logs wanted.\n", client->id);
	fd = open(SERVER_REPORTER, O_RDONLY);
	if (fd < 0)
		clientWrite("Failed to open logs...\n", client);
	else {
		while (1) {
			ret = read(fd, buf, sizeof(buf) - 1);
			if (ret <= 0)
				break ;
			buf[ret] = '\0';
			clientWrite(buf, client);
		}
		close(fd);
	}
}

void			serverPrintLogs(t_cl *client, t_cmd *cmds)
{
	char		**options;

	options = mysplitwhitespaces(cmds->opt);
	if (!options)
		serverLog(1, "[ERRO] - %d: Failed to split command.\n", client->id);
	else if (!options[1])
		printLogs(client);
	else if (!mystrcmp(options[1], "clear"))
		serverClearLogs(client);
	else
	{
		clientWrite("Wrong option '", client);
		clientWrite(options[1], client);
		clientWrite("'\n", client);
	}
	mytabdel(&options);
	clientWrite("$> ", client);
}
