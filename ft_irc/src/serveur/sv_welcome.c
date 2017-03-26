/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 05:06:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/26 01:26:38 by gbourgeo         ###   ########.fr       */
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
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 001 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" :Welcome to the Internet Relay Network ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write("!~", &e->wr);
	sv_cl_write(cl->reg.username, &e->wr);
	sv_cl_write("@", &e->wr);
	sv_cl_write(cl->addr, &e->wr);
	sv_cl_write(END_CHECK, &e->wr);
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 002 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" :Your host is ", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write("], running version 1.0", &e->wr);
	sv_cl_write(END_CHECK, &e->wr);
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 003 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" :This server was created ", &e->wr);
	sv_cl_write(e->creation, &e->wr);
}

static void			rpl_4(t_env *e, t_fd *cl)
{
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 004 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" ", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 1.0 ", &e->wr);
	sv_cl_write(USER_MODES, &e->wr);
	sv_cl_write(" ", &e->wr);
	sv_cl_write(CHAN_MODES, &e->wr);
	sv_cl_write(END_CHECK, &e->wr);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
}

static void			convert(int nb, t_env *e)
{
	char			*ptr;

	ptr = ft_itoa(nb);
	sv_cl_write(ptr, &e->wr);
	free(ptr);
}

static void			rpl_5_42(t_env *e, t_fd *cl)
{
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 005 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" RFC2812 PREFIX=(ov)@+ CHANTYPES=#&!+ CHANLIMIT=", &e->wr);
	convert(CHAN_LIMIT, e);
	sv_cl_write(" NICK_LEN=", &e->wr);
	convert(NICK_LEN, e);
	sv_cl_write(" TOPIC_LEN=", &e->wr);
	convert(TOPIC_LEN, e);
	sv_cl_write(" CHANNELLEN=", &e->wr);
	convert(CHANNAME_LEN, e);
	sv_cl_write(" CHANMODES=", &e->wr);
	sv_cl_write(CHAN_MODES + 3, &e->wr);
	sv_cl_write(" :are supported by this server\r\n", &e->wr);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
	sv_cl_write(":", &e->wr);
	sv_cl_write(e->name, &e->wr);
	sv_cl_write(" 042 ", &e->wr);
	sv_cl_write(cl->reg.nick, &e->wr);
	sv_cl_write(" ", &e->wr);
	sv_cl_write(cl->uid, &e->wr);
	sv_cl_write(" :your unique ID\r\n", &e->wr);
}

void				sv_welcome(t_env *e, t_fd *cl)
{
	rpl_1_2_3(e, cl);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
	rpl_4(e, cl);
	rpl_5_42(e, cl);
	sv_cl_send_to(cl, &e->wr);
	e->wr.head = e->wr.tail;
	rpl_motd(cl, e);
	cl->reg.registered = 1;
	e->members++;
}
