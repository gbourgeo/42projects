/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 16:42:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			error_loggin_in(t_file *us, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " NOTICE ", 8, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :This nickname is registered.", 30, 0);
	send(cl->fd, " Please choose a different nickname.", 36, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	if (cl->reg.password)
	{
		send(cl->fd, e->name, SERVER_LEN, 0);
		send(cl->fd, " NOTICE ", 8, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		send(cl->fd, " :Invalid password for ", 23, 0);
		send(cl->fd, us->nick, NICK_LEN, 0);
		send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	}
}

static void			check_registered(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!ft_strcmp(us->nick, cl->reg.nick))
		{
			if (cl->reg.password && !ft_strcmp(us->password, cl->reg.password))
			{
				cl->reg.umode = us->mode;
				ft_strncpy(cl->reg.nick, us->nick, NICK_LEN);
				ft_strncpy(cl->reg.username, us->username, NICK_LEN);
				ft_free(&cl->reg.realname);
				cl->reg.realname = us->realname;
				return ;
			}
			return (error_loggin_in(us, cl, e));
		}
		us = us->next;
	}
}

static void			wrong_username(t_fd *cl, t_env *e)
{
	cl->leaved = 2;
	cl->reason = "Invalid username";
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, "NOTICE", 6, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :*** Your username is invalid. Please make sure ", 49, 0);
	send(cl->fd, "that your username contains only alphanumeric ", 46, 0);
	send(cl->fd, "characters.", 11, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

void				sv_check_clients(t_env *e)
{
	t_fd			*cl;

	cl = e->fds;
	while (cl)
	{
		if (cl->leaved)
			cl = sv_clear_client(e, cl);
		else if (cl->reg.registered <= 0 && *cl->reg.nick && *cl->reg.username)
		{
			if (!ft_strisalnum(cl->reg.username))
				wrong_username(cl, e);
			else
			{
				sv_welcome(e, cl);
				check_registered(cl, e);
			}
		}
		else
			cl = cl->next;
	}
}
