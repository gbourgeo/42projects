/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:14:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/30 14:21:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

t_command				*cl_commands(int getsize)
{
	static t_command	cmd[] = {
		{ "?", cl_help },
		{ "cd", cl_cd },
		{ "ls", cl_ls },
		{ "rm", cl_rm },
		{ "mkd", cl_mkd },
		{ "exit", cl_quit },
		{ "get", cl_get },
		{ "put", cl_put },
		{ "pwd", cl_pwd },
	};

	if (getsize)
		return (long *)(sizeof(cmd) / sizeof(cmd[0]));
	return (cmd);
}
