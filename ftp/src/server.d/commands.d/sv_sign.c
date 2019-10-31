/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 16:52:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		signin_info(char *user, t_client *cl)
{
	ft_putstr("User \x1B[0;33m");
	ft_putstr(user);
	ft_putstr("\x1B[0m successfully logged in ! Changing directory to ");
	ft_putstr("\"\x1B[1;35m");
	ft_putstr(cl->home);
	ft_putendl("\x1B[0m\" !");
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
				if (SV_CHECK(sv->options, sv_interactive))
					signin_info(cmds[1], cl);
				return (sv_client_write(SERVER_OK_OUTPUT, cl));
			}
		ptr = ptr->next;
	}
	return (sv_cmd_err(ft_get_error(ERR_INVALID_NAMEPASS), cmds[0], cl, sv));
}
