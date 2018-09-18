/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/02 10:00:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/18 15:00:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		rpl_help(char *num, char *txt, t_env *e, t_fd *cl)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(num, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(e->ptr, cl);
	sv_cl_write(" :", cl);
	sv_cl_write(txt, cl);
	sv_cl_write(END_CHECK, cl);
}

static void		sv_explain(int nb, t_fd *cl, t_env *e)
{
	static char	*msg[][80] = { HELP1, HELP2, HELP3 };
	int			pos;

	pos = 0;
	while (msg[nb][pos])
	{
		rpl_help("705", msg[nb][pos], e, cl);
		pos++;
	}
	rpl_help("705", "", e, cl);
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
			rpl_help("524", ":Help not found", e, cl);
		else
		{
			e->ptr = *cmds;
			rpl_help("704", s[nb], e, cl);
			rpl_help("705", "", e, cl);
			sv_explain(nb, cl, e);
		}
		cmds++;
	}
}

void			sv_help(char **cmds, t_env *e, t_fd *cl)
{
	static char	*name[] = { COMMANDS1, COMMANDS2, COMMANDS3 };
	int			nb;

	nb = 0;
	if (!cmds[0] || !*cmds[0])
	{
		e->ptr = "index";
		rpl_help("704", "Help commands available to users:", e, cl);
		rpl_help("705", "", e, cl);
		while (name[nb])
			rpl_help("705", name[nb++], e, cl);
		rpl_help("705", "Type HELP [<command>] to get help about a ", e, cl);
		rpl_help("705", "specific command.", e, cl);
	}
	else
		sv_specific_help(name, cmds, cl, e);
	rpl_help("706", "End of /HELP", e, cl);
	e->ptr = NULL;
}
