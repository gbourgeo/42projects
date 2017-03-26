/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_motd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:26:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/26 01:48:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		prefix(char *str, t_fd *cl, t_env *e)
{
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 372 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" :- ", &e->wr);
	sv_cl_write(str, &e->wr);
	sv_cl_write(END_CHECK, &e->wr);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
}

void			rpl_motd(t_fd *cl, t_env *e)
{
	prefix("Message of the day -", cl, e);
	prefix("", cl, e);
	prefix("          __                                    ", cl, e);
	prefix("   ____ _/ /_  ____  __  ___________ ____  ____ ", cl, e);
	prefix("  / __ `/ __ \\/ __ \\/ / / / ___/ __ `/ _ \\/ __ \\", cl, e);
	prefix(" / /_/ / /_/ / /_/ / /_/ / /  / /_/ /  __/ /_/ /", cl, e);
	prefix(" \\__, /_.___/\\____/\\__,_/_/   \\__, /\\___/\\____/ ", cl, e);
	prefix("/____/                       /____/             ", cl, e);
	prefix("", cl, e);
	prefix("  Bienvenue sur le serveur de gbourgeo.", cl, e);
	prefix("", cl, e);
	prefix("  Ce serveur a ete realise avec amour,", cl, e);
	prefix("  Ne lui brisez pas le coeur...", cl, e);
	prefix("", cl, e);
}
