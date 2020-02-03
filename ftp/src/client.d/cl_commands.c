/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:14:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 16:00:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

t_command				*cl_commands(int getsize)
{
	static t_command	cmd[] = {
		{ "?", cl_help },
		{ "cd", cl_cd },
		{ "quit", cl_quit },
		{ "get", cl_get },
		{ "ls", cl_ls },
		{ "mkdir", cl_mkdir },
		{ "put", cl_put },
		{ "pwd", cl_pwd },
		{ "rm", cl_rm },
	};

	if (getsize)
		return (t_command *)(sizeof(cmd) / sizeof(cmd[0]));
	return (cmd);
}
