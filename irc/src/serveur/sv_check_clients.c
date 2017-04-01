/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/26 00:01:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			wrong_username(t_fd *cl, t_env *e)
{
	char			*ptr;

	ptr = "Your username is invalid. Please make sure that your "\
		"username contains only alphanumeric characters.";
	cl->leaved = 2;
	cl->reason = "Invalid username";
	sv_notice(ptr, cl, e);
}

static void			error_loggin_in(int err, t_fd *cl, t_env *e)
{
	char			*ptr;

	if (err == 0)
	{
		ptr = "This nickname is registered. Please choose a different "\
			"nickname.";
		sv_notice(ptr, cl, e);
		if (cl->reg.password)
			sv_notice("Invalid password.", cl, e);
	}
	else
	{
		cl->leaved = err;
		cl->reason = (err == 1) ? "Invalid username" : "Invalid password";
		sv_notice("You failed to log to the server. Try again later.", cl, e);
	}
}

static void			check_registered(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!sv_strcmp(us->nick, cl->reg.nick))
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
			return (error_loggin_in(0, cl, e));
		}
		us = us->next;
	}
}

static void			check_password(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!ft_strcmp(us->username, cl->reg.username))
		{
			if (!ft_strcmp(us->password, cl->reg.password))
			{
				cl->reg.umode = us->mode;
				ft_strncpy(cl->reg.nick, us->nick, NICK_LEN);
				ft_strncpy(cl->reg.username, us->username, NICK_LEN);
				ft_free(&cl->reg.realname);
				cl->reg.realname = us->realname;
				sv_welcome(e, cl);
				return ;
			}
			return (error_loggin_in(1, cl, e));
		}
		us = us->next;
	}
	error_loggin_in(2, cl, e);
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
			else if (LOCK_SERVER)
				check_password(cl, e);
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
