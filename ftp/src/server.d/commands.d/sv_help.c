/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:31:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/23 00:19:33 by gbourgeo         ###   ########.fr       */
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
	int			i;
	int			errnb;
	t_command	*cmd;

	i = 0;
	errnb = IS_OK;
	while (cmds[i] && errnb == IS_OK)
	{
		if (!sv_validpathname(cmds[i]))
			errnb = sv_response(cl, "553 \"%s\" filename not allowed", cmds[i]);
		else if ((cmd = sv_command_by_name(cmds[i], cl)) == NULL)
			errnb = sv_response(cl, " \"%s\" invalid command", cmds[i]);
		else
			errnb = cmd->help(cmd, cl);
		i++;
	}
	return (errnb);
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

	cmd = sv_commands(0);
	errnb = sv_response(cl, "211-Help start");
	i = 0;
	if (cmds[1])
		errnb = sv_help_commands(cmds + 1, cl);
	else
	{
		while (i < (long)sv_commands(1) && errnb == IS_OK)
		{
			if (cl->login.member->rights >= cmd[i].rights
			&& (errnb = sv_client_write(cmd[i].name, cl)) == IS_OK
			&& (errnb = sv_client_write("\t\t", cl)) == IS_OK
			&& (errnb = sv_client_write(cmd[i].descrip, cl)) == IS_OK)
				errnb = sv_client_write("\n", cl);
			i++;
		}
	}
	if (errnb != IS_OK)
		return (sv_response(cl, "500 %s", ft_get_error(errnb)));
	return (sv_response(cl, "211 Help end"));
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
		"HELP SITE.",
	};
	long	i;
	int		errnb;

	i = 0;
	errnb = sv_response(cl, "214-%s [<commandname>]", cmd->name, cmd->descrip);
	while (errnb == IS_OK && help[i + 1])
	{
		errnb = sv_response(cl, "%s", help[i]);
		i++;
	}
	if (errnb == IS_OK)
		errnb = sv_response(cl, "214 %s", help[i]);
	return (errnb);
}
