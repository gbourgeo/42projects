/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2018/07/16 23:29:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

void			serverHelp(t_cl *client)
{
	char		*cmd[] = { SERVER_COMMANDS };
	char		*hlp[] = { SERVER_HELP };

	for (size_t i = 0; i < sizeof(cmd) / sizeof(*cmd); i++) {
		clientWrite(cmd[i], client);
		clientWrite(": ", client);
		clientWrite(hlp[i], client);
	}
}

void			serverShell(t_cl *client)
{
	(void)client;
}
