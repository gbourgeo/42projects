/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 05:06:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 06:34:27 by gbourgeo         ###   ########.fr       */
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

static void			pre_requisit(int fd, char *name, char *num, char *nick)
{
	send(fd, name, SERVER_LEN, 0);
	send(fd, num, 5, 0);
	send(fd, nick, NICK_LEN, 0);
}

void				sv_welcome(t_env *e, t_fd *cl)
{
	pre_requisit(cl->fd, e->name, " 001 ", cl->reg.nick);
	send(cl->fd, " :Welcome to the GBOURGEO Internet Relay Chat ", 46, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	pre_requisit(cl->fd, e->name, " 002 ", cl->reg.nick);
	send(cl->fd, " :Your host is ", 15, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, "[", 1, 0);
	send(cl->fd, e->addr4, 16, 0);
	send(cl->fd, "/", 1, 0);
	send(cl->fd, e->port, ft_strlen(e->port), 0);
	send(cl->fd, "], running version 1.0", 22, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	pre_requisit(cl->fd, e->name, " 003 ", cl->reg.nick);
	send(cl->fd, " :This server was created ", 26, 0);
	send(cl->fd, e->creation, ft_strlen(e->creation) - 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	pre_requisit(cl->fd, e->name, " 004 ", cl->reg.nick);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, e->name + 1, SERVER_LEN - 1, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, "1.0", 3, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	cl->reg.registered = 1;
	e->members++;
}
