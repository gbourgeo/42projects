/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:14:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 17:23:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

t_command				*cl_commands(int getsize)
{
	static t_command	cmd[] = {
		{ "?", "Help of local commands", cl_help_loc_help, cl_help_local, 0 },
		{ "\\", "Start a local command", cl_bslash_help, cl_bslash, 0 },
		{ "cd", "Change working directory", cl_cd_help, cl_cd, 0 },
		{ "connect", "Connect to a server", cl_connect_help, cl_connect, 0 },
		{ "clear", "Clear Server chat screen", cl_clear_help, cl_clear, 0 },
		{ "exit", "Quit the client", cl_exit_help, cl_exit, 0 },
		{ "get", "Get file from server", cl_get_help, cl_get, 0 },
		{ "help", "Help of server commands", cl_help_help, cl_help, 0 },
		{ "ls", "List files or directory", cl_ls_help, cl_ls, 0 },
		{ "mkdir", "Create directory", cl_mkdir_help, cl_mkdir, 0 },
		{ "nlst", "List files or directory", cl_nlst_help, cl_nlst, 0 },
		{ "pass", "Sends password to server", cl_pass_help, cl_pass, 0 },
		{ "put", "Put file to server", cl_put_help, cl_put, 0 },
		{ "pwd", "Print working directory", cl_pwd_help, cl_pwd, 0 },
		{ "quit", "Quit the server", cl_quit_help, cl_quit, 0 },
		{ "refresh", "Refresh list Windows", cl_refresh_help, cl_refresh, 0 },
		{ "rm", "Remove file from server", cl_rm_help, cl_rm, 0 },
		{ "rmdir", "Remove directory from server", cl_rmdir_help, cl_rmdir, 0 },
	};

	if (getsize)
		return (t_command *)(sizeof(cmd) / sizeof(cmd[0]));
	return (cmd);
}
