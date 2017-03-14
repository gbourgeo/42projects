/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 04:01:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 01:45:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int		sv_size(char *str)
{
	int			i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void			sv_err(char *err, char *cmd, char *cmd2, t_fd *cl, t_env *e)
{
	static char	*replies[] = { { NULL, NULL, NULL },
							   { cmd, NULL, ":No such nick" },
							   { cmd, NULL, ":No such server" },
							   { cmd, NULL, ":No such channel" },
							   { cmd, NULL, ":Cannot send to channel" },
							   { cmd, NULL, ":You have joined too many channels" },
							   { cmd, NULL, ":There was no such nickname" },
							   { cmd, NULL, ":Too many recipients. abort" }, //407
							   { cmd, NULL, ":No such service" }, //408
							   { cmd, NULL, ":No origin specified" },
							   { NULL, NULL, NULL }, //410
							   { ":No recipient given (", cmd, ")" },
							   { NULL, NULL, ":No text to send" },
							   { cmd, NULL, ":No toplevel domain specified" },
							   { cmd, NULL, ":Wildcard in toplevel domain" },
							   { cmd, NULL, ":Bad Server/host mask" }, //415
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, //416-420
							   { cmd, NULL, ":Unknown command" },
							   { cmd, NULL, ":MOTD file is missing" },
							   { cmd, NULL, ":No administrative info available" },
							   { cmd, NULL, ":File error..." }, //424 missing some parameters
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }, //425-430
							   { NULL, NULL, ":No nickname given" },
							   { cmd, NULL, ":Erroneus nickname" },
							   { cmd, NULL, ":Nickname is already in use" }, //433
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, //434-435
							   { cmd, NULL, ":Nickname collision" },
							   { cmd, NULL, ":Nick/channel is temporarily unavailable" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }, //438-440
							   { cmd, cmd2, ":They aren't on that channel" },
							   { cmd, NULL, ":You're not on that channel" }, //442
							   { cmd, cmd2, ":is already on channel" },
							   { cmd, NULL, ":User not logged in" },
							   { NULL, NULL, ":SUMMON has been disabled" },
							   { NULL, NULL, ":USERS has been disbled" }, //446
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, //447-450
							   { NULL, NULL, ":You have not registered" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }, //452-460
							   { cmd, NULL, ":Not enough parameters" }, //461
							   { NULL, NULL, ":Unauthorized command (already registered)" },
							   { NULL, NULL, ":Your host isn't among the privileged" },
							   { NULL, NULL, ":Password incorrect" },
							   { NULL, NULL, ":You are banned from this server" },
							   { NULL, NULL, ":You will be banned soon" },
							   { cmd, NULL, ":Channel key already set" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }, //468-470
							   { cmd, NULL, ":Cannot join channel (+1)" },
							   { cmd, ":is unknown mode char to me for ", cmd2 },
							   { cmd, NULL, ":Cannot join channel (+i)" },
							   { cmd, NULL, ":Cannot join channel (+b)" },
							   { cmd, NULL, ":Cannot join channel (+k)" },
							   { cmd, NULL, ":Bad channel mask" },
							   { cmd, NULL, ":Channel doesn't support modes" },
							   { cmd, cmd2, ":Channel list is full" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, //479-480
							   { NULL, NULL, ":Permission Denied- You're not an FT_IRC operator" },
							   { cmd, NULL, ":You're not channel operator" },
							   { NULL, NULL, ":You can't kill a server!" },
							   { cmd, NULL, ":Your connection is restricted!" },
							   { cmd, NULL, ":You're not the original channel operator" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, //486-490
							   { NULL, NULL, ":No O-lines for your host" },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
							   { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }, //492-500
							   { NULL, NULL, ":Unknown MODE flag" },
							   { cmd, NULL, ":Cannot change mode for other users" } };
	int			pos;

	if (ft_strlen(err) != 3)
		return ;
	pos = ft_atoi(err + 1);
	if (*err - '0' == 4 || (*err - '0' == 5 && pos < 3))
	{
		send(cl->fd, e->name, SERVER_LEN, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, err, sv_size(err), 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		if (*replies[*err - '0' - 4])
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, replies[*err - '0' - 4], sv_size(replies[*err - '0' - 4]), 0);
		}
		if (*(replies[*err - '0' - 4] + 1))
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, str, sv_size(str), 0);
		}
		if (*(replies[*err - '0' - 4] + 1))
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
		}
	}
}
