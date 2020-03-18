/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_help_local.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:40:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/18 13:33:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static t_command	*cl_command_by_name(char *cmdname)
{
	t_command	*cmd;
	long		i;

	cmd = cl_commands(0);
	i = 0;
	while (i < (long)cl_commands(1))
	{
		if (!ftp_strcmp(cmdname, cmd[i].name))
			return (cmd + i);
		i++;
	}
	return (NULL);
}

static int			cl_help_command(char **cmd, t_client *cl)
{
	t_command	*cmds;
	int			i;
	int			errnb;

	i = 1;
	errnb = IS_OK;
	while (cmd[i] && errnb == IS_OK)
	{
		if ((cmds = cl_command_by_name(cmd[i])) != NULL)
			errnb = cmds->help(cmds, cl);
		i++;
	}
	return (errnb);
}

static char			*padding(int pos, t_command *cmds)
{
	static char	space[] = "          ";
	long		i;
	int			len;
	int			max;

	i = 0;
	max = 0;
	if ((pos + 1) % 8 == 0)
		return ("\n");
	while (i < (long)cl_commands(1))
	{
		if ((len = ft_strlen(cmds[i].name)) > max)
			max = len;
		i++;
	}
	ft_memset(space, ' ', sizeof(space));
	len = ft_strlen(cmds[pos].name);
	space[max - len + 1] = '\0';
	return (space);
}

int					cl_help_local(char *buf, char **cmd, t_client *cl)
{
	t_command		*cmds;
	long			i;
	int				errnb;

	(void)buf;
	cmds = cl_commands(0);
	if (cmd[1])
		return (cl_help_command(cmd, cl));
	i = 0;
	errnb = wprintw(cl->ncu.chatwin, "Commands recognized:\n");
	while (i < (long)cl_commands(1) && errnb == OK)
	{
		errnb = wprintw(cl->ncu.chatwin, " %s%s",
		cmds[i].name, padding(i, cmds));
		i++;
	}
	if (errnb == OK
	&& (errnb = wprintw(cl->ncu.chatwin, "\n")) == OK
	&& (errnb = wattron(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN))) == OK
	&& (errnb = wprintw(cl->ncu.chatwin, "SUCCESS")) == OK
	&& (errnb = wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN))) == OK
	&& (errnb = wprintw(cl->ncu.chatwin, " Command OK\n")) == OK)
		wrefresh(cl->ncu.chatwin);
	return ((errnb == OK) ? IS_OK : ERR_WRITE);
}

int					cl_help_loc_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command prints informations about the commands allowed",
		"by the client to communicate or not with the server.", NULL
	};

	return (cl_help_print(cmd, "[<command_name>]", help, cl));
}
