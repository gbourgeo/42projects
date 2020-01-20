/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_regt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:10:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 17:55:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			print_info(char **cmds, t_client *cl, t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client "FTP_YELLOW"%d"FTP_RESET": Successfully ", cl->fd);
	printf("reistered "FTP_UNDERLINED);
	printf("%s:%s:***:%s:"FTP_RESET".\n", cmds[1], cmds[2], cmds[4]);
}

/*
** Register parameters are like in SV_USERS_FILE:
**
** 1st :	Type of the new user (Server or Client).
** 2nd :	Name of the new user.
** 3rd :	Password to sign in.
** 4th :	The rights th new user have.
**
** Example: "register C toto KouKouLeSAmiS 2"
*/

int					sv_regt(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*users;
	int			errnb;

	users = sv->users;
	if (!cmds[1] || !cmds[2] || !cmds[3] || !cmds[4])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (!FT_CHECK(sv->options, sv_user_mode))
		return (sv_cmd_err("Registration Unavailable", cmds[0], cl, sv));
	if (!sv_user_parse(&cmds[1], sv))
		return (sv_cmd_err(ft_get_error(ERR_WRONG_PARAM), cmds[0], cl, sv));
	while (users)
	{
		if (!ft_strcmp(users->name, cmds[2]))
			return (sv_cmd_err(ft_get_error(ERR_REGISTERED), cmds[0], cl, sv));
		users = users->next;
	}
	if ((errnb = sv_new_user(&cmds[1], &sv->users->next, sv)) != IS_OK)
		return (errnb);
	sv->users->next->type |= us_new;
	print_info(cmds, cl, sv);
	if (sv_save_user(sv->users->next, cl, sv))
		return (sv_cmd_err("Failed to save user", cmds[0], cl, sv));
	return (sv_cmd_ok("Registered new user", cl, sv));
}

int					sv_regt_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Register a new account\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
