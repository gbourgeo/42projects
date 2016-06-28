/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_command_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/28 02:06:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_nick(char **cmds, t_env *e, size_t i)
{
	size_t		all;

	all = 0;
	if (cmds[1])
	{
		while (all < e->maxfd)
		{
			if (e->fds[all].type == FD_CLIENT &&
				!ft_strncmp(e->fds[all].name, cmds[1], NAME_SIZE))
			{
				send(e->fds[i].fd, "\e[31mNick already taken.\n\e[0m", 29, 0);
				return ;
			}
			all++;
		}
		ft_strncpy(e->fds[i].name, cmds[1], NAME_SIZE + 1);
		return ;
	}
	send(e->fds[i].fd, "\e[31mUsage: /nick [name]\n\e[0m", 29, 0);
}

void			sv_who(char **cmds, t_env *e, size_t i)
{
	size_t		all;

	all = 0;
	send(e->fds[i].fd, "\e[33m[\e[0m", 10, 0);
	send(e->fds[i].fd, e->fds[i].chan, CHAN_SIZE, 0);
	send(e->fds[i].fd, "\e[33m] users:\n\e[0m", 18, 0);
	while (all < e->maxfd)
	{
		if (e->fds[all].type == FD_CLIENT &&
			!ft_strcmp(e->fds[all].chan, e->fds[i].chan))
		{
			send(e->fds[i].fd, "- ", 2, 0);
			send(e->fds[i].fd, e->fds[all].name, NAME_SIZE, 0);
			send(e->fds[i].fd, "\n", 1, 0);
		}
		all++;
	}
	(void)cmds;
}

void			sv_list(char **cmds, t_env *e, size_t i)
{
	t_chan		*tmp;

	tmp = e->chan;
	send(e->fds[i].fd, "\e[33mChannels list:\n\e[0m", 24, 0);
	while (tmp)
	{
		send(e->fds[i].fd, "\e[33m- \e[0m", 11, 0);
		send(e->fds[i].fd, tmp->name, CHAN_SIZE, 0);
		if (!ft_strcmp(tmp->name, e->fds[i].chan))
			send(e->fds[i].fd, "*", 1, 0);
		send(e->fds[i].fd, "\n", 1, 0);
		tmp = tmp->next;
	}
	(void)cmds;
}

void			sv_help(char **cmds, t_env *e, size_t i)
{
	int			fd;

	fd = e->fds[i].fd;
	send(fd, "\e[33mFT_IRC commands :\n\e[0m", 27, 0);
	send(fd, "/nick    <nickname>\n", 20, 0);
	send(fd, "/join    <channel>\n", 19, 0);
	send(fd, "/leave   <channel>\n", 19, 0);
	send(fd, "/msg     <client> <message>\n", 28, 0);
	send(fd, "/connect <_host_[:port]>\n", 25, 0);
	send(fd, "/who     : list the current channel users.\n", 43, 0);
	send(fd, "/list    : list the IRC channels.\n", 34, 0);
	send(fd, "/quit    : quit the server.\n", 29, 0);
	(void)cmds;
}

void			sv_connect(char **cmds, t_env *e, size_t i)
{
	(void)cmds;
	(void)e;
	(void)i;
}
