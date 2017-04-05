/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rpl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:38:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 02:43:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			rpl_cmode(t_grp *grp, char *limit)
{
	sv_cl_write(":", grp->to);
	sv_cl_write((grp->on->cmode & CHFL_ANON && grp->to->fd != grp->from->fd) ?
				"anonymous" : grp->from->inf->nick, grp->to);
	sv_cl_write("!~", grp->to);
	sv_cl_write((grp->on->cmode & CHFL_ANON && grp->to->fd != grp->from->fd) ?
				"anonymous" : grp->from->inf->username, grp->to);
	sv_cl_write("@", grp->to);
	sv_cl_write((grp->on->cmode & CHFL_ANON && grp->to->fd != grp->from->fd) ?
				"anonymous" : grp->from->addr, grp->to);
	sv_cl_write(" MODE ", grp->to);
	sv_cl_write(grp->on->name, grp->to);
	sv_cl_write((grp->c) ? " +" : " -", grp->to);
	sv_cl_write(grp->mdr, grp->to);
	if ((*grp->ptr == 'l' || *grp->ptr == 'k') && grp->c)
	{
		sv_cl_write(" ", grp->to);
		sv_cl_write((*grp->ptr == 'l') ? limit : grp->on->key, grp->to);
	}
	sv_cl_write(END_CHECK, grp->to);
	if (limit)
		free(limit);
}

void			rpl_umode(t_grp *g, t_chan *c, t_fd *to, t_fd *cl)
{
	sv_cl_write(":", to);
	sv_cl_write((c->cmode & CHFL_ANON) ? "anonymous" : cl->inf->nick, to);
	sv_cl_write("!~", to);
	sv_cl_write((c->cmode & CHFL_ANON) ? "anonymous" : cl->inf->username, to);
	sv_cl_write("@", to);
	sv_cl_write((c->cmode & CHFL_ANON) ? "anonymous" : cl->addr, to);
	sv_cl_write(" MODE ", to);
	sv_cl_write(c->name, to);
	sv_cl_write((g->c) ? " :+" : " :-", to);
	sv_cl_write(g->ptr, to);
	sv_cl_write(" ", to);
	sv_cl_write(g->to->inf->nick, to);
	sv_cl_write(END_CHECK, to);
}
