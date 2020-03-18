/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_regt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:10:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:24:45 by gbourgeo         ###   ########.fr       */
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

int					sv_regt(char **cmds, t_client *cl)
{
	t_server	*sv;
	t_user		*users;
	int			errnb;

	sv = &g_serv;
	users = sv->users;
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] || !cmds[2] || !cmds[3] || !cmds[4])
		return (sv_response(cl, "501 %s", ft_get_error(ERR_NB_PARAMS)));
	if (!sv_user_parse(&cmds[1], sv))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_WRONG_PARAM)));
	while (users)
	{
		if (!ft_strcmp(users->name, cmds[2]))
			return (sv_response(cl, "510 %s", ft_get_error(ERR_REGISTERED)));
		users = users->next;
	}
	if ((errnb = sv_new_user(&cmds[1], &sv->users->next, sv)) != IS_OK)
		return (errnb);
	sv->users->next->type |= us_new;
	print_info(cmds, cl, sv);
	if ((errnb = sv_save_user(sv->users->next, cl, sv)))
		return (errnb);
	return (sv_response(cl, "259 \"%s\" registered", cmds[2]));
}

/*
** Register parameters are like in SV_USERS_FILE:
**
** 1st :	Type of the new user (Server or Client).
** 2nd :	Name of the new user.
** 3rd :	Password to sign in.
** 4th :	The rights th new user have.
**
** Example: "REGT C toto KouKouLeSAmiS 2"
*/

int					sv_regt_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command register a new user in the server user databse.",
		"The parameters are server like implemented and follow this rules:",
		"",
		"	REGT <type> <name> <password> <privileges>",
		"",
		"where <type> is a single character specifying if you want to register",
		"a new Server (S) or a new Client (C), <name> represents the user",
		"name to pass to USER when registering to the server, <password>",
		"is the password to give to PASS when registering, and <privileges>",
		"is the user privileges on the server and should be a number from",
		"0 to 3. Low privileges (0) will grant less commands to the user",
		"with higher privileges.", NULL
	};

	return (sv_print_help(cl, cmd, "<type> <name> <pass> <rights>", help));
}
