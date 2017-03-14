/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 10:00:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 07:10:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_explain(int nb, t_fd *cl)
{
	static char	*msg[] = { SV_HELPMSG1, SV_HELPMSG2, SV_HELPMSG3 };

	send(cl->fd, msg[nb], ft_strlen(msg[nb]), 0);
}

static void		sv_specific_help(char **name, char **cmds, t_fd *cl)
{
	static char	*syntax[] = { SYNTAX1, SYNTAX2, SYNTAX3, SYNTAX4 };
	int			nb;

	while (*(++cmds))
	{
		nb = 0;
		ft_strtoupper(*cmds);
		while (name[nb] && ft_strcmp(name[nb], *cmds))
			nb++;
		send(cl->fd, "*** HELP : ", 11, 0);
		send(cl->fd, *cmds, ft_strlen(*cmds), 0);
		if (name[nb] == NULL)
			send(cl->fd, "\nCommand not available.", 23, 0);
		else
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, syntax[nb], ft_strlen(syntax[nb]), 0);
			send(cl->fd, "\n", 1, 0);
			sv_explain(nb, cl);
		}
		if (*(cmds + 1))
			send(cl->fd, "\n\n", 2, 0);
	}
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
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}
