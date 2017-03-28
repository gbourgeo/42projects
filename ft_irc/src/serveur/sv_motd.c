/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_motd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:26:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 19:55:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		prefix(char *str, t_fd *cl, t_env *e)
{
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 372 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" :- ", &cl->wr);
	sv_write(str, &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
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
