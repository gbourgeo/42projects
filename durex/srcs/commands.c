/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2018/07/19 04:39:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "durex.h"

void			serverHelp(t_cl *client)
{
	char		*cmd[] = { SERVER_COMMANDS };
	char		*hlp[] = { SERVER_HELP };

	for (size_t i = 0; i < sizeof(cmd) / sizeof(*cmd); i++) {
		clientWrite(cmd[i], client);
		clientWrite(": ", client);
		clientWrite(hlp[i], client);
		clientWrite("\n", client);
	}
}

void			serverShell(t_cl *client)
{
	ft_dprintf(client->fd, "Spawning shell on port %s\n", SERVER_PORT + 1);
	
	serverQuitClient(client);
}

void			serverQuitClient(t_cl *client)
{
	close(client->fd);
	clearClient(client);
}
