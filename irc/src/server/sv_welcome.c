/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 05:06:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:37:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** 001    RPL_WELCOME
**        "Welcome to the Internet Relay Network
**         <nick>!<user>@<host>"
** 002    RPL_YOURHOST
**        "Your host is <servername>, running version <ver>"
** 003    RPL_CREATED
**        "This server was created <date>"
** 004    RPL_MYINFO
**        "<servername> <version> <available user modes>
**        <available channel modes>"
*/

static void			rpl_1_2_3(t_env *e, t_fd *cl)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 001 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :Welcome to the Internet Relay Network ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write("!~", cl);
	sv_cl_write(cl->inf->username, cl);
	sv_cl_write("@", cl);
	sv_cl_write((*cl->i.host) ? cl->i.host : cl->i.addr, cl);
	sv_cl_write(END_CHECK, cl);
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 002 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :Your host is ", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(", running version 1.0", cl);
	sv_cl_write(END_CHECK, cl);
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 003 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :This server was created ", cl);
	sv_cl_write(e->creation, cl);
}

static void			rpl_4(t_env *e, t_fd *cl)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 004 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 1.0 ", cl);
	sv_cl_write(USER_MODES, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(CHAN_MODES, cl);
	sv_cl_write(END_CHECK, cl);
}

static void			convert(int nb, t_fd *cl, t_env *e)
{
	char			*ptr;

	(void)e;
	ptr = ft_itoa(nb);
	sv_cl_write(ptr, cl);
	free(ptr);
}

static void			rpl_5_42(t_env *e, t_fd *cl)
{
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 005 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" RFC2812 PREFIX=(ov)@+ CHANTYPES=#&!+ CHANLIMIT=", cl);
	convert(CHAN_LIMIT, cl, e);
	sv_cl_write(" NICK_LEN=", cl);
	convert(NICK_LEN, cl, e);
	sv_cl_write(" TOPIC_LEN=", cl);
	convert(TOPIC_LEN, cl, e);
	sv_cl_write(" CHANNELLEN=", cl);
	convert(CHANNAME_LEN, cl, e);
	sv_cl_write(" CHANMODES=", cl);
	sv_cl_write(CHAN_MODES + 3, cl);
	sv_cl_write(" :are supported by this server\r\n", cl);
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 042 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(cl->uid, cl);
	sv_cl_write(" :your unique ID\r\n", cl);
}

void				sv_welcome(t_env *e, t_fd *cl)
{
	rpl_1_2_3(e, cl);
	rpl_4(e, cl);
	rpl_5_42(e, cl);
	rpl_motd(cl, e);
	cl->inf->registered = 1;
	e->members++;
}
