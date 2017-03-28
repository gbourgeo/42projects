/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 05:06:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 19:55:35 by gbourgeo         ###   ########.fr       */
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
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 001 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" :Welcome to the Internet Relay Network ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write("!~", &cl->wr);
	sv_write(cl->reg.username, &cl->wr);
	sv_write("@", &cl->wr);
	sv_write(cl->addr, &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 002 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" :Your host is ", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(", running version 1.0", &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 003 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" :This server was created ", &cl->wr);
	sv_write(e->creation, &cl->wr);
}

static void			rpl_4(t_env *e, t_fd *cl)
{
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 004 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" ", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 1.0 ", &cl->wr);
	sv_write(USER_MODES, &cl->wr);
	sv_write(" ", &cl->wr);
	sv_write(CHAN_MODES, &cl->wr);
	sv_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

static void			convert(int nb, t_fd *cl, t_env *e)
{
	char			*ptr;

	(void)e;
	ptr = ft_itoa(nb);
	sv_write(ptr, &cl->wr);
	free(ptr);
}

static void			rpl_5_42(t_env *e, t_fd *cl)
{
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 005 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" RFC2812 PREFIX=(ov)@+ CHANTYPES=#&!+ CHANLIMIT=", &cl->wr);
	convert(CHAN_LIMIT, cl, e);
	sv_write(" NICK_LEN=", &cl->wr);
	convert(NICK_LEN, cl, e);
	sv_write(" TOPIC_LEN=", &cl->wr);
	convert(TOPIC_LEN, cl, e);
	sv_write(" CHANNELLEN=", &cl->wr);
	convert(CHANNAME_LEN, cl, e);
	sv_write(" CHANMODES=", &cl->wr);
	sv_write(CHAN_MODES + 3, &cl->wr);
	sv_write(" :are supported by this server\r\n", &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
	sv_write(":", &cl->wr);
	sv_write(e->name, &cl->wr);
	sv_write(" 042 ", &cl->wr);
	sv_write(cl->reg.nick, &cl->wr);
	sv_write(" ", &cl->wr);
	sv_write(cl->uid, &cl->wr);
	sv_write(" :your unique ID\r\n", &cl->wr);
}

void				sv_welcome(t_env *e, t_fd *cl)
{
	rpl_1_2_3(e, cl);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
	rpl_4(e, cl);
	rpl_5_42(e, cl);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
	rpl_motd(cl, e);
	cl->reg.registered = 1;
	e->members++;
}
