/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:58:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:24:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

size_t				sv_getcommandsright(int rights)
{
	if (rights < 1)
		return (3);
	if (rights < 2)
		return (6);
	if (rights < 3)
		return (11);
	return ((size_t)sv_commands(1));
}

t_command			*sv_commands(int getsize)
{
	static t_command	cmds[] = {
		{ "help", "Display available commands.", sv_help },
		{ "quit", "Quit the server.", sv_quit },
		{ "sign", "Sign-in to the server.", sv_signin },
		{ "ls", "List current working directory files.", sv_ls },
		{ "cd", "Change working directory.", sv_cd },
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
