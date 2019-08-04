/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:57:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/04 23:58:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void				serverShell(t_cl *client, t_cmd *cmds)
{
	(void)cmds;
	serverLog(1, "[CMDS] - %d: Shell wanted.\n", client->id);
	client->shell = spawnShell(client->fd);
	if (client->shell == -1)
		clientWrite("Failed to spawn a shell...\n", client);
}
