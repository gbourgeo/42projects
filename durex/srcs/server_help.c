/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:56:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/04 23:56:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void				serverHelp(t_cl *client, t_cmd *cmds)
{
	serverLog(1, "[CMDS] - %d: Help wanted.\n", client->id);
	for (size_t i = 0; cmds[i].name; i++) {
		clientWrite(cmds[i].name, client);
		if (cmds[i].options != NULL) {
			clientWrite(" ", client);
			clientWrite(cmds[i].options, client);
		}
		clientWrite(" : ", client);
		clientWrite(cmds[i].def, client);
		clientWrite("\n", client);
	}
	clientWrite("$> ", client);
}
