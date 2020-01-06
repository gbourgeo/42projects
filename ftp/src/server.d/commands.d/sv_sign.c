/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:53:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/06 18:14:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		print_info(char *name, t_client *cl, t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client "FTP_YELLOW"%d"FTP_RESET": Logged in as '", cl->fd);
	printf(FTP_ITALIC"%s"FTP_RESET"'.\n", name);
}

int				sv_signin(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*ptr;

	if (!cmds[1] || !cmds[2])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (!FT_CHECK(sv->options, sv_user_mode))
		return (sv_cmd_err("Sign-in Unavailable", cmds[0], cl, sv));
	ptr = sv_getuserbyname(sv->users, cmds[1]);
	if (ptr)
		if (!ft_strcmp(ptr->pass, cmds[2]))
		{
			ft_strdel(&cl->pwd);
			ft_strdel(&cl->oldpwd);
			if (!(cl->home = ptr->home)
			|| !(cl->pwd = ft_strdup("/"))
			|| !(cl->oldpwd = ft_strdup(cl->pwd)))
				return (ERR_MALLOC);
			cl->user = *ptr;
			print_info(cmds[1], cl, sv);
			return (sv_cmd_ok("Successfully signed in", cl, sv));
		}
	return (sv_cmd_err(ft_get_error(ERR_INVALID_NAMEPASS), cmds[0], cl, sv));
}
