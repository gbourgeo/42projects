/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/21 19:46:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		signin_success(t_client *cl, t_server *sv)
{
	int			errnb;

	if (SV_CHECK(sv->options, sv_interactive))
	{
		ft_putstr("Client \x1B[0;33m");
		ft_putnbr(cl->fd);
		ft_putendl("\x1B[0m: successfully logged in.");
	}
	if ((errnb = sv_client_write("Successfully logged in.", cl)) == IS_OK)
		errnb = sv_client_write(SERVER_OK_OUTPUT, cl);
	return (errnb);
}

int				sv_signin(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*ptr;

	if (!cmds[1] || !cmds[2])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	ptr = sv->users;
	while (ptr)
	{
		if (!ft_strcmp(cmds[1], ptr->name))
			if (!ft_strcmp(cmds[2], ptr->pass))
			{
				ft_strdel(&cl->pwd);
				ft_strdel(&cl->oldpwd);
				if (!(cl->home = ptr->home)
				|| !(cl->pwd = ft_strdup("/"))
				|| !(cl->oldpwd = ft_strdup(cl->pwd)))
					return (ERR_MALLOC);
				cl->user = ptr;
				return (signin_success(cl, sv));
			}
		ptr = ptr->next;
	}
	return (sv_cmd_err(ft_get_error(ERR_INVALID_NAMEPASS), cmds[0], cl, sv));
}
