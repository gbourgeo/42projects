/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 22:07:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <time.h>

static void			wrong_username(t_fd *cl, t_env *e)
{
	char			*ptr;

	ptr = "Your username is invalid. Please make sure that your "\
		"username contains only alphanumeric characters.";
	cl->leaved = 2;
	cl->reason = "Invalid username";
	sv_notice(ptr, cl, e);
}

static void			error_loggin_in(char *err, t_file *us, t_fd *cl, t_env *e)
{
	char			*ptr;

	if (*err == 0)
	{
		ptr = "This nickname is registered. You have 30 sec to choose a "\
			"different nickname or it will be changed automatically.";
		sv_notice(ptr, cl, e);
		if (cl->inf->pass && ft_strcmp(us->pass, cl->inf->pass))
			sv_notice("Invalid pass.", cl, e);
		time(&cl->inf->must_change_nick);
	}
	else
	{
		cl->leaved = 1;
		cl->reason = err;
		sv_notice("You failed to log to the server. Try again later.", cl, e);
	}
}

static void			check_registered(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!sv_strcmp(us->nick, cl->inf->nick))
		{
			if (us->registered <= 0 && cl->inf->pass &&
				!ft_strcmp(us->pass, cl->inf->pass))
			{
				free(cl->inf->pass);
				ft_free(&cl->inf->realname);
				free(cl->inf);
				cl->inf = us;
				break ;
			}
			sv_welcome(e, cl);
			return (error_loggin_in("", us, cl, e));
		}
		us = us->next;
	}
	sv_welcome(e, cl);
}

static void			check_pass(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!sv_strcmp(us->nick, cl->inf->nick))
		{
			if (ft_strcmp(us->pass, cl->inf->pass))
				return (error_loggin_in("Invalid pass", us, cl, e));
			if (cl->inf->registered)
				return (error_loggin_in("Already registered", us, cl, e));
			free(cl->inf->pass);
			ft_free(&cl->inf->realname);
			free(cl->inf);
			cl->inf = us;
			sv_welcome(e, cl);
			return ;
		}
		us = us->next;
	}
	error_loggin_in("Invalid login", us, cl, e);
}

void				sv_check_clients(t_env *e)
{
	t_fd			*cl;

	cl = e->fds;
	while (cl)
	{
		if (cl->inf->must_change_nick > 0)
			sv_nick_change(cl, e);
		if (cl->leaved)
		{
			if (cl->wr.len == 0)
				cl = sv_clear_client(e, cl);
		}
		else if (cl->inf->registered <= 0 && *cl->inf->nick &&
				*cl->inf->username)
		{
			if (!ft_strisalnum(cl->inf->username))
				wrong_username(cl, e);
			else if (LOCK_SERVER)
				check_pass(cl, e);
			else
				check_registered(cl, e);
		}
		if (cl)
			cl = cl->next;
	}
}
