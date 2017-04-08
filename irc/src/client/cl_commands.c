/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 03:00:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/08 04:54:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/socket.h>

static int		cl_nick_check(char *nick)
{
	int			i;

	if (!nick || !*nick)
		return (1);
	if (sv_strcmp(nick, "anonymous") || ft_isalpha(*nick) || ISSPECIAL(*nick))
	{
		i = 1;
		while (nick[i] && i <= NICK_LEN)
		{
			if (ft_isalpha(nick[i]) || ft_isdigit(nick[i]) ||
				ISSPECIAL(nick[i]) || nick[i] == '-')
				i++;
			else
				return (2);
		}
		return (0);
	}
	return (2);
}

void			cl_nick(char **cmds, t_client *cl)
{
	int			err;

	err = cl_nick_check(cmds[1]);
	if (err == 1)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putendl_fd(" :No nickname given", STDERR_FILENO);
	}
	else if (err == 2)
	{
		ft_putstr_fd(cmds[1], STDERR_FILENO);
		ft_putendl_fd(" :Erroneus nickname", STDERR_FILENO);
	}
	else
		ft_strncpy(cl->nick, cmds[1], NICK_LEN);
}

void			cl_help(char **cmds, t_client *cl)
{
	(void)cmds;
	(void)cl;
	ft_putstr("The commands described here are used to register a connection");
	ft_putstr(" with an \nIRC server as a user as well as to correctly ");
	ft_putstr("disconnect.\n\n");
	ft_putstr("A \"PASS\" command is not required for a client connection ");
	ft_putstr("to be \nregistered, but it MUST precede the latter of the ");
	ft_putstr("NICK/USER \ncombination (for a user connection) or the SERVICE");
	ft_putstr(" command (for a\nservice connection). The RECOMMENDED order ");
	ft_putstr("for a client to register\nis as follows:\n\n");
	ft_putstr("                           1. Pass message\n");
	ft_putstr("           2. Nick message                2. Service message\n");
	ft_putstr("           3. User message\n\n");
	ft_putstr("Upon success, the client will receive an RPL_WELCOME ");
	ft_putstr("(for users) or\nRPL_YOURESERVICE (for services) message ");
	ft_putstr("indicating that the\nconnection is now registered and known ");
	ft_putstr("the to the entire IRC network.\nThe reply message MUST contain");
	ft_putstr(" the full client identifier upon which\nit was registered.\n\n");
	ft_putendl("CONNECT <target_server> [port]");
	ft_putendl("HELP");
	ft_putendl("NICK <nickname>");
	ft_putendl("PASS <passwordhere>");
	ft_putendl("USER <user> <mode> <unused> <realname>");
	ft_putendl("QUIT");
}

void			cl_quit(char **cmds, t_client *cl)
{
	ft_free(&cmds);
	if (cl->sock > 0)
		close(cl->sock);
	FD_ZERO(&cl->fds);
	if (cl->pass)
		free(cl->pass);
	ft_free(&cl->user);
	ft_memset(cl, 0, sizeof(*cl));
	ft_putendl("Client leaved. Bye.");
	exit(0);
}

void			cl_connect(char **cmds, t_client *cl)
{
	char		*port;

	if (!cmds[1])
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		return (ft_putendl_fd(ERR_NEEDMOREPARAMS, 2));
	}
	port = (cmds[2]) ? cmds[2] : ft_strrchr(cmds[1], ':');
	if (port && !cmds[2])
		*port++ = 0;
	if (port == NULL || *port == 0)
		port = DEF_PORT;
	if (cl_getaddrinfo(cmds[1], port, cl))
		return ;
	if (cl->pass && sleep(1))
		cl_send(cl->sock, "PASS ", cl->pass, NULL);
	if (*cl->nick && sleep(1))
		cl_send(cl->sock, "NICK ", cl->nick, NULL);
	if (cl->user && sleep(1))
		cl_send(cl->sock, "USER ", *cl->user, cl->user);
}
