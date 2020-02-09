/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:58:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:39:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** { "APPE", "Append data to file.", sv_appe_help, sv_appe, 3 },
** { "NOOP", "Sends OK.", sv_noop_help, sv_noop, 3 },
** { "RNFR", "File to be renamed.", sv_rnfr_help, sv_rnfr, 3 },
** { "RNTO", "File new name.", sv_rnto_help, sv_rnto, 3 },
** { "ABOR", "Abort last command.", sv_abor_help, sv_abor, 3 },
*/

t_command			*sv_commands(int getsize)
{
	static t_command	cmds[] = {
		{ "CDUP", "Change to parent directory.", sv_cdup_help, sv_cdup, 1 },
		{ "CWD", "Change working directory.", sv_cwd_help, sv_cwd, 1 },
		{ "DELE", "Remove file from server.", sv_dele_help, sv_dele, 2 },
		{ "HELP", "Display available commands.", sv_help_help, sv_help, 0 },
		{ "MKD", "Create directory on server.", sv_mkd_help, sv_mkd, 2 },
		{ "NLST", "Short catalog.", sv_nlst_help, sv_nlst, 1 },
		{ "LIST", "File listing.", sv_list_help, sv_list, 3 },
		{ "PASS", "Give the user password.", sv_pass_help, sv_pass, 0 },
		{ "PASV", "Server enters passive mode.", sv_pasv_help, sv_pasv, 2 },
		{ "PORT", "Specify Data port to open.", sv_port_help, sv_port, 2 },
		{ "QUIT", "Quit the server.", sv_quit_help, sv_quit, 0 },
		{ "REIN", "Reinitialize the user.", sv_rein_help, sv_rein, 2 },
		{ "RETR", "Retreive file from server.", sv_retr_help, sv_retr, 2 },
		{ "RMD", "Remove directory from server.", sv_rmd_help, sv_rmd, 2 },
		{ "STOR", "Store data.", sv_stor_help, sv_stor, 2 },
		{ "STOU", "Store data in an unique file.", sv_stou_help, sv_stou, 2 },
		{ "TYPE", "Data representation type.", sv_type_help, sv_type, 2 },
		{ "USER", "Identify the user.", sv_user_help, sv_user, 0 },
		{ "PWD", "Current working directory path.", sv_pwd_help, sv_pwd, 1 },
		{ "REGT", "Register a new account.", sv_regt_help, sv_regt, 3 },
	};

	return ((getsize) ? (t_command *)(sizeof(cmds) / sizeof(cmds[0])) : cmds);
}
