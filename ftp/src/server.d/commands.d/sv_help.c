/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:31:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 20:04:48 by gbourgeo         ###   ########.fr       */
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
		if (!ft_strcmp(cmdname, cmd[i].name))
		{
			if (cl->login.member->rights >= cmd[i].rights)
				return (cmd + i);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static int			sv_help_commands(char **cmds, t_client *cl, t_server *sv)
{
	int			i;
	int			errnb;
	t_command	*cmd;

	i = 0;
	errnb = IS_OK;
	while (cmds[i] && errnb == IS_OK)
	{
		if ((cmd = sv_command_by_name(cmds[i], cl)) == NULL)
			errnb = sv_cmd_err("Invalid command", cmds[i], cl, sv);
		else
			errnb = cmd->help(cmd, cl);
		i++;
	}
	return (errnb);
}

int					sv_help(char **cmds, t_client *cl, t_server *sv)
{
	t_command	*cmd;
	int			errnb;
	long		i;

	cmd = sv_commands(0);
	errnb = IS_OK;
	i = 0;
	if (cmds[1])
		errnb = sv_help_commands(cmds + 1, cl, sv);
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
		return (sv_cmd_err(ft_get_error(errnb), cmds[0], cl, sv));
	return (sv_cmd_ok("End HELP", cl, sv));
}

int					sv_help_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Help\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
