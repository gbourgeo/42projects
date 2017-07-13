/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_oper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 03:01:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:34:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		new_op(t_user *op, t_fd *cl)
{
	cl->inf->umode |= (op->mode == 'O') ? USR_OP : USR_LOCALOP;
	sv_cl_write(":", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write("!~", cl);
	sv_cl_write(cl->inf->username, cl);
	sv_cl_write("@", cl);
	sv_cl_write((*cl->i.host) ? cl->i.host : cl->i.addr, cl);
	sv_cl_write(" MODE ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write((op->mode == 'O') ? " :+O" : " +o", cl);
	sv_cl_write(END_CHECK, cl);
}

void			sv_oper(char **cmds, t_env *e, t_fd *cl)
{
	t_user		*op;

	if (!cmds[0] || !cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, NULL, NULL, cl));
	op = e->conf.opers;
	while (op)
	{
		if (!ft_strcmp(op->hostname, cl->i.host) &&
			!ft_strcmp(op->nick, cmds[0]))
		{
			if (!ft_strcmp(op->passwd, cmds[1]))
				return (new_op(op, cl));
			return (sv_err(ERR_PASSWDMISMATCH, NULL, NULL, cl));
		}
		op = op->next;
	}
	sv_err(ERR_NOOPERHOST, NULL, NULL, cl);
}
