/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_motd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 01:26:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/05 02:30:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** We agree dat (char rpl,...) is awfull as f***.
** Waiting for the RPL messages to be implemented.
*/

static void		prefix(char rpl, char *str, t_fd *cl, t_env *e)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	if (rpl == 0)
		sv_cl_write(" 375 ", cl);
	else if (rpl == 1)
		sv_cl_write(" 372 ", cl);
	else if (rpl == 2)
		sv_cl_write(" 376 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :- ", cl);
	sv_cl_write(str, cl);
	sv_cl_write(END_CHECK, cl);
}

void			rpl_motd(t_fd *cl, t_env *e)
{
	prefix(0, "Message of the day -", cl, e);
	prefix(1, "", cl, e);
	prefix(1, "          __                                    ", cl, e);
	prefix(1, "   ____ _/ /_  ____  __  ___________ ____  ____ ", cl, e);
	prefix(1, "  / __ `/ __ \\/ __ \\/ / / / ___/ __ `/ _ \\/ __ \\", cl, e);
	prefix(1, " / /_/ / /_/ / /_/ / /_/ / /  / /_/ /  __/ /_/ /", cl, e);
	prefix(1, " \\__, /_.___/\\____/\\__,_/_/   \\__, /\\___/\\____/ ", cl, e);
	prefix(1, "/____/                       /____/             ", cl, e);
	prefix(1, "", cl, e);
	prefix(1, "  Bienvenue sur le serveur de gbourgeo.", cl, e);
	prefix(1, "", cl, e);
	prefix(1, "  Ce serveur a ete realise avec amour,", cl, e);
	prefix(1, "  Ne lui brisez pas le coeur...", cl, e);
	prefix(1, "", cl, e);
	prefix(2, "End of Message of the day.", cl, e);
}
