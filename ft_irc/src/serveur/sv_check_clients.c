/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_clients.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 04:52:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/17 05:07:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int			error_loggin_in(char *err, t_fd *cl)
{
	cl->reg.registered = 0;
	send(cl->fd, err, ft_strlen(err), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	ft_strclr(cl->reg.username);
	free(cl->reg.password);
	cl->reg.password = NULL;
	cl->reg.umode = 0;
	ft_strclr(cl->reg.nick);
	ft_free(&cl->reg.realname);
	return (0);
}

static int			check_username(t_fd *cl, t_env *e)
{
	t_file			*us;

	us = e->users;
	while (us)
	{
		if (!ft_strcmp(us->username, cl->reg.username))
		{
			if (!ft_strcmp(us->password, cl->reg.password))
			{
				cl->reg.registered = 1;
				cl->reg.umode = us->mode;
				ft_strncpy(cl->reg.nick, us->nick, NICK_LEN);
				ft_free(&cl->reg.realname);
				cl->reg.realname = us->realname;
				sv_welcome(e, cl);
				return (0);
			}
			return (error_loggin_in("ERROR: failed to loggin.", cl));
		}
		else if (!ft_strcmp(us->nick, cl->reg.nick))
			return (error_loggin_in("ERROR: Nick collision.", cl));
		us = us->next;
	}
	return (1);
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
			if (cl->reg.password)
			{
				if (check_username(cl, e))
					sv_welcome(e, cl);
			}
			else
				sv_welcome(e, cl);
		}
		else
			cl = cl->next;
	}
}
