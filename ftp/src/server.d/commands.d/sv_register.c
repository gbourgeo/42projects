/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:10:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/21 23:39:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			print_info(char **cmds, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client "COLOR_YELLOW"%d"COLOR_RESET": Successfully ", cl->fd);
	printf("reistered "COLOR_UNDERLINED);
	printf("%s:%s:***:%s:"COLOR_RESET".\n", cmds[1], cmds[2], cmds[4]);
}

static int			register_err(const char *str, char *cmdname, t_client *cl)
{
	int			errnb;

	if ((errnb = sv_client_write(cmdname, cl)) == IS_OK)
		if ((errnb = sv_client_write(": ", cl)) == IS_OK)
			if ((errnb = sv_client_write(str, cl)) == IS_OK)
				errnb = sv_client_write(".\n", cl);
	return (errnb);
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

int					sv_register(char **cmds, t_client *cl, t_server *sv)
{
	t_user		*users;
	int			errnb;

	users = sv->users;
	if (!cmds[1] || !cmds[2] || !cmds[3] || !cmds[4])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (users == NULL)
		return (register_err("Registration unavailable", cmds[0], cl));
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
		return (sv_cmd_err("Failed to register", cmds[0], cl, sv));
	return (sv_cmd_ok("Successfully registered", cl, sv));
}
