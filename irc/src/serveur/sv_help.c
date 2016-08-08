/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 10:00:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/02 17:10:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_explain(int nb, t_fd *cl)
{
	static char	*msg[] = { "Mark yourself as being away. <message> is a messag"\
						"e that will be\nautomatically sent to anyone who trie"\
						"s sending you a private message.\nIf you are already "\
						"marked as being away, /away will change your status\n"\
						"back to \"here\".",
						"Request the server to establish a connection to <host"\
						">.\nIt is only available to IRC Operators.",
						"/help without parameters lists all IRC commands.\n/he"\
						"lp with a command name prints info about that command",
						"Leave the current channel and join a new one.",
						"Leave the current channel.",
						"Lists all active channels and, if set, their topics.",
						"Send a private message.",
						"Change your nickname. You can't choose a nickname al"\
						"ready in use.\nPlus, some characters are forbiden.",
						"Exit from FT_IRC.",
						"Sets the topic for the channel you're on.",
						"Without parameters lists users on all channels.\n"\
						"Followed by a channel, lists users on that channel.\n"\
						"/who * lists users on the same channel as you." };

	send(cl->fd, msg[nb], ft_strlen(msg[nb]), 0);
}

static void		sv_specific_help(char **name, char **cmds, t_fd *cl)
{
	static char	*syntax[] = { SYNTAX1, SYNTAX2, SYNTAX3 };
	int			nb;

	nb = 0;
	while (name[nb] && ft_strcmp(name[nb] + 1, cmds[1]))
		nb++;
	if (name[nb] == NULL)
	{
		send(cl->fd, "*** There is no help info about that command.\n", 46, 0);
		send(cl->fd, "*** Type \"/help\" to get a list of commands.", 43, 0);
		return ;
	}
	send(cl->fd, "*** Help: ", 10, 0);
	send(cl->fd, name[nb], ft_strlen(name[nb]), 0);
	send(cl->fd, "\t", 1, 0);
	send(cl->fd, syntax[nb], ft_strlen(syntax[nb]), 0);
	send(cl->fd, "\n", 1, 0);
	sv_explain(nb, cl);
}

void			sv_help(char **cmds, t_env *e, t_fd *cl)
{
	static char	*name[] = { COMMANDS1, COMMANDS2 };
	int			nb;

	(void)e;
	nb = 0;
	if (!cmds[1] || !*cmds[1])
	{
		send(cl->fd, "\e[33m*** Help: FT_IRC Commands:\e[0m", 35, 0);
		while (name[nb])
		{
			send(cl->fd, "\n", 1, 0);
			send(cl->fd, name[nb], ft_strlen(name[nb]), 0);
			nb++;
		}
		send(cl->fd, "\n\nType /help <command> to get help about a ", 43, 0);
		send(cl->fd, "particular command.\n", 20, 0);
		send(cl->fd, "For example \"/help nick\" gives you help about", 45, 0);
		send(cl->fd, " the /nick command.\nTo use a command you must", 45, 0);
		send(cl->fd, " prefix it with a slash \"/\".\n", 29, 0);
		send(cl->fd, "*** End Help", 12, 0);
	}
	else
		sv_specific_help(name, cmds, cl);
	send(cl->fd, "\r\n", 2, 0);
}
