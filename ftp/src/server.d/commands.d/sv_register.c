/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:10:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 02:13:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			print_info(char *name, t_client *cl, t_server *sv)
{
	if (SV_CHECK(sv->options, sv_interactive))
	{
		ft_putstr("Client \x1B[0;33m");
		ft_putnbr(cl->fd);
		ft_putstr("\x1B[0m: Successfully registered `");
		ft_putstr(name);
		ft_putendl("`");
	}
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
	if (!cmds[1] || !cmds[1][0] || !cmds[2] || !cmds[2][0]
	|| !cmds[3] || !cmds[3][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (users == NULL)
		return (register_err("Registration unavailable", cmds[0], cl));
	errnb = IS_OK;
	if (!sv_user_parse(&cmds[1], sv))
		return (sv_cmd_err(ft_get_error(ERR_WRONG_PARAM), cmds[0], cl, sv));
	while (users)
	{
		if (!ft_strcmp(users->name, cmds[2]))
			return (sv_cmd_err(ft_get_error(ERR_ALREADY_REGISTERED), cmds[0],
								cl, sv));
		users = users->next;
	}
	if ((errnb = sv_new_user(&cmds[1], &sv->users->next, sv)) != IS_OK)
		return (errnb);
	sv->users->next->type |= us_new;
	print_info(cmds[2], cl, sv);
	if (sv_save_user(sv->users->next, cl, sv))
		return (sv_cmd_err("Failed to register", cmds[0], cl, sv));
	return (sv_cmd_ok("Successfully registered", cl, sv));
}
