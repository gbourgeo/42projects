/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:31:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:32:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static t_command	*sv_command_by_name(char *cmdname, t_client *cl)
{
	t_command	*cmd;
	long		i;

	cmd = sv_commands(0);
	i = 0;
	while (i < (long)sv_commands(1))
	{
		if (!ftp_strcmp(cmdname, cmd[i].name))
		{
			if (cl->login.member->rights >= cmd[i].rights)
				return (cmd + i);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static int			sv_help_commands(char **cmds, t_client *cl)
{
	t_command	*cmd;
	int			i;
	int			errnb;

	i = 0;
	if ((errnb = sv_response(cl, "214-Help start")) != IS_OK)
		return (errnb);
	while (cmds[i])
	{
		if (!sv_validpathname(cmds[i])
		|| !(cmd = sv_command_by_name(cmds[i], cl)))
			return (sv_response(cl, "553 \"%s\" invalid command", cmds[i]));
		if ((errnb = cmd->help(cmd, cl)) != IS_OK)
			return (sv_response(cl, "500 %s", ft_get_error(errnb)));
		i++;
	}
	return (sv_response(cl, "214 Help OK"));
}

/*
** HELP
** 211, 214
** 500, 501, 502, 421
*/

int					sv_help(char **cmds, t_client *cl)
{
	t_command	*cmd;
	int			errnb;
	long		i;

	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	cmd = sv_commands(0);
	i = 0;
	if (cmds[1])
		return (sv_help_commands(cmds + 1, cl));
	errnb = sv_response(cl, "214-The following commands are recognized:");
	while (i < (long)sv_commands(1) && errnb == IS_OK)
	{
		if (cl->login.member->rights >= cmd[i].rights
		&& (errnb = sv_client_write(" ", cl)) == IS_OK)
			errnb = sv_client_write(cmd[i].name, cl);
		if (!((i + 1) % 10))
			errnb = sv_client_write("\n", cl);
		else if (ft_strlen(cmd[i].name) < 4)
			errnb = sv_client_write(" ", cl);
		i++;
	}
	if (errnb != IS_OK)
		return (sv_response(cl, "\n500 %s", ft_get_error(errnb)));
	return (sv_response(cl, "\n214 Help OK"));
}

/*
** HELP [<SP> <chaîne>] <CRLF>
*/

int					sv_help_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command send helpful information regarding its ",
		"implementation status over the control connection to the user.",
		"The command may take an argument (e.g., any command name) and",
		"return more specific information as a response. HELP is allowed",
		"before entering a USER command. The server may use this reply",
		"to specify site-dependent parameters, e.g., in response to",
		"HELP SITE.", NULL
	};

	return (sv_print_help(cl, cmd, "[<commandname>]", help));
}
