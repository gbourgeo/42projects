/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 12:35:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			error_loggin_in(t_file *us, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, cl);
	sv_cl_write(" NOTICE ", cl);
	sv_cl_write(cl->reg.nick, cl);
	sv_cl_write(" :This nickname is registered.", cl);
	sv_cl_write(" Please choose a different nickname.", cl);
	sv_cl_write(END_CHECK, cl);
	sv_cl_send_to(cl, cl);
	if (cl->reg.password)
	{
		sv_cl_write(e->name, cl);
		sv_cl_write(" NOTICE ", cl);
		sv_cl_write(cl->reg.nick, cl);
		sv_cl_write(" :Invalid password for ", cl);
		sv_cl_write(us->nick, cl);
		sv_cl_write(END_CHECK, cl);
		sv_cl_send_to(cl, cl);
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
	sv_cl_write(e->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write("NOTICE", cl);
	sv_cl_write(" ", cl);
	sv_cl_write(cl->reg.nick, cl);
	sv_cl_write(" :*** Your username is invalid. Please make sure ", cl);
	sv_cl_write("that your username contains only alphanumeric ", cl);
	sv_cl_write("characters.", cl);
	sv_cl_write(END_CHECK, cl);
	sv_cl_send_to(cl, cl);
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
