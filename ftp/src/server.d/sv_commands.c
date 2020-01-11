/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:58:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 20:00:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

size_t				sv_getuserrights(t_user *user)
{
	if (!user || user->rights < 1)
		return (3);
	if (user->rights < 2)
		return (6);
	if (user->rights < 3)
		return (11);
	return ((size_t)sv_commands(1));
}

t_command			*sv_commands(int getsize)
{
	static t_command	cmds[] = {
		{ "HELP", "Display available commands.", sv_help },
		{ "QUIT", "Quit the server.", sv_quit },
		{ "USER", "Identify the user.", sv_user },
		{ "PASS", "Give the user password.", sv_password },
		{ "CWD", "Change working directory.", sv_cwd },
		{ "CDUP", "Change to parent directory.", sv_cdup },
		{ "REIN", "Reinitialize the user.", sv_rein },

		{ "PORT", "Data port.", sv_port },
		// { "PASV", "Server listen to data port", sv_pasv },
		{ "ls", "List current working directory files.", sv_ls },
		{ "pwd", "Display current working directory.", sv_pwd },
		{ "mkdir", "Create directory on server.", sv_mkdir },
		{ "rmdir", "Remove directory from server.", sv_rmdir },
		{ "unlink", "Remove file from server.", sv_unlink },
		{ "get", "Get file from server.", sv_transfer },
		{ "put", "Put file to server.", sv_transfer },
		{ "register", "Register a new account.", sv_register },
	};

	if (getsize)
		return (t_command *)(sizeof(cmds) / sizeof(cmds[0]));
	return (cmds);
}
