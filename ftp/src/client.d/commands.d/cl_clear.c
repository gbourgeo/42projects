/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:22:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 23:40:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int					cl_clear(char *buf, char **cmd, t_client *cl)
{
	(void)buf;
	(void)cmd;
	wclear(cl->ncu.chatwin);
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

int					cl_clear_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the user to clear the server chat Window.", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
