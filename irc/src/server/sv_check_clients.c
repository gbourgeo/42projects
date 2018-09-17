/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:28:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <time.h>

static void			wrong_username(t_fd *cl)
{
	char			*ptr;

	ptr = "Your username is invalid. Please make sure that your "\
		"username contains only alphanumeric characters.";
	cl->leaved = 2;
	cl->reason = "Invalid username";
	sv_notice(ptr, cl);
}

static void			error_loggin_in(char *err, t_fd *cl)
{
	char			*ptr;

	if (*err == 0)
	{
		ptr = "This nickname is registered. You have 30 sec to choose a "\
			"different nickname or it will be changed automatically.";
		sv_notice(ptr, cl);
		time(&cl->inf->must_change_nick);
	}
	else
	{
		cl->leaved = 1;
		cl->reason = err;
		sv_notice("You failed to log to the server. Try again later.", cl);
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
			return (error_loggin_in("", cl));
		}
		us = us->next;
	}
	sv_welcome(e, cl);
}

static void			check_allowed(t_fd *cl, t_env *e)
{
	t_user			*us;

	if (sv_allowed(&cl->i, e->conf.allowed_user))
		return (check_registered(cl, e));
	if ((us = sv_allowed(&cl->i, e->conf.pass_user)))
	{
		if (!ft_strcmp(us->passwd, cl->inf->pass))
			return (sv_welcome(e, cl));
	}
	error_loggin_in("Not allowed to login", cl);
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
				wrong_username(cl);
			else
				check_allowed(cl, e);
		}
		if (cl)
			cl = cl->next;
	}
}
