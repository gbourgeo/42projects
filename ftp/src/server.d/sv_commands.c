/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:58:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 19:50:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static t_command	define_commands(char *name, char *descrip, int (*func)())
{
	return ((t_command){ name, descrip, func });
}

static void			define_all(t_command *cmds)
{
	*cmds = define_commands("help", "Display available commands.", sv_help);
	*(cmds + 1) = define_commands("quit", "Quit the server.", sv_quit);
	*(cmds + 2) = define_commands("sign", "Sign-in to the server.", sv_signin);
	*(cmds + 3) = define_commands("ls", "List current working directory files."
	, sv_ls);
	*(cmds + 4) = define_commands("cd", "Change working directory.", sv_cd);
	*(cmds + 5) = define_commands("pwd", "Display current working directory."
	, sv_pwd);
	*(cmds + 6) = define_commands("mkdir", "Create directory on server."
	, sv_mkdir);
	*(cmds + 7) = define_commands("rmdir", "Remove directory from server."
	, sv_rmdir);
	*(cmds + 8) = define_commands("unlink", "Remove file from server."
	, sv_unlink);
	*(cmds + 9) = define_commands("get", "Get file from server.", sv_get);
	*(cmds + 10) = define_commands("put", "Put file to server.", sv_put);
	*(cmds + 11) = define_commands("register", "Register a new account."
	, sv_register);
}

t_command			*sv_commands(int getsize, int tofree)
{
	static t_command	*cmds = NULL;

	if (tofree)
	{
		if (cmds)
			free(cmds);
		cmds = NULL;
		return (NULL);
	}
	if (getsize)
		return ((cmds == NULL) ? (t_command *)0 : (t_command *)13);
	if (cmds != NULL)
		return (cmds);
	if ((cmds = ft_memalloc(sizeof(*cmds) * 13)) == NULL)
		return (NULL);
	define_all(cmds);
	return (cmds);
}

int					sv_getcommandsright(int rights)
{
	if (rights < 1)
		return (3);
	if (rights < 2)
		return (6);
	if (rights < 3)
		return (11);
	return ((int)sv_commands(1, 0));
}
