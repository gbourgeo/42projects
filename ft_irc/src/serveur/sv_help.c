/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 10:00:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/26 01:04:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_help_msg(char *num, char *txt, t_env *e, t_fd *cl)
{
	int			nb;

	nb = 0;
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(num, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(e->ptr, &cl->wr);
	sv_cl_write(" :", &cl->wr);
	sv_cl_write(txt, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

static void		sv_explain(int nb, t_fd *cl, t_env *e)
{
	static char	*msg[][80] = { HELP1, HELP2, HELP3 };
	int			pos;

	pos = 0;
	while (msg[nb][pos])
	{
		sv_help_msg("705", msg[nb][pos], e, cl);
		pos++;
	}
	sv_help_msg("705", "", e, cl);
}

static void		sv_specific_help(char **name, char **cmds, t_fd *cl, t_env *e)
{
	static char	*s[] = { SYNTAX1, SYNTAX2 };
	int			nb;

	while (*cmds)
	{
		nb = 0;
		while (name[nb] && sv_strcmp(name[nb], *cmds))
			nb++;
		if (name[nb] == NULL)
			sv_help_msg("524", ":Help not found", e, cl);
		else
		{
			e->ptr = *cmds;
			sv_help_msg("704", s[nb], e, cl);
			sv_help_msg("705", "", e, cl);
			sv_explain(nb, cl, e);
		}
		cmds++;
	}
}

void			sv_help(char **cmds, t_env *e, t_fd *cl)
{
	static char	*name[] = { COMMANDS1, COMMANDS2 };
	int			nb;

	nb = 0;
	if (!cmds[0] || !*cmds[0])
	{
		e->ptr = "index";
		sv_help_msg("704", "Help commands available to users:", e, cl);
		sv_help_msg("705", "", e, cl);
		while (name[nb])
			sv_help_msg("705", name[nb++], e, cl);
		sv_help_msg("705", "Type HELP [<command>] to get help about a ", e, cl);
		sv_help_msg("705", "specific command.", e, cl);
	}
	else
		sv_specific_help(name, cmds, cl, e);
	sv_help_msg("706", "End of /HELP", e, cl);
	e->ptr = NULL;
}
